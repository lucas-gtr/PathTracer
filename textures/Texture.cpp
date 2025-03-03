#include "Texture.hpp"

Texture::Texture(const float value){
  m_width = 1;
  m_height = 1;
  m_channels = 1;

  m_image = new float[1];
  m_image[0] = value;
}

Texture::Texture(const vec3& value){
  m_width = 1;
  m_height = 1;
  m_channels = 3;
  
  m_image = new float[3];
  m_image[0] = value[0];
  m_image[1] = value[1];
  m_image[2] = value[2];
}

Texture::Texture(std::string file_path){
  TextureData texture_data = TextureLoader::Load(file_path.c_str());
  
  if(texture_data.image == nullptr) {
    m_width = 1;
    m_height = 1;
    m_channels = 3;
    
    m_image = new float[3];
    m_image[0] = 1.0f;
    m_image[1] = 0.0f;
    m_image[2] = 1.0f;
    return;
  }
  
  m_width = texture_data.width;
  m_height = texture_data.height;
  m_channels = texture_data.n_channels;
  
  m_image = new float[m_width*m_height*m_channels];
  for(int i = 0; i < m_width*m_height*m_channels; i++){
    m_image[i] = int(texture_data.image[i]) / 255.0f;
  }
}

void Texture::SetClampBorderColor(const vec3& color){
  m_clamp_border_color = color;
}

void Texture::SetTextureWrapping(TextureWrapping texture_wrapping)
{
  if (texture_wrapping == TextureWrapping::REPEAT)
    m_texture_wrapping_strategy = std::make_unique<RepeatWrapping>();
  else if (texture_wrapping == TextureWrapping::REPEAT_MIRROR)
    m_texture_wrapping_strategy = std::make_unique<RepeatMirrorWrapping>();
  else if (texture_wrapping == TextureWrapping::CLAMP)
    m_texture_wrapping_strategy = std::make_unique<ClampWrapping>();
  else if (texture_wrapping == TextureWrapping::CLAMP_COLOR)
    m_texture_wrapping_strategy = std::make_unique<ClampColorWrapping>();
}

void Texture::SetTextureFiltering(TextureFiltering texture_filtering)
{
  if (texture_filtering == TextureFiltering::NEAREST)
    m_texture_filtering_strategy = std::make_unique<NearestFiltering>();
  else if (texture_filtering == TextureFiltering::LINEAR)
    m_texture_filtering_strategy = std::make_unique<LinearFiltering>();
}

void Texture::SetColorSpace(ColorSpace color_space){
  if (m_color_space == color_space) return;
  
  for (int i = 0; i < m_width * m_height; i++) {
    for (int channel = 0; channel < m_channels; channel++) {
      if (m_channels == 4 && channel == 3) continue; // Don't change alpha
      
      float& color = m_image[i * m_channels + channel];
      if (color_space == ColorSpace::sRGB) {
        if (color <= 0.0031308f) color *= 12.92f;
        else color = 1.055f * std::pow(color, 1.0f / 2.4f) - 0.055f;
      } else if (color_space == ColorSpace::RGB) {
        if (color <= 0.04045f) color /= 12.92f;
        else color = std::pow((color + 0.055f) / 1.055f, 2.4f);
      }
    }
  }  
  m_color_space = color_space;
}

const vec2 Texture::GetPixelCoordinates(const vec2& texture_coord){
  return m_texture_wrapping_strategy->GetPixelCoordinates(texture_coord, m_width, m_height);
}

float Texture::GetValue1F(const vec2& texture_coord){
  vec2 pixel_coord = GetPixelCoordinates(texture_coord);
  if(pixel_coord == vec2(-1.0f))
    return (m_clamp_border_color.x + m_clamp_border_color.y + m_clamp_border_color.z) / 3.0;
  
  if(m_channels == 1)
    return m_texture_filtering_strategy->GetFiltering1F(pixel_coord, m_width, m_height, m_channels, m_image);
  if(m_channels == 3 || m_channels == 4){
    vec3 color = m_texture_filtering_strategy->GetFiltering3F(pixel_coord, m_width, m_height, m_channels, m_image);
    return (color.x + color.y + color.z) / 3.0f;
  }
  assert(false);
}

vec3 Texture::GetValue3F(const vec2& texture_coord){
  vec2 pixel_coord = GetPixelCoordinates(texture_coord);
  if(pixel_coord == vec2(-1.0f))
    return m_clamp_border_color;
  
  if(m_channels == 1)
    return vec3(m_texture_filtering_strategy->GetFiltering1F(pixel_coord, m_width, m_height, m_channels, m_image));
  if(m_channels == 3 || m_channels == 4)
    return m_texture_filtering_strategy->GetFiltering3F(pixel_coord, m_width, m_height, m_channels, m_image);
  
  assert(false);
}

Texture::~Texture() {
  delete [] m_image;
}

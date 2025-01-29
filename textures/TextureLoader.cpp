#include "TextureLoader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TextureData TextureLoader::Load(const char* texture_path) {
  int width, height, n_channels;
  
  TextureData texture_data;
  
  //  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load(texture_path, &width, &height, &n_channels, 0);
  if (!data) {
    std::cerr << "Failed to load texture at path: " << texture_path << '\n';
    return texture_data;
  }
  
  texture_data.image = data;
  texture_data.width = width;
  texture_data.height = height;
  texture_data.n_channels = n_channels;
  
  stbi_image_free(data);
  
  return texture_data;
}

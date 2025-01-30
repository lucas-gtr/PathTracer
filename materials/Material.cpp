#include "Material.hpp"

Material::Material() {
  SetDiffuse(vec3(0.8f));
  SetNormalMap(vec3(0.0f, 0.0f, 1.0f));
  SetMetallic(0.0f);
  SetRoughness(0.5f);
  SetOpacity(1.0f);
  m_emission_color = nullptr;
  SetEmissionIntensity(0.0f);
  SetIOR(1.0f);
}

void Material::SetDiffuse(const std::string& texture_name) {
  m_diffuse = TextureManager::instance().GetTexture(texture_name);
}

void Material::SetDiffuse(const vec3& color_rgb) {
  m_diffuse = std::make_shared<Texture>(color_rgb);
}

void Material::SetNormalMap(const std::string& texture_name) {
  m_normal_map = TextureManager::instance().GetTexture(texture_name);
}

void Material::SetNormalMap(const vec3& color_rgb) {
  m_normal_map = std::make_shared<Texture>(color_rgb);
}

void Material::SetMetallic(const std::string& texture_name) {
  m_metallic = TextureManager::instance().GetTexture(texture_name);
}

void Material::SetMetallic(const float value) {
  m_metallic = std::make_shared<Texture>(value);
}

void Material::SetRoughness(const std::string& texture_name) {
  m_roughness = TextureManager::instance().GetTexture(texture_name);
}

void Material::SetRoughness(const float value) {
  m_roughness = std::make_shared<Texture>(value);
}

void Material::SetOpacity(const std::string& texture_name) {
  m_opacity = TextureManager::instance().GetTexture(texture_name);
}

void Material::SetOpacity(const float value) {
  m_opacity = std::make_shared<Texture>(value);
}

void Material::SetEmissionColor(const std::string& texture_name) {
  m_emission_color = TextureManager::instance().GetTexture(texture_name);
}

void Material::SetEmissionColor(const vec3& color_rgb) {
  m_emission_color = std::make_shared<Texture>(color_rgb);
}

void Material::SetEmissionIntensity(const std::string& texture_name) {
  m_emission_intensity = TextureManager::instance().GetTexture(texture_name);
}

void Material::SetEmissionIntensity(const float value) {
  m_emission_intensity = std::make_shared<Texture>(value);
}

void Material::SetIOR(const std::string& texture_name) {
  m_IOR = TextureManager::instance().GetTexture(texture_name);
}

void Material::SetIOR(const float value) {
  m_IOR = std::make_shared<Texture>(value);
}

const vec3 Material::diffuse(const vec2& texture_coord) const{
  return m_diffuse->GetValue3F(texture_coord);
}

const vec3 Material::normal_map(const vec2& texture_coord) const{
  return 2 * m_normal_map->GetValue3F(texture_coord) - 1.0f;
}

const float Material::metallic(const vec2& texture_coord) const{
  return m_metallic->GetValue1F(texture_coord);
}

const float Material::roughness(const vec2& texture_coord) const{
  return m_roughness->GetValue1F(texture_coord);
}

const float Material::opacity(const vec2& texture_coord) const{
  return m_opacity->GetValue1F(texture_coord);
}

const vec3 Material::emission_color(const vec2& texture_coord) const{
  if(m_emission_color == nullptr) return diffuse(texture_coord);
  else return m_emission_color->GetValue3F(texture_coord);
}

const float Material::emission_intensity(const vec2& texture_coord) const{
  return m_emission_intensity->GetValue1F(texture_coord);
}

const float Material::IOR(const vec2& texture_coord) const{
  return m_IOR->GetValue1F(texture_coord);
}

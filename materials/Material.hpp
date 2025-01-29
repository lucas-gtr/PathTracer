#pragma once

#include "geometry.h"

#include "TextureManager.h"

class Material {
private:
  std::shared_ptr<Texture> m_diffuse;
  std::shared_ptr<Texture> m_normal_map;
  std::shared_ptr<Texture> m_metallic;
  std::shared_ptr<Texture> m_roughness;
  std::shared_ptr<Texture> m_opacity;
  std::shared_ptr<Texture> m_emission_color;
  std::shared_ptr<Texture> m_emission_intensity;
  std::shared_ptr<Texture> m_IOR;
    
public:
  Material();
  
  void SetDiffuse(const std::string& texture_name);
  void SetDiffuse(const vec3& color_rgb);
  
  void SetNormalMap(const std::string& texture_name);
  void SetNormalMap(const vec3& color_rgb);

  void SetMetallic(const std::string& texture_name);
  void SetMetallic(const float value);

  void SetRoughness(const std::string& texture_name);
  void SetRoughness(const float value);
  
  void SetOpacity(const std::string& texture_name);
  void SetOpacity(const float value);

  void SetEmissionColor(const std::string& texture_name);
  void SetEmissionColor(const vec3& color_rgb);

  void SetEmissionIntensity(const std::string& texture_name);
  void SetEmissionIntensity(const float value);

  void SetIOR(const std::string& texture_name);
  void SetIOR(const float value);

  const vec3 diffuse(const vec2& texture_coord) const;
  const vec3 normal_map(const vec2& texture_coord) const;
  const float metallic(const vec2& texture_coord) const;
  const float roughness(const vec2& texture_coord) const;
  const float opacity(const vec2& texture_coord) const;
  const vec3 emission_color(const vec2& texture_coord) const;
  const float emission_intensity(const vec2& texture_coord) const;
  const float IOR(const vec2& texture_coord) const;
};

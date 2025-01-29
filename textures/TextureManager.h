#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>
#include "Texture.hpp"

class TextureManager {
private:
  std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
  
  TextureManager() = default;
  
  TextureManager(const TextureManager&) = delete;
  TextureManager& operator=(const TextureManager&) = delete;
  
public:
  static TextureManager& instance() {
    static TextureManager texture_manager_instance;
    return texture_manager_instance;
  }
  
  std::shared_ptr<Texture> GetTexture(const std::string& name) {
    auto it = textures.find(name);
    if (it != textures.end()) {
      return it->second;
    }
    std::cout << "Texture " << name << " not found" << '\n';
    return nullptr;
  }
  
  void CreateNewTexture(const std::string& name, const std::string& file_path) {
    if (textures.find(name) != textures.end()) {
      std::cout << "Texture with this name already exists" << '\n';
      return;
    }
    textures[name] = std::make_shared<Texture>(file_path);
  }
  
  void CreateNewTexture(const std::string& name, const float value) {
    if (textures.find(name) != textures.end()) {
      std::cout << "Texture with this name already exists" << '\n';
      return;
    }
    textures[name] = std::make_shared<Texture>(value);
  }
  
  void CreateNewTexture(const std::string& name, const vec3& color_rgb) {
    if (textures.find(name) != textures.end()) {
      std::cout << "Texture with this name already exists" << '\n';
      return;
    }
    textures[name] = std::make_shared<Texture>(color_rgb);
  }
  
  void CreateNewTexture(const std::string& name, const vec4& color_rgba) {
    if (textures.find(name) != textures.end()) {
      std::cout << "Texture with this name already exists" << '\n';
      return;
    }
    textures[name] = std::make_shared<Texture>(color_rgba);
  }
};

inline void CreateNewTexture(const std::string& name, const std::string& file_path) {
  TextureManager::instance().CreateNewTexture(name, file_path);
}

inline void CreateNewTexture(const std::string& name, const float value) {
  TextureManager::instance().CreateNewTexture(name, value);
}

inline void CreateNewTexture(const std::string& name, const vec3& color_rgb) {
  TextureManager::instance().CreateNewTexture(name, color_rgb);
}

inline void CreateNewTexture(const std::string& name, const vec4& color_rgba) {
  TextureManager::instance().CreateNewTexture(name, color_rgba);
}

inline std::shared_ptr<Texture> GetTexture(const std::string& name) {
  return TextureManager::instance().GetTexture(name);
}

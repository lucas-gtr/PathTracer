#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>

#include "Material.hpp"

class MaterialManager {
private:
  std::unordered_map<std::string, std::shared_ptr<Material>> materials;
  
  MaterialManager() { CreateNewMaterial("default"); };
  
  MaterialManager(const MaterialManager&) = delete;
  MaterialManager& operator=(const MaterialManager&) = delete;
  
public:
  static MaterialManager& instance() {
    static MaterialManager material_manager_instance;
    return material_manager_instance;
  }
  
  std::shared_ptr<Material> GetMaterial(const std::string& name) {
    auto it = materials.find(name);
    if (it != materials.end()) {
      return it->second;
    }
    std::cout << "Material " << name << " not found" << '\n';
    return nullptr;
  }
  
  void CreateNewMaterial(const std::string& name) {
    if (materials.find(name) != materials.end()) {
      std::cout << "Material with the name " << name << " already exists" << '\n';
      return;
    }
    materials[name] = std::make_shared<Material>();
  }
};

inline void CreateNewMaterial(const std::string& name) {
  MaterialManager::instance().CreateNewMaterial(name);
}

inline std::shared_ptr<Material> GetMaterial(const std::string& name) {
  return MaterialManager::instance().GetMaterial(name);
}

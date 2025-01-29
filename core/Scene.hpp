#pragma once

#include <vector>
#include <memory>

#include "Sphere.hpp"
#include "Box.hpp"
#include "Triangle.hpp"
#include "Quad.hpp"
#include "Ellipse.hpp"
#include "Ring.hpp"

#include "PointLight.hpp"

#include "SceneObject.hpp"
#include "Camera.hpp"
#include "RenderObject.hpp"
#include "BVHNode.hpp"

class Scene {
private:
  std::shared_ptr<Camera> m_camera = nullptr;
  
  std::vector<std::shared_ptr<SceneObject>> m_object_list;
  std::vector<std::shared_ptr<RenderObject>> m_renderable_object_list;

public:
  Scene();
  
  const std::shared_ptr<Camera> camera() const { return m_camera; }
  const std::vector<std::shared_ptr<RenderObject>> renderable_list() const { return m_renderable_object_list; }
  
  void AddSphere(const vec3& center = vec3(0.0f), const float radius = 0.5f, std::string material="default");
  void AddBox(const vec3& center = vec3(0.0f), const vec3& scale = vec3(1.0f), std::string material="default");
  void AddQuad(const vec3& center = vec3(0.0f), const vec3& u = vec3(10.0f, 0.0f, 0.0f), const vec3& v = vec3(0.0f, 0.0f, 10.0f), std::string material="default");
  void AddEllipse(const vec3& center = vec3(0.0f), const vec3& u = vec3(1.0f, 0.0f, 0.0f), const vec3& v = vec3(0.0f, 0.0f, 1.0f), std::string material="default");
  void AddRing(const vec3& center = vec3(0.0f), const vec3& u = vec3(1.0f, 0.0f, 0.0f), const vec3& v = vec3(0.0f, 0.0f, 1.0f), float inner_radius = 0.5f, std::string material="default");
  void AddTriangle(const vec3& p1 = vec3(-0.5f, 0.0f, 0.0f), const vec3& p2 = vec3(0.0f, 0.5f, 0.0f), const vec3& p3 = vec3(0.5f, 0.0f, 0.0f), std::string material="default");
  
  void AddPointLight(const vec3& position, const float radius, const vec3& color, const float intensity);
  
  void AddObject(std::shared_ptr<RenderObject> renderable_object);
  void AddObject(std::shared_ptr<Camera> camera);
  
  void SetCamera(std::shared_ptr<Camera> camera);
};

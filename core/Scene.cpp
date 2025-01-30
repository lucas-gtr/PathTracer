#include "Scene.hpp"

Scene::Scene() { }

void Scene::AddSphere(const vec3& center, const float radius, std::string material){
  AddObject(std::make_shared<Sphere>(center, radius, material));
}

void Scene::AddBox(const vec3& center, const vec3& scale, std::string material) {
  AddObject(std::make_shared<Box>(center, scale, material));
}

void Scene::AddQuad(const vec3& center, const vec3& u, const vec3& v, std::string material) {
  AddObject(std::make_shared<Quad>(center, u, v, material));
}

void Scene::AddEllipse(const vec3& center, const vec3& u, const vec3& v, std::string material) {
  AddObject(std::make_shared<Ellipse>(center, u, v, material));
}

void Scene::AddRing(const vec3& center, const vec3& u, const vec3& v, float inner_radius, std::string material) {
  AddObject(std::make_shared<Ring>(center, u, v, inner_radius, material));
}

void Scene::AddTriangle(const vec3& p1, const vec3& p2, const vec3& p3, std::string material) {
  AddObject(std::make_shared<Triangle>(p1, p2, p3, material));
}

void Scene::AddPointLight(const vec3& position, const float radius, const vec3& color, const float intensity) {
  AddObject(std::make_shared<PointLight>(position, radius, color, intensity));
}

void Scene::AddObject(std::shared_ptr<Box> box) {
  for (auto& quad : box->quad_list) {
    m_renderable_object_list.push_back(quad);
    m_object_list.push_back(quad);
  }
}

void Scene::AddObject(std::shared_ptr<RenderObject> renderable_object) {
  m_renderable_object_list.push_back(renderable_object);
  m_object_list.push_back(renderable_object);
}

void Scene::AddObject(std::shared_ptr<Camera> camera) {
  m_object_list.push_back(camera);
  if(m_camera == nullptr) SetCamera(camera);
}

void Scene::SetCamera(std::shared_ptr<Camera> camera) {
  m_camera = camera;
}



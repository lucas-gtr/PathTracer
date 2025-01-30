#include "Box.hpp"

#include <sys/time.h>

Box::Box(const vec3& center, const vec3& scale, const std::string& material_name) : VisibleObject(vec3(0.0f), vec3(0.0f), scale, material_name) {
  vec3 half_extents = scale * 0.5f;
  // Front face
  quad_list[0] = std::make_shared<Quad>(vec3(0.0f, 0.0f, half_extents.z),
                                        vec3(scale.x, 0.0f, 0.0f),
                                        vec3(0.0f, scale.y, 0.0f),
                                        material_name);
  // Back face
  quad_list[1] = std::make_shared<Quad>(vec3(0.0f, 0.0f, -half_extents.z),
                                        vec3(scale.x, 0.0f, 0.0f),
                                        vec3(0.0f, scale.y, 0.0f),
                                        material_name);
  // Top face
  quad_list[2] = std::make_shared<Quad>(vec3(0.0f, half_extents.y, 0.0f),
                                        vec3(scale.x, 0.0f, 0.0f),
                                        vec3(0.0f, 0.0f, scale.z),
                                        material_name);
  // Bottom face
  quad_list[3] = std::make_shared<Quad>(vec3(0.0f, -half_extents.y, 0.0f),
                                        vec3(scale.x, 0.0f, 0.0f),
                                        vec3(0.0f, 0.0f, scale.z),
                                        material_name);
  // Right face
  quad_list[4] = std::make_shared<Quad>(vec3(half_extents.x, 0.0f, 0.0f),
                                        vec3(0.0f, scale.y, 0.0f),
                                        vec3(0.0f, 0.0f, scale.z),
                                        material_name);
  // Left face
  quad_list[5] = std::make_shared<Quad>(vec3(-half_extents.x, 0.0f, 0.0f),
                                        vec3(0.0f, scale.y, 0.0f),
                                        vec3(0.0f, 0.0f, scale.z),
                                        material_name);
  for(auto quad : quad_list){
    quad->SetPosition(center);
    quad->SetupShape();
  }
  SetBBox();
}

void Box::SetBBox(){
  m_bbox = BBox(quad_list[0]->bbox(), quad_list[1]->bbox());
}

void Box::SetRotation(const vec3 &rotation){
  for(auto quad : quad_list){
    quad->SetRotation(rotation);
  }
  
  SetBBox();
}

const bool Box::hit(Ray& ray) const {
  bool hit_one_quad = false;
  for(auto quad : quad_list){
    if(quad->hit(ray)) hit_one_quad = true;
  }
  
  return hit_one_quad;
}


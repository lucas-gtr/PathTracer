#include "Shape2D.hpp"

Shape2D::Shape2D(const vec3& shape_center, const vec3& u, const vec3& v, const std::string& material_name) : VisibleObject(vec3(0.0f), vec3(0.0f), vec3(1.0f), material_name) {
  if(dot(u.normalized(), v.normalized()) == 1.0f){
    std::cerr << "Couldn't build the 2D Shape : vector u and v are collinear" << '\n';
    return;
  }
  m_shape_center = shape_center;
  
  m_u = u;
  m_v = v;
  
  SetupShape();
}

void Shape2D::SetupShape() {
  m_normal = vec_cross(m_u, m_v);
  m_normal_weight = m_normal / (m_normal.length() * m_normal.length());
  
  m_normal.normalize();
  intersection_constant = dot(m_normal, m_shape_center + m_position);
  
  SetBBox();
}

void Shape2D::SetRotation(const vec3& rotation){
  mat4 rotation_mat = mat4(1.0f);

  rotation_mat.rotate(rotation);
  
  m_shape_center = vec3(rotation_mat * vec4(m_shape_center, 1.0f));
  m_u = vec3(rotation_mat * vec4(m_u, 1.0f));
  m_v = vec3(rotation_mat * vec4(m_v, 1.0f));
    
  SetupShape();
}

void Shape2D::SetBBox() {
  BBox bbox_diagonal1 = BBox(m_shape_center + m_position - (m_u + m_v) / 2.0, m_shape_center + m_position + (m_u + m_v) / 2.0);
  BBox bbox_diagonal2 = BBox(m_shape_center + m_position - (m_u - m_v) / 2.0, m_shape_center + m_position + (m_u - m_v) / 2.0);
  m_bbox = BBox(bbox_diagonal1, bbox_diagonal2);
}

const bool Shape2D::CheckRayCollision(Ray& ray) const {
  auto denom = dot(m_normal, ray.direction());
  
  if (std::fabs(denom) < 1e-8) return false;
  
  float dist = (intersection_constant - dot(m_normal, ray.origin())) / denom;
  if(ray.IsDistanceOutOfBounds(dist)) return false;
  
  const vec3& intersection_point = ray.origin() + dist * ray.direction();
  vec3 planar_hitpt_vector = intersection_point - (m_shape_center + m_position);
  float alpha = dot(m_normal_weight, vec_cross(planar_hitpt_vector, m_v));
  float beta = dot(m_normal_weight, vec_cross(m_u, planar_hitpt_vector));
  
  if(!IsInShape(alpha, beta)) return false;
  
  ray.RecordIntersection(intersection_point, dist);
  return true;
}

const vec3 Shape2D::GetHitNormal(const HitRecord& hit_record) const {
  return m_normal;
}

const vec2 Shape2D::GetTextureCoord(const HitRecord& hit_record) const {
  vec3 planar_hitpt_vector = hit_record.intersection_point - (m_shape_center + m_position - (m_u + m_v) / 2.0);
  float alpha = dot(m_normal_weight, vec_cross(planar_hitpt_vector, m_v));
  float beta = dot(m_normal_weight, vec_cross(m_u, planar_hitpt_vector));
  
  return vec2(alpha, 1.0 - beta);
}

#pragma once

#include "SceneObject.hpp"
#include "BoundingBox.hpp"

class HittableObject : public SceneObject {
protected:
  BBox m_bbox;
  
public:
  HittableObject(const vec3& position = vec3(0.0f), const vec3& rotation = vec3(0.0f), const vec3& scale = vec3(1.0f));
  
  const BBox& bbox() const { return m_bbox; }
  
  static bool bbox_compare(const std::shared_ptr<HittableObject> a, const std::shared_ptr<HittableObject> b, int axis) {
    float box_a_min = a->m_bbox.axis_bounds()[0][axis];
    float box_b_min = b->m_bbox.axis_bounds()[0][axis];
    return box_a_min < box_b_min;
  }
  
  static bool bbox_compare_x (const std::shared_ptr<HittableObject> a, const std::shared_ptr<HittableObject> b) {
    return bbox_compare(a, b, 0);
  }
  
  static bool bbox_compare_y (const std::shared_ptr<HittableObject> a, const std::shared_ptr<HittableObject> b) {
    return bbox_compare(a, b, 1);
  }
  
  static bool bbox_compare_z (const std::shared_ptr<HittableObject> a, const std::shared_ptr<HittableObject> b) {
    return bbox_compare(a, b, 2);
  }
  
  virtual const bool hit(Ray& ray) const = 0;
};

#pragma once

#include <vector>

#include "RenderObject.hpp"

class BVHNode : public HittableObject {
private:
  std::shared_ptr<HittableObject> m_left_node;
  std::shared_ptr<HittableObject> m_right_node;
  
public:
  BVHNode(std::vector<std::shared_ptr<RenderObject>> object_list);
  BVHNode(std::vector<std::shared_ptr<RenderObject>>& object_list, size_t start, size_t end);
  
  const bool hit(Ray& ray) const override;
};

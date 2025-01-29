#include "BVHNode.hpp"

BVHNode::BVHNode(std::vector<std::shared_ptr<RenderObject>> object_list) : BVHNode(object_list, 0, object_list.size()){
}

BVHNode::BVHNode(std::vector<std::shared_ptr<RenderObject>>& object_list, size_t start, size_t end){
  
  BBox list_bbox = BBox();
  for (size_t i=start; i < end; i++) list_bbox = BBox(list_bbox, object_list[i]->bbox());
  int axis = list_bbox.longest_axis();
    
  size_t bbox_object_count = end - start;
  if (bbox_object_count == 1) m_left_node = m_right_node = object_list[start];
  else if (bbox_object_count == 2) {
    m_left_node = object_list[start];
    m_right_node = object_list[start+1];
  } else {
    auto comparator = (axis == 0) ? bbox_compare_x : (axis == 1) ? bbox_compare_y : bbox_compare_z;
    std::sort(std::begin(object_list) + start, std::begin(object_list) + end, comparator);
    
    size_t mid = start + bbox_object_count/2;
    m_left_node = std::make_shared<BVHNode>(object_list, start, mid);
    m_right_node = std::make_shared<BVHNode>(object_list, mid, end);
  }
  m_bbox = BBox(m_left_node->bbox(), m_right_node->bbox());
}

const bool BVHNode::hit(Ray& ray) const {
  if(!m_bbox.hit(ray)) return false;
  
  // Make sure both nodes are tested
  bool right_node_hit = m_right_node->hit(ray);
  bool left_node_hit = m_left_node->hit(ray);
  return right_node_hit || left_node_hit;
}

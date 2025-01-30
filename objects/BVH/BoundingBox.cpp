#include "BoundingBox.hpp"

BBox::BBox() { }

BBox::BBox(vec3 bounds1, vec3 bounds2){
  for(int axis = 0; axis < 3; axis++){
    m_axis_bounds[0][axis] = std::min(bounds1[axis], bounds2[axis]) - epsilon;
    m_axis_bounds[1][axis] = std::max(bounds1[axis], bounds2[axis]) + epsilon;
  }
}

BBox::BBox(BBox bbox1, BBox bbox2){
  for(int axis = 0; axis < 3; axis++){
    m_axis_bounds[0][axis] = std::min(bbox1.m_axis_bounds[0][axis], bbox2.m_axis_bounds[0][axis]) - epsilon;
    m_axis_bounds[1][axis] = std::max(bbox1.m_axis_bounds[1][axis], bbox2.m_axis_bounds[1][axis]) + epsilon;
  }
}

const int BBox::longest_axis() const {
  float x_size = m_axis_bounds[1][0] - m_axis_bounds[0][0];
  float y_size = m_axis_bounds[1][1] - m_axis_bounds[0][1];
  float z_size = m_axis_bounds[1][2] - m_axis_bounds[0][2];
  
  if (x_size > y_size)
    return x_size > z_size ? 0 : 2;
  else
    return y_size > z_size ? 1 : 2;
}

const bool BBox::hit(Ray& ray) const {
  float min_dist = ray.min_distance();
  float max_dist = ray.max_distance();
  
  for (int axis = 0; axis < 3; axis++) {
    const float min = m_axis_bounds[0][axis];
    const float max = m_axis_bounds[1][axis];
    const float inv_dir = 1.0 / ray.direction()[axis];
        
    float t0 = (min - ray.origin()[axis]) * inv_dir;
    float t1 = (max - ray.origin()[axis]) * inv_dir;
    
    if (t0 < t1) {
      if (t0 > min_dist) min_dist = t0;
      if (t1 < max_dist) max_dist = t1;
    } else {
      if (t1 > min_dist) min_dist = t1;
      if (t0 < max_dist) max_dist = t0;
    }
    
    if (max_dist <= min_dist) {      
      return false;
    }
  }
  return true;
}


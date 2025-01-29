#pragma once

#include "geometry.h"

class IToneMappingStrategy {
public:
  virtual ~IToneMappingStrategy() = default;
  virtual void GetColorLDR(vec3& hdr_color) const = 0;
};

class ToneMappingNone : public IToneMappingStrategy {
public:
  virtual void GetColorLDR(vec3& hdr_color) const override;
};

class ToneMappingReinhard : public IToneMappingStrategy {
public:
  virtual void GetColorLDR(vec3& hdr_color) const override;
};

class ToneMappingExposure : public IToneMappingStrategy {
private:
  float m_exposure;
  
public:
  ToneMappingExposure(float exposure) : m_exposure(exposure) { }
  
  virtual void GetColorLDR(vec3& hdr_color) const override;
};

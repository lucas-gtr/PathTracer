#include "ToneMappingStrategy.hpp"

void ToneMappingNone::GetColorLDR(vec3& hdr_color) const {
  hdr_color = hdr_color.clamped(0.0f, 1.0f);
}

void ToneMappingReinhard::GetColorLDR(vec3& hdr_color) const {
    hdr_color /= (hdr_color + vec3(1.0f));
  }

void ToneMappingExposure::GetColorLDR(vec3& hdr_color) const {
  for(int i = 0; i < 3; i++)
    hdr_color[i] = 1.0f - std::exp(-hdr_color[i] * m_exposure);
}

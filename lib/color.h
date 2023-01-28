#ifndef CVS_LIB_COLOR_H_
#define CVS_LIB_COLOR_H_

#include <algorithm>
#include <cstdint>

namespace cvs {

struct BGRA {
  uint8_t b;
  uint8_t g;
  uint8_t r;
  uint8_t a;
};

inline float ToLinearRGB(uint8_t v) {
  float fv = v / 255.f;
  if (fv < 0.04045f) return fv / 12.92f;
  return pow((fv + 0.055f) / 1.055f, 2.4f);
}

inline uint8_t ToSRGB(float v) {
  if (v <= 0.f) return 0;
  if (v >= 1.f) return 255;
  int x;
  if (v < 0.0031308f)
    x = (int)(0.5f + (v * 12.92f * 255.f));
  else
    x = (int)(0.f + 255.f * (powf(v, 1.f / 2.4f) * 1.055f - 0.055f));
  return std::clamp(x, 0, 255);
}

}  // namespace cvs

#endif  // CVS_LIB_COLOR_H_

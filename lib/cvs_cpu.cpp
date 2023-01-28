#include "cvs_cpu.h"

#include <omp.h>

namespace cvs {

inline float dot(const float a[3], const float b[3]) {
  return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

inline float mix(float a, float b, float rate) { return a + (b - a) * rate; }

void SimulateCPU(ColorVisionType type, float severity, BGRA* image,
                 size_t len) {
  switch (type) {
    case ColorVisionType::Protan:
    case ColorVisionType::Deutan:
      SimulateBrettel1997CPU(type, severity, image, len);
      break;
    case ColorVisionType::Tritan:
      SimulateVienot1999CPU(type, severity, image, len);
      break;
  }
}

void SimulateBrettel1997CPU(ColorVisionType type, float severity, BGRA* image,
                            size_t len) {
  const auto params = Brettel1997Params::Get(type);

#pragma omp parallel for
  for (int i = 0; i < len; i++) {
    const float bgr[3]{
        ToLinearRGB(image[i].b),
        ToLinearRGB(image[i].g),
        ToLinearRGB(image[i].r),
    };

    const float x = dot(params->normal, bgr);
    const auto mat = x >= 0 ? params->mat1 : params->mat2;

    float bgr_sim[3]{dot(bgr, mat[0]), dot(bgr, mat[1]), dot(bgr, mat[2])};

    image[i].b = ToSRGB(mix(bgr[0], bgr_sim[0], severity));
    image[i].g = ToSRGB(mix(bgr[1], bgr_sim[1], severity));
    image[i].r = ToSRGB(mix(bgr[2], bgr_sim[2], severity));
  }
}

void SimulateVienot1999CPU(ColorVisionType type, float severity, BGRA* image,
                           size_t len) {
  const auto params = Vienot1999Params::Get(type);

#pragma omp parallel for
  for (int i = 0; i < len; i++) {
    const float bgr[3]{
        ToLinearRGB(image[i].b),
        ToLinearRGB(image[i].g),
        ToLinearRGB(image[i].r),
    };
    float bgr_sim[3]{
        dot(bgr, params->mat[0]),
        dot(bgr, params->mat[1]),
        dot(bgr, params->mat[2]),
    };

    image[i].b = ToSRGB(mix(bgr[0], bgr_sim[0], severity));
    image[i].g = ToSRGB(mix(bgr[1], bgr_sim[1], severity));
    image[i].r = ToSRGB(mix(bgr[2], bgr_sim[2], severity));
  }
}

}  // namespace cvs

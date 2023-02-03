#ifndef CL_KERNEL_SOURCE
#define CL_KERNEL_SOURCE(x) x
#endif // CL_KERNEL_SOURCE

CL_KERNEL_SOURCE(

inline float3 ToLinearRGB(uchar3 v) {
  float3 fv = convert_float3(v) / 255.f;
  float3 cutoff = convert_float3(isless(fv, (float3)0.04045f));
  float3 low = fv / 12.92f;
  float3 high = powr((fv + 0.055f) / 1.055f, 2.4f);
  return mix(high, low, cutoff);
}

inline uchar3 ToSRGB(float3 v) {
  float3 cutoff = convert_float3(isless(v, (float3)0.0031308f));
  float3 low = v * 12.92f;
  float3 high = pow(v, 1.f / 2.4f) * 1.055f - 0.055f;
  float3 srgb = clamp(mix(high, low, cutoff) * 255.f, 0.f, 255.f);
  return convert_uchar3(srgb);
}

__kernel void Brettel1997(
    __global uchar4 *image,
    __constant float *params,
    const float severity) {
  size_t i = get_global_id(0);
  float3 bgr = ToLinearRGB(image[i].xyz);

  float x = dot(bgr.xyz, vload3(6, params));
  int offset = isless(x, 0) * 3;
  float3 bgr_cvd = (float3)(
      dot(bgr, vload3(offset + 0, params)),
      dot(bgr, vload3(offset + 1, params)),
      dot(bgr, vload3(offset + 2, params))
  );

  image[i].xyz = ToSRGB(mix(bgr, bgr_cvd, severity));
}

__kernel void Vienot1999(
    __global uchar4* image,
    __constant float* mat,
    const float severity) {
  size_t i = get_global_id(0);
  float3 bgr = ToLinearRGB(image[i].xyz);

  float3 bgr_cvd = (float3)(
      dot(bgr, vload3(0, mat)),
      dot(bgr, vload3(1, mat)),
      dot(bgr, vload3(2, mat))
  );

  image[i].xyz = ToSRGB(mix(bgr, bgr_cvd, severity));
}

__kernel void GrayCIEXYZ(
    __global uchar4* image,
    const float severity) {
  size_t i = get_global_id(0);
  float3 bgr = ToLinearRGB(image[i].xyz);
  float y = 0.2126 * bgr.z + 0.7152 * bgr.y + 0.0722 * bgr.x;
  image[i].xyz = ToSRGB(mix(bgr, (float3)y, severity));
}

)

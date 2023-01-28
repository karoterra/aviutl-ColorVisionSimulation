#ifndef CL_KERNEL_SOURCE
#define CL_KERNEL_SOURCE(x) x
#endif // CL_KERNEL_SOURCE

CL_KERNEL_SOURCE(

inline float4 ToLinearRGB(uchar4 v) {
  float4 fv = convert_float4(v) / 255.f;
  float4 cutoff = convert_float4(isless(fv, (float4)0.04045f));
  float4 low = fv / 12.92f;
  float4 high = powr((fv + 0.055f) / 1.055f, 2.4f);
  return mix(high, low, cutoff);
}

inline uchar4 ToSRGB(float4 v) {
  float4 cutoff = convert_float4(isless(v, (float4)0.0031308f));
  float4 low = v * 12.92f;
  float4 high = pow(v, 1.f / 2.4f) * 1.055f - 0.055f;
  float4 srgb = clamp(mix(high, low, cutoff) * 255.f, 0.f, 255.f);
  return convert_uchar4(srgb);
}

__kernel void Brettel1997(
    __global uchar4 *image,
    __constant float *params,
    const float severity) {
  size_t i = get_global_id(0);
  float4 bgra = ToLinearRGB(image[i]);

  float x = dot(bgra.xyz, vload3(6, params));
  int offset = isless(x, 0) * 3;
  float4 bgra_cvd = (float4)(
      dot(bgra.xyz, vload3(offset + 0, params)),
      dot(bgra.xyz, vload3(offset + 1, params)),
      dot(bgra.xyz, vload3(offset + 2, params)),
      bgra.w
  );

  image[i] = ToSRGB(mix(bgra, bgra_cvd, severity));
}

__kernel void Vienot1999(
    __global uchar4* image,
    __constant float* mat,
    const float severity) {
  size_t i = get_global_id(0);
  float4 bgra = ToLinearRGB(image[i]);

  float4 bgra_cvd = (float4)(
      dot(bgra.xyz, vload3(0, mat)),
      dot(bgra.xyz, vload3(1, mat)),
      dot(bgra.xyz, vload3(2, mat)),
      bgra.w
  );

  image[i] = ToSRGB(mix(bgra, bgra_cvd, severity));
}

)

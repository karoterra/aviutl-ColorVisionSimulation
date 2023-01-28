#ifndef CVS_LIB_CVS_CPU_H_
#define CVS_LIB_CVS_CPU_H_

#include "color.h"
#include "cvs_params.h"

namespace cvs {

void SimulateCPU(ColorVisionType type, float severity, BGRA* image, size_t len);

void SimulateBrettel1997CPU(ColorVisionType type, float severity, BGRA* image,
                            size_t len);

void SimulateVienot1999CPU(ColorVisionType type, float severity, BGRA* image,
                           size_t len);

}  // namespace cvs

#endif  // CVS_LIB_CVS_CPU_H_

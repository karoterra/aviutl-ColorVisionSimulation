#ifndef CVS_LIB_CVS_CL_H_
#define CVS_LIB_CVS_CL_H_

#include "color.h"
#include "cvs_params.h"

namespace cvs {

void SimulateCL(ColorVisionType type, float severity, BGRA* image, size_t len);

void SimulateBrettel1997CL(ColorVisionType type, float severity, BGRA* image,
                           size_t len);

void SimulateVienot1999CL(ColorVisionType type, float severity, BGRA* image,
                          size_t len);

}  // namespace cvs

#endif  // CVS_LIB_CVS_CL_H_

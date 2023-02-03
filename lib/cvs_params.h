#ifndef CVS_LIB_CVS_PARAMS_H_
#define CVS_LIB_CVS_PARAMS_H_

namespace cvs {

enum class ColorVisionType {
  Common,
  Protan,
  Deutan,
  Tritan,
  Achromat,
};

struct Brettel1997Params {
  float mat1[3][3];
  float mat2[3][3];
  float normal[3];

  static const Brettel1997Params* Get(ColorVisionType type);
};

extern const Brettel1997Params kBrettel1997ProtanParams;
extern const Brettel1997Params kBrettel1997DeutanParams;
extern const Brettel1997Params kBrettel1997TritanParams;

struct Vienot1999Params {
  float mat[3][3];

  static const Vienot1999Params* Get(ColorVisionType type);
};

extern const Vienot1999Params kVienot1999ProtanParams;
extern const Vienot1999Params kVienot1999DeutanParams;
extern const Vienot1999Params kVienot1999TritanParams;

inline ColorVisionType ToColorVisionType(int type) {
  switch (type) {
    case 1:
      return ColorVisionType::Protan;
    case 2:
      return ColorVisionType::Deutan;
    case 3:
      return ColorVisionType::Tritan;
    case 4:
      return ColorVisionType::Achromat;
  }
  return ColorVisionType::Common;
}

inline const Brettel1997Params* Brettel1997Params::Get(ColorVisionType type) {
  switch (type) {
    case ColorVisionType::Protan:
      return &kBrettel1997ProtanParams;
    case ColorVisionType::Deutan:
      return &kBrettel1997DeutanParams;
    case ColorVisionType::Tritan:
      return &kBrettel1997TritanParams;
  }
  return nullptr;
}

inline const Vienot1999Params* Vienot1999Params::Get(ColorVisionType type) {
  switch (type) {
    case ColorVisionType::Protan:
      return &kVienot1999ProtanParams;
    case ColorVisionType::Deutan:
      return &kVienot1999DeutanParams;
    case ColorVisionType::Tritan:
      return &kVienot1999TritanParams;
  }
  return nullptr;
}

}  // namespace cvs

#endif  // CVS_LIB_CVS_PARAMS_H_

#include "cvs_params.h"

namespace cvs {

const Brettel1997Params kBrettel1997ProtanParams{
    .mat1{
        {1.00156, -0.00540, 0.00384},
        {0.04372, 0.84864, 0.10764},
        {-0.34528, 1.19548, 0.14980},
    },
    .mat2{
        {1.00139, -0.00524, 0.00386},
        {0.03892, 0.85291, 0.10816},
        {-0.30742, 1.16172, 0.14570},
    },
    .normal{-0.00441, 0.00393, 0.00048},
};
const Brettel1997Params kBrettel1997DeutanParams{
    .mat1{
        {0.99278, 0.02728, -0.02006},
        {0.09462, 0.64245, 0.26294},
        {-0.22858, 0.86381, 0.36477},
    },
    .mat2{
        {0.99196, 0.02784, -0.01980},
        {0.10540, 0.63506, 0.25954},
        {-0.25464, 0.88166, 0.37298},
    },
    .normal{0.00892, -0.00611, -0.00281},
};
const Brettel1997Params kBrettel1997TritanParams{
    .mat1{
        {0.11911, 0.80500, 0.07589},
        {0.14431, 0.86812, -0.01243},
        {-0.14826, 0.13548, 1.01277},
    },
    .mat2{
        {0.24796, 1.12767, -0.37562},
        {0.12320, 0.81526, 0.06154},
        {-0.12657, 0.18979, 0.93678},
    },
    .normal{-0.01113, -0.02788, 0.03901},
};

const Vienot1999Params kVienot1999ProtanParams{{
    {1.00000, -0.00401, 0.00401},
    {-0.00000, 0.88762, 0.11238},
    {0.00000, 0.88762, 0.11238},
}};
const Vienot1999Params kVienot1999DeutanParams{{
    {1.00000, 0.02234, -0.02234},
    {-0.00000, 0.70725, 0.29275},
    {0.00000, 0.70725, 0.29275},
}};
const Vienot1999Params kVienot1999TritanParams{{
    {0.14076, 0.85924, -0.00000},
    {0.14076, 0.85924, 0.00000},
    {-0.14461, 0.14461, 1.00000},
}};

}  // namespace cvs

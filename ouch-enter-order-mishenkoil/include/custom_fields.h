//
// Created by mishenkoil on 12.04.2020.
//

#pragma once
#include "custom_codec.h"
#include <cmath>

inline unsigned char * custom_encode_text(unsigned char * start, const std::string & str, const size_t field_size)
{
    return custom_encode(start, str, field_size);
}

inline unsigned char * custom_encode_char(unsigned char * start, const char ch)
{
    return custom_encode(start, static_cast<const uint8_t>(ch));
}

inline unsigned char * custom_encode_binary4(unsigned char * start, const uint32_t value)
{
    return custom_encode(start, value);
}

inline unsigned char * custom_encode_price(unsigned char * start, const double value)
{
    const double order = 10000;
    const double epsilon = 1e-5;
    // beware: no precision loss check
    return custom_encode(start, static_cast<int32_t>(value * order + std::copysign(epsilon, value)));
}

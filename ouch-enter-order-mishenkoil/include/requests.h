#pragma once

#include "custom_fields.h"
#include "fields.h"

#include <cstddef>
#include <vector>
#include <string>
#include <array>
#include <algorithm>

enum class RequestType {
    /*EnterOrder*/
    New
};

constexpr size_t new_order_bitfield_num()
{
    return 4;
}

constexpr size_t new_order_opt_fields_size()
{
    return 0
           #define FIELD(name, _, __) + name##_field_size
           #include "new_order_opt_fields.inl"
            ;
}

constexpr size_t calculate_size(const RequestType type)
{
    switch (type) {
        case RequestType::New:
            return 38 + new_order_bitfield_num() + new_order_opt_fields_size();
        default:
            return 38 + new_order_bitfield_num();
    }
}

enum class Side {
    Buy,
    Sell
};

enum class OrdType {
    Market,
    Limit
};

enum class TimeInForce {
    Day,
    IOC
};

enum class Capacity {
    Agency,
    Principal,
    RisklessPrincipal
};

std::vector<unsigned char> create_enter_order_request(
  const std::string & cl_ord_id,
  Side side,
  double volume,
  double price,
  const std::string & symbol,
  OrdType ord_type,
  TimeInForce time_in_force,
  Capacity capacity,
  const std::string & firm,
  const std::string & user
);
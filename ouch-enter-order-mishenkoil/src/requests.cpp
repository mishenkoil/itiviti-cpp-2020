#include "requests.h"

#include <string>

namespace {

    void encode_new_order_opt_fields(unsigned char * bitfield_start,
                                     const char time_in_force,
                                     const char capacity)
    {
        auto * p = bitfield_start + new_order_bitfield_num();
#define FIELD(name, bitfield_num, bit) \
    set_opt_field_bit(bitfield_start, bitfield_num, bit); \
    p = encode_field_##name(p, name);
#include "new_order_opt_fields.inl"
    }

    unsigned char * set_custom_price(unsigned char * start)
    {
        *start++ = 0x7F;
        *start++ = 0xFF;
        *start++ = 0xFF;
        *start++ = 0xFF;
        return start;
    }

    unsigned char * add_request_header(unsigned char * start/*, unsigned length, const RequestType type, unsigned seq_no */)
    {
        *start++ = 0x4F;
        return start;
    }

    char convert_side(const Side side)
    {
        switch (side) {
            case Side::Buy: return 'B';
            case Side::Sell: return 'S';
        }
        return 0;
    }

    char convert_time_in_force(const TimeInForce time_in_force)
    {
        switch (time_in_force) {
            case TimeInForce::Day: return '0';
            case TimeInForce::IOC: return '3';
        }
        return 0;
    }

    char convert_capacity(const Capacity capacity)
    {
        switch (capacity) {
            case Capacity::Agency: return '1';
            case Capacity::Principal: return '2';
            case Capacity::RisklessPrincipal: return '7';
        }
        return 0;
    }

} // anonymous namespace

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
)
{
    //   static_assert(calculate_size(RequestType::New) == 78, "Wrong New Order message size");

    std::vector<unsigned char> msg(calculate_size(RequestType::New), 0x00);
    auto * p = add_request_header(&msg[0]/*, msg.size() - 2, RequestType::New, seq_no */);
    p = custom_encode_text(p, cl_ord_id, 14);
    p = custom_encode_char(p, convert_side(side));
    p = custom_encode_binary4(p, static_cast<uint32_t>(volume)); /* Quantity */
    p = custom_encode_binary4(p, static_cast<uint32_t>(std::stoll(symbol))); /* Order Book */
    if (ord_type == OrdType::Limit) {
        p = custom_encode_price(p, price); /* Price */
    } else {
        p = set_custom_price(p); /* Price */
    }
    p = custom_encode_text(p, firm, 4); /* Firm */
    p = custom_encode_text(p, user, 6); /* User */

    encode_new_order_opt_fields(p,
                                convert_time_in_force(time_in_force),
                                convert_capacity(capacity));

    return msg;
}
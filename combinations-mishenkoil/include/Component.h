#pragma once

#include <ctime>
#include <istream>
#include <string>

enum class InstrumentType : char {
    C = 'C',
    F = 'F',
    O = 'O',
    P = 'P',
    U = 'U',
    Unknown = '\0'
};

struct Component {
    static Component from_stream(std::istream &);

    static Component from_string(const std::string &);

    char get_type() const {
        switch (type) {
            case InstrumentType::C:
                return 'C';
            case InstrumentType::O:
                return 'O';
            case InstrumentType::P:
                return 'P';
            case InstrumentType::F:
                return 'F';
            case InstrumentType::U:
                return 'U';
            case InstrumentType::Unknown:
                return '\0';
            default:
                return {};
        }
    }

    InstrumentType type{InstrumentType::Unknown};
    double ratio{0};
    double strike{0};
    std::tm expiration{};
};


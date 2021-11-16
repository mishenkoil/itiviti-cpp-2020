//
// Created by mishenkoil on 13.06.2020.
//

#pragma once

#include <string>
#include <iostream>
#include <pugixml.hpp>
#include <variant>

enum class ExpirationOffsetType {
    Plus,
    Minus,
    Day,
    Month,
    Quarter,
    Year
};

struct XML_component {
    explicit XML_component(pugi::xml_node & comp) {
        type = comp.attribute("type").value()[0];

        std::string tmp_ratio = comp.attribute("ratio").value();
        if (tmp_ratio.back() == '+' || tmp_ratio.back() == '-') {
            ratio = tmp_ratio.back();
        } else {
            ratio = atof(tmp_ratio.c_str());
        }

        if (comp.attribute("expiration")) {
            expiration = comp.attribute("expiration").value()[0];
        }
        if (comp.attribute("expiration_offset")) {
            std::string tmp = comp.attribute("expiration_offset").value();
            switch (tmp.back()) {
                case '+':
                    expiration_offset = tmp.size();
                    expiration_offset_type = ExpirationOffsetType::Plus;
                    break;
                case '-':
                    expiration_offset = tmp.size();
                    expiration_offset_type = ExpirationOffsetType::Minus;
                    break;
                case 'd':
                    expiration_offset = 1;
                    if (tmp.size() > 1) {
                        expiration_offset = stoi(tmp.substr(0,tmp.size() - 1));
                    }
                    expiration_offset_type = ExpirationOffsetType::Day;
                    break;
                case 'm':
                    expiration_offset = 1;
                    if (tmp.size() > 1) {
                        expiration_offset = stoi(tmp.substr(0,tmp.size() - 1));
                    }
                    expiration_offset_type = ExpirationOffsetType::Month;
                    break;
                case 'q':
                    expiration_offset = 1;
                    if (tmp.size() > 1) {
                        expiration_offset = stoi(tmp.substr(0,tmp.size() - 1));
                    }
                    expiration_offset_type = ExpirationOffsetType::Quarter;
                    break;
                case 'y':
                    expiration_offset = 1;
                    if (tmp.size() > 1) {
                        expiration_offset = stoi(tmp.substr(0,tmp.size() - 1));
                    }
                    expiration_offset_type = ExpirationOffsetType::Year;
                    break;
            }
        }
        if (comp.attribute("strike")) {
            strike = comp.attribute("strike").value()[0];
        }
        if (comp.attribute("strike_offset")) {
            std::string tmp = comp.attribute("strike_offset").value();
            if (tmp[0] == '+') {
                strike_offset = tmp.size();
            }
            else {
                strike_offset = -tmp.size();
            }
        }
    }

    void print() {
        std::cout << "type: " << type << " ratio: " << *std::get_if<char>(&ratio) << *std::get_if<double >(&ratio);
        if (expiration)
            std::cout << " expiration: " << expiration;
        if (expiration_offset)
            std::cout << " expiration_offset: " << expiration_offset;
        if (strike)
            std::cout << " strike: " << strike;
        if (strike_offset)
            std::cout << " strike_offset: " << strike_offset;
        std::cout << std::endl;
    }

    char type;
    std::variant<double, char> ratio;
    char expiration = '\0';
    int expiration_offset = 0;
    ExpirationOffsetType expiration_offset_type;
    char strike = '\0';
    int strike_offset = 0;
};

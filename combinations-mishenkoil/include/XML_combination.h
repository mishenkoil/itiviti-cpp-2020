//
// Created by mishenkoil on 13.06.2020.
//

#pragma once

#include <vector>
#include "XML_component.h"

enum class CardinalityType {
    Fixed,
    Multiple,
    More
};


struct XML_combination {
    std::string name;
    std::string shortname;
    std::string identifier;
    CardinalityType cardinality;
    size_t mincount;
    std::vector<XML_component> components;

    void set_cardinality(pugi::xml_node & node) {
        if (static_cast<std::string> (node.child("legs").attribute("cardinality").value()) == "fixed") {
            cardinality = CardinalityType::Fixed;
        }
        else if (static_cast<std::string> (node.child("legs").attribute("cardinality").value()) == "multiple") {
            cardinality = CardinalityType::Multiple;
        }
        else if (static_cast<std::string> (node.child("legs").attribute("cardinality").value()) == "more") {
            cardinality = CardinalityType::More;
            mincount = atoi(node.child("legs").attribute("mincount").value());
        }
        else {
            std::abort();
        }
    }
};


#pragma once

#include "XML_combination.h"
#include <filesystem>
#include <string>
#include <vector>
#include <iostream>

struct Component;

class Combinations
{
public:
    Combinations() = default;

    bool load(const std::filesystem::path & resource);

    std::string classify(const std::vector<Component> & components, std::vector<int> & order) const;

private:
    // implementation details
    std::vector<XML_combination> xml_combinations;
};


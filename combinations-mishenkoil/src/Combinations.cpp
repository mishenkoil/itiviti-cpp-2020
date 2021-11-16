#include <pugixml.hpp>
#include <string>
#include <set>
#include <algorithm>
#include <unordered_map>
#include "Combinations.h"
#include "Component.h"

namespace {
    bool check_consistency_equivalent(const std::vector<XML_component> &xml_components,
                                      const std::vector<Component> &components) {
        double f_xml_relative = 0, o_xml_relative = 0, u_xml_relative = 0;
        for (const auto &xml_comp : xml_components) {
            if (xml_comp.type == 'F') {
                f_xml_relative++;
            }
            if (xml_comp.type == 'U') {
                u_xml_relative++;
            }
            if (xml_comp.type == 'C' || xml_comp.type == 'P' || xml_comp.type == 'O') {
                o_xml_relative++;
            }
        }
        f_xml_relative /= xml_components.size();
        o_xml_relative /= xml_components.size();
        u_xml_relative /= xml_components.size();

        double f_relative = 0, o_relative = 0, u_relative = 0;
        for (const auto &comp : components) {
            if (comp.get_type() == 'F') {
                f_relative++;
            }
            if (comp.get_type() == 'U') {
                u_relative++;
            }
            if (comp.get_type() == 'C' || comp.get_type() == 'P' || comp.get_type() == 'O') {
                o_relative++;
            }
        }
        f_relative /= components.size();
        o_relative /= components.size();
        u_relative /= components.size();

        return f_relative == f_xml_relative && o_relative == o_xml_relative && u_relative == u_xml_relative;
    }

    bool fixed_combination_equivalent(const std::vector<XML_component> &xml_components,
                                      const std::vector<Component> &components,
                                      std::vector<int> &order) {
        std::unordered_map<char, double> strike_map;
        std::unordered_map<char, std::tm> expiration_map;
        for (int i = 0; i < order.size(); ++i) {
            if (xml_components[i].type != components[order[i] - 1].get_type()) {
                if (!(xml_components[i].type == 'O' &&
                      (components[order[i] - 1].get_type() == 'P' || components[order[i] - 1].get_type() == 'C'))) {
                    return false;
                }
            }
            if (std::get_if<char>(&xml_components[i].ratio)) {
                if (std::get<char>(xml_components[i].ratio) == '+' && components[order[i] - 1].ratio <= 0) {
                    return false;
                }
                if (std::get<char>(xml_components[i].ratio) == '-' && components[order[i] - 1].ratio >= 0) {
                    return false;
                }
            }
            if (std::get_if<double>(&xml_components[i].ratio)) {
                if (std::get<double>(xml_components[i].ratio) != components[order[i] - 1].ratio) {
                    return false;
                }
            }

            if (xml_components[i].strike) {
                if (xml_components[i].type == 'O' || xml_components[i].type == 'C' ||
                    xml_components[i].type == 'P') {
                    if (strike_map.find(xml_components[i].strike) == strike_map.end()) {
                        strike_map[xml_components[i].strike] = components[order[i] - 1].strike;
                    } else {
                        if (strike_map[xml_components[i].strike] != components[order[i] - 1].strike) {
                            return false;
                        }
                    }
                }
            }

            if (xml_components[i].expiration) {
                if (expiration_map.find(xml_components[i].expiration) == expiration_map.end()) {
                    expiration_map[xml_components[i].expiration] = components[order[i] - 1].expiration;
                } else {
                    std::tm t1 = expiration_map[xml_components[i].expiration];
                    std::tm t2 = components[order[i] - 1].expiration;
                    if (difftime(mktime(&t1), mktime(&t2)) != 0) {
                        return false;
                    }
                }
            }

            if (xml_components[i].strike_offset) {
                for (int ii = i - 1; ii >= 0; --ii) {
                    if (xml_components[ii].type == 'O' || xml_components[ii].type == 'C' ||
                        xml_components[ii].type == 'P') {
                        if (xml_components[ii].strike_offset) {

                            if (xml_components[i].strike_offset == xml_components[ii].strike_offset) {
                                if (components[order[i] - 1].strike != components[order[ii] - 1].strike) {
                                    return false;
                                }
                            }
                            if (xml_components[i].strike_offset > 0 &&
                                xml_components[ii].strike_offset > 0) {
                                if (xml_components[i].strike_offset >
                                    xml_components[ii].strike_offset) {
                                    if (components[order[i] - 1].strike <= components[order[ii] - 1].strike) {
                                        return false;
                                    }
                                }
                            }
                            if (xml_components[i].strike_offset < 0 &&
                                xml_components[ii].strike_offset < 0) {
                                if (xml_components[i].strike_offset >
                                    xml_components[ii].strike_offset) {
                                    if (components[order[i] - 1].strike >= components[order[ii] - 1].strike) {
                                        return false;
                                    }
                                }
                            }
                        } else {
                            if (xml_components[i].strike_offset > 0) {
                                if (components[order[i] - 1].strike <= components[order[ii] - 1].strike) {
                                    return false;
                                }
                            }
                            if (xml_components[i].strike_offset < 0) {
                                if (components[order[i] - 1].strike >= components[order[ii] - 1].strike) {
                                    return false;
                                }
                            }
                        }
                    }
                }
            }

            if (xml_components[i].expiration_offset) {
                for (int ii = i - 1; ii >= 0; --ii) {

                    std::tm i_date = components[order[i] - 1].expiration;
                    std::tm ii_date = components[order[ii] - 1].expiration;

                    if (xml_components[ii].expiration_offset) {

                        if (xml_components[i].expiration_offset == xml_components[ii].expiration_offset) {
                            if (difftime(mktime(&i_date), mktime(&ii_date)) != 0) {
                                return false;
                            }
                        }
                        if (xml_components[i].expiration_offset_type == ExpirationOffsetType::Plus &&
                            xml_components[ii].expiration_offset_type == ExpirationOffsetType::Plus) {
                            if (xml_components[i].expiration_offset >
                                xml_components[ii].expiration_offset) {
                                if (difftime(mktime(&i_date), mktime(&ii_date)) <= 0) {
                                    return false;
                                }
                            } else {
                                continue;
                            }
                        }
                        if (xml_components[i].expiration_offset_type == ExpirationOffsetType::Minus &&
                            xml_components[ii].expiration_offset_type == ExpirationOffsetType::Minus) {
                            if (xml_components[i].expiration_offset >
                                xml_components[ii].expiration_offset) {
                                if (difftime(mktime(&i_date), mktime(&ii_date)) >= 0) {
                                    return false;
                                }
                            } else {
                                continue;
                            }
                        }

                        size_t i_offset = xml_components[i].expiration_offset;
                        size_t ii_offset = xml_components[ii].expiration_offset;

                        if (xml_components[i].expiration_offset_type == ExpirationOffsetType::Quarter &&
                            xml_components[ii].expiration_offset_type == ExpirationOffsetType::Quarter) {
                            if ((i_offset > ii_offset) &&
                                (i_offset - ii_offset) * 3 != (components[order[i] - 1].expiration.tm_mon -
                                                               components[order[ii] - 1].expiration.tm_mon)) {
                                return false;
                            }
                            if ((i_offset < ii_offset) &&
                                (ii_offset - i_offset) * 3 != (components[order[ii] - 1].expiration.tm_mon -
                                                               components[order[i] - 1].expiration.tm_mon)) {
                                return false;
                            }
                        }
                        if (xml_components[i].expiration_offset_type == ExpirationOffsetType::Year &&
                            xml_components[ii].expiration_offset_type == ExpirationOffsetType::Year) {
                            if ((i_offset > ii_offset) &&
                                (i_offset - ii_offset) != (components[order[i] - 1].expiration.tm_year -
                                                           components[order[ii] - 1].expiration.tm_year)) {
                                return false;
                            }
                            if ((i_offset < ii_offset) &&
                                (ii_offset - i_offset) != (components[order[ii] - 1].expiration.tm_year -
                                                           components[order[i] - 1].expiration.tm_year)) {
                                return false;
                            }
                            if (components[order[ii] - 1].expiration.tm_mon !=
                                components[order[i] - 1].expiration.tm_mon) {
                                return false;
                            }
                            if (components[order[ii] - 1].expiration.tm_mday !=
                                components[order[i] - 1].expiration.tm_mday) {
                                return false;
                            }
                        }
                        if (xml_components[i].expiration_offset_type == ExpirationOffsetType::Month &&
                            xml_components[ii].expiration_offset_type == ExpirationOffsetType::Month) {
                            if ((i_offset > ii_offset) &&
                                (i_offset - ii_offset) != (components[order[i] - 1].expiration.tm_mon -
                                                           components[order[ii] - 1].expiration.tm_mon)) {
                                return false;
                            }
                            if ((i_offset < ii_offset) &&
                                (ii_offset - i_offset) != (components[order[ii] - 1].expiration.tm_mon -
                                                           components[order[i] - 1].expiration.tm_mon)) {
                                return false;
                            }
                            if (components[order[ii] - 1].expiration.tm_mday !=
                                components[order[i] - 1].expiration.tm_mday) {
                                return false;
                            }
                        }
                        if (xml_components[i].expiration_offset_type == ExpirationOffsetType::Day &&
                            xml_components[ii].expiration_offset_type == ExpirationOffsetType::Day) {
                            if ((i_offset > ii_offset) &&
                                (i_offset - ii_offset) != (components[order[i] - 1].expiration.tm_mday -
                                                           components[order[ii] - 1].expiration.tm_mday)) {
                                return false;
                            }
                            if ((i_offset < ii_offset) &&
                                (ii_offset - i_offset) != (components[order[ii] - 1].expiration.tm_mday -
                                                           components[order[i] - 1].expiration.tm_mday)) {
                                return false;
                            }
                        }
                    } else {
                        if (xml_components[i].expiration_offset_type == ExpirationOffsetType::Plus) {
                            if (difftime(mktime(&i_date), mktime(&ii_date)) <= 0) {
                                return false;
                            }
                        }
                        if (xml_components[i].expiration_offset_type == ExpirationOffsetType::Minus) {
                            if (difftime(mktime(&i_date), mktime(&ii_date)) >= 0) {
                                return false;
                            }
                        }

                        size_t i_offset = xml_components[i].expiration_offset;

                        if (xml_components[i].expiration_offset_type == ExpirationOffsetType::Quarter) {
                            if (i_offset * 3 != (components[order[i] - 1].expiration.tm_mon -
                                                 components[order[ii] - 1].expiration.tm_mon)) {
                                return false;
                            }
                        }
                        if (xml_components[i].expiration_offset_type == ExpirationOffsetType::Year) {
                            if (i_offset != (components[order[i] - 1].expiration.tm_mday !=
                                             components[order[ii] - 1].expiration.tm_mday)) {
                                return false;
                            }
                            if (i_offset != (components[order[i] - 1].expiration.tm_mon !=
                                             components[order[ii] - 1].expiration.tm_mon)) {
                                return false;
                            }
                            if (i_offset != (components[order[i] - 1].expiration.tm_year -
                                             components[order[ii] - 1].expiration.tm_year)) {
                                return false;
                            }
                        }
                        if (xml_components[i].expiration_offset_type == ExpirationOffsetType::Month) {
                            if (i_offset != (components[order[i] - 1].expiration.tm_mday !=
                                             components[order[ii] - 1].expiration.tm_mon)) {
                                return false;
                            }
                            if (i_offset != (components[order[i] - 1].expiration.tm_mon -
                                             components[order[ii] - 1].expiration.tm_mon)) {
                                return false;
                            }
                        }
                        if (xml_components[i].expiration_offset_type == ExpirationOffsetType::Day) {
                            if (i_offset != (components[order[i] - 1].expiration.tm_mday -
                                             components[order[ii] - 1].expiration.tm_mday)) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    }

    bool multiple_combination_equivalent(const std::vector<XML_component> &xml_components,
                                         const std::vector<Component> &components,
                                         std::vector<int> &order) {
        size_t blocks_amount = components.size() / xml_components.size();
        size_t block_size = xml_components.size();
        std::vector<int> order_to_check(block_size);
        for (size_t i = 0; i < blocks_amount; ++i) {
            for (size_t j = i * block_size; j < (i + 1) * block_size; ++j) {
                order_to_check[j - i * block_size] = order[j];
            }
            if (!fixed_combination_equivalent(xml_components, components, order_to_check)) {
                return false;
            }
        }
        return true;
    }

    bool more_combination_equivalent(const XML_component &xml_component,
                                     const std::vector<Component> &components,
                                     std::vector<int> &order) {
        for (int i = 0; i < order.size(); ++i) {
            if (xml_component.type != components[order[i] - 1].get_type()) {
                if (!(xml_component.type == 'O' &&
                      (components[order[i] - 1].get_type() == 'P' || components[order[i] - 1].get_type() == 'C'))) {
                    return false;
                }
            }
            if (std::get_if<char>(&xml_component.ratio)) {
                if (std::get<char>(xml_component.ratio) == '+' && components[order[i] - 1].ratio <= 0) {
                    return false;
                }
                if (std::get<char>(xml_component.ratio) == '-' && components[order[i] - 1].ratio >= 0) {
                    return false;
                }
            }
            if (std::get_if<double>(&xml_component.ratio)) {
                if (std::get<double>(xml_component.ratio) != components[order[i] - 1].ratio) {
                    return false;
                }
            }
        }
        return true;
    }

    void shuffle_order(std::vector<int> &order) {
        std::vector<int> temp = order;
        for (size_t i = 0; i < temp.size(); ++i) {
            order[temp[i] - 1] = i + 1;
        }
    }

}

bool Combinations::load(const std::filesystem::path &resource) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(resource.c_str());
    if (!result) {
        return false;
    }
// parsing data
    for (auto comb : doc.child("combinations").children("combination")) {
        XML_combination tmp_comb;
        tmp_comb.name = comb.attribute("name").value();
        tmp_comb.shortname = comb.attribute("shortname").value();
        tmp_comb.identifier = comb.attribute("identifier").value();
        tmp_comb.set_cardinality(comb);
        for (auto comp : comb.child("legs").children("leg")) {
            XML_component tmp_comp(comp);
            tmp_comb.components.push_back(tmp_comp);
        }
        xml_combinations.push_back(tmp_comb);
    }
    return true;
}

std::string Combinations::classify(const std::vector<Component> &components,
                                   std::vector<int> &order) const {
    if (components.empty()) {
        return "Unclassified";
    }
    order.resize(components.size());
    for (int i = 1; i <= components.size(); ++i) {
        order[i - 1] = i;
    }
    for (const auto &xml_combination : xml_combinations) {
        if (((components.size() != xml_combination.components.size()) &&
             xml_combination.cardinality == CardinalityType::Fixed)
            ||
            ((components.size() % xml_combination.components.size() != 0) &&
             xml_combination.cardinality == CardinalityType::Multiple)
            || ((components.size() < xml_combination.components.size()) &&
                xml_combination.cardinality == CardinalityType::More)) {
            continue;
        }

        switch (xml_combination.cardinality) {
            case CardinalityType::Fixed:
                for (int j = 0; j < order.size(); ++j) {
                    order[j] = j + 1;
                }
                do {
                    if (fixed_combination_equivalent(xml_combination.components, components, order)) {
                        shuffle_order(order);
                        return xml_combination.name;
                    }
                } while (std::next_permutation(order.begin(), order.end()));
                break;
            case CardinalityType::Multiple:
                if (!check_consistency_equivalent(xml_combination.components, components))
                    break;

                for (int j = 0; j < order.size(); ++j) {
                    order[j] = j + 1;
                }

                do {
                    if (multiple_combination_equivalent(xml_combination.components, components, order)) {
                        shuffle_order(order);
                        return xml_combination.name;
                    }
                } while (std::next_permutation(order.begin(), order.end()));
                break;
            case CardinalityType::More:
                if (order.size() < xml_combination.mincount) {
                    break;
                }
                if (more_combination_equivalent(xml_combination.components.front(), components, order)) {
                    shuffle_order(order);
                    return xml_combination.name;
                }
                break;
            default:
                break;
        }
    }
    order.clear();
    return "Unclassified";
}

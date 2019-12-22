#include "myhtmlpp/matchers.hpp"

#include <sstream>
#include <string>

bool myhtmlpp::matchers::exact_match(const Node& node, const std::string& key,
                                     const std::string& val) {
    if (auto attr = node.at(key)) {
        return attr.value() == val;
    }

    return false;
}

bool myhtmlpp::matchers::whitespace_seperated(const Node& node,
                                              const std::string& key,
                                              const std::string& val) {
    if (val.empty()) {
        return false;
    }

    if (auto attr = node.at(key)) {
        std::stringstream ss(attr.value());
        std::string token;
        while (std::getline(ss, token, ' ')) {
            if (token == val) {
                return true;
            }
        }
    }

    return false;
}

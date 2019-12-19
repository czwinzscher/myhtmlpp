#pragma once

#include "node.hpp"

#include <string>

namespace myhtmlpp::matchers {

/**
 * @brief Returns true if `node` has an attribute with the key `key`
 *        and the value of this key is equal to `value`, false otherwise.
 */
bool exact_match(const Node& node, const std::string& key,
                 const std::string& val);

/**
 * @brief Returns true if `node` has an attribute with the key `key`
 *        and the value of this key, split by whitespace, contains `value`,
 *        false otherwise.
 */
bool whitespace_seperated(const Node& node, const std::string& key,
                          const std::string& val);

}  // namespace myhtmlpp::matchers

#include "myhtmlpp/error.hpp"

#include <string>

myhtmlpp::init_error::init_error(mystatus_t status)
    : std::runtime_error("myhtml_init failed with status " +
                         std::to_string(status)) {}

myhtmlpp::tree_init_error::tree_init_error(mystatus_t status)
    : std::runtime_error("myhtml_tree_init failed with status " +
                         std::to_string(status)) {}

myhtmlpp::parse_error::parse_error(mystatus_t status)
    : std::runtime_error("parsing failed with status " +
                         std::to_string(status)) {}

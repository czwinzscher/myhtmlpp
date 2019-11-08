#pragma once

#include <myhtml/api.h>
#include <stdexcept>
#include <string>

namespace myhtmlpp {

/// Exception indicating that `myhtml_init` failed.
class init_error : public std::runtime_error {
public:
    explicit init_error(mystatus_t status);
};

/// Exception indicating that `myhtml_tree_init` failed.
class tree_init_error : public std::runtime_error {
public:
    explicit tree_init_error(mystatus_t status);
};

/// Exception indicating that `myhtml_parse` or `myhtml_parse_fragment` failed.
class parse_error : public std::runtime_error {
public:
    explicit parse_error(mystatus_t status);
};

}  // namespace myhtmlpp

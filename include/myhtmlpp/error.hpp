#pragma once

#include <myhtml/api.h>
#include <stdexcept>
#include <string>

namespace myhtmlpp {

class init_error : public std::runtime_error {
public:
    explicit init_error(mystatus_t status);
};

class tree_init_error : public std::runtime_error {
public:
    explicit tree_init_error(mystatus_t status);
};

class parse_error : public std::runtime_error {
public:
    explicit parse_error(mystatus_t status);
};

}  // namespace myhtmlpp

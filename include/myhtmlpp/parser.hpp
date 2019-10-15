#pragma once

#include "node.hpp"

#include <myhtml/api.h>
#include <string>

namespace myhtmlpp {

class Parser {
public:
    explicit Parser(const std::string& html);
    ~Parser();

    myhtmlpp::Node root();

private:
    myhtml_t* m_raw_myhtml;
    myhtml_tree_t* m_raw_tree;
};

}  // namespace myhtmlpp

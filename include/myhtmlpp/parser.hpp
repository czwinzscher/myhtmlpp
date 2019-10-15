#pragma once

#include <myhtml/api.h>
#include <string>

namespace myhtmlpp {

class Parser {
public:
    explicit Parser(const std::string& html);
    ~Parser();

private:
    myhtml_t* m_raw_myhtml;
    myhtml_tree_t* m_tree;
};

}  // namespace myhtmlpp

#pragma once

#include <myhtml/api.h>
#include <optional>

namespace myhtmlpp {

class Node {
public:
    explicit Node(myhtml_tree_node_t* raw_node);

    std::optional<std::string> text();
    std::optional<myhtmlpp::Node> child();
    std::optional<myhtmlpp::Node> parent();

private:
    myhtml_tree_node_t* m_raw_node;
};

}

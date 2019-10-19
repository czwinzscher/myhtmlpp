#pragma once

#include <myhtml/api.h>
#include <optional>
#include <vector>

namespace myhtmlpp {

class Node {
public:
    explicit Node(myhtml_tree_node_t* raw_node);
    ~Node();

    bool good();

    std::optional<std::string> text();
    std::vector<myhtmlpp::Node> children();
    std::optional<myhtmlpp::Node> parent();
    myhtml_tag_id_t tag_id() const;

private:
    myhtml_tree_node_t* m_raw_node;
};

}  // namespace myhtmlpp

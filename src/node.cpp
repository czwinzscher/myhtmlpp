#include "myhtmlpp/node.hpp"

myhtmlpp::Node::Node(myhtml_tree_node_t* raw_node)
    : m_raw_node(raw_node) {}

std::optional<myhtmlpp::Node> myhtmlpp::Node::child() {
    if (auto raw_child = myhtml_node_child(m_raw_node)) {
        return Node(raw_child);
    }

    return std::nullopt;
}

std::optional<myhtmlpp::Node> myhtmlpp::Node::parent() {
    if (auto raw_parent = myhtml_node_parent(m_raw_node)) {
        return Node(raw_parent);
    }

    return std::nullopt;
}

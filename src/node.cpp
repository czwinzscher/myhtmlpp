#include "myhtmlpp/node.hpp"

myhtmlpp::Node::Node(myhtml_tree_node_t* raw_node) : m_raw_node(raw_node) {}

myhtmlpp::Node::~Node() { myhtml_node_free(m_raw_node); }

std::optional<std::string> myhtmlpp::Node::text() {
    if (auto raw_text = myhtml_node_text(m_raw_node, nullptr)) {
        return std::string(raw_text);
    }

    return std::nullopt;
}

std::vector<myhtmlpp::Node> myhtmlpp::Node::children() {
    std::vector<myhtmlpp::Node> res;

    myhtml_tree_node_t* raw_child = myhtml_node_child(m_raw_node);
    while (raw_child != nullptr) {
        res.emplace_back(raw_child);
        raw_child = myhtml_node_next(raw_child);
    }

    return res;
}

std::optional<myhtmlpp::Node> myhtmlpp::Node::parent() {
    if (auto raw_parent = myhtml_node_parent(m_raw_node)) {
        return Node(raw_parent);
    }

    return std::nullopt;
}

myhtml_tag_id_t myhtmlpp::Node::tag_id() {
    return myhtml_node_tag_id(m_raw_node);
}

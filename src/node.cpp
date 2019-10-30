#include "myhtmlpp/node.hpp"
#include "myhtmlpp/tree.hpp"

#include <myhtml/api.h>
#include <optional>
#include <string>
#include <vector>

myhtmlpp::Node::Node(myhtml_tree_node_t* raw_node) : m_raw_node(raw_node) {}

myhtmlpp::Node::~Node() { myhtml_node_free(m_raw_node); }

bool myhtmlpp::Node::operator==(const Node& other) const {
    return m_raw_node == other.m_raw_node;
}

bool myhtmlpp::Node::operator!=(const Node& other) const {
    return !operator==(other);
}

bool myhtmlpp::Node::good() const { return m_raw_node != nullptr; }

// myhtmlpp::Tree myhtmlpp::Node::tree() const {
//     return m_tree;
// }

std::string myhtmlpp::Node::text() const {
    if (auto raw_text = myhtml_node_text(m_raw_node, nullptr)) {
        return std::string(raw_text);
    }

    return "";
}

myhtml_tag_id_t myhtmlpp::Node::tag_id() const {
    return myhtml_node_tag_id(m_raw_node);
}

std::optional<myhtmlpp::Node> myhtmlpp::Node::first_child() const {
    if (auto raw_first = myhtml_node_child(m_raw_node)) {
        return Node(raw_first);
    }

    return std::nullopt;
}

std::optional<myhtmlpp::Node> myhtmlpp::Node::last_child() const {
    if (auto raw_last = myhtml_node_last_child(m_raw_node)) {
        return Node(raw_last);
    }

    return std::nullopt;
}

std::optional<myhtmlpp::Node> myhtmlpp::Node::next() const {
    if (auto raw_next = myhtml_node_next(m_raw_node)) {
        return Node(raw_next);
    }

    return std::nullopt;
}

std::optional<myhtmlpp::Node> myhtmlpp::Node::previous() const {
    if (auto raw_prev = myhtml_node_prev(m_raw_node)) {
        return Node(raw_prev);
    }

    return std::nullopt;
}

std::optional<myhtmlpp::Node> myhtmlpp::Node::parent() const {
    if (auto raw_parent = myhtml_node_parent(m_raw_node)) {
        return Node(raw_parent);
    }

    return std::nullopt;
}

std::vector<myhtmlpp::Node> myhtmlpp::Node::children() const {
    std::vector<myhtmlpp::Node> res;

    myhtml_tree_node_t* raw_child = myhtml_node_child(m_raw_node);
    while (raw_child != nullptr) {
        res.emplace_back(raw_child);
        raw_child = myhtml_node_next(raw_child);
    }

    return res;
}

void myhtmlpp::Node::add_child(const Node& node) {
    myhtml_tree_node_add_child(m_raw_node, node.m_raw_node);
}

void myhtmlpp::Node::insert_before(const Node& node) {
    myhtml_tree_node_insert_before(m_raw_node, node.m_raw_node);
}

void myhtmlpp::Node::insert_after(const Node& node) {
    myhtml_tree_node_insert_after(m_raw_node, node.m_raw_node);
}

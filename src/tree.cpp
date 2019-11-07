#include "myhtmlpp/tree.hpp"

#include "myhtmlpp/node.hpp"

#include <mycore/myosi.h>
#include <mycore/mystring.h>
#include <myhtml/api.h>
#include <string>
#include <vector>

myhtmlpp::Tree::Tree(myhtml_t* raw_myhtml, myhtml_tree_t* raw_tree)
    : m_raw_myhtml(raw_myhtml), m_raw_tree(raw_tree) {}

myhtmlpp::Tree::~Tree() {
    myhtml_tree_destroy(m_raw_tree);
    myhtml_destroy(m_raw_myhtml);
}

bool myhtmlpp::Tree::good() const {
    return m_raw_tree != nullptr && m_raw_myhtml != nullptr;
}

myhtmlpp::Node myhtmlpp::Tree::document_node() const {
    return Node(myhtml_tree_get_document(m_raw_tree));
}

myhtmlpp::Node myhtmlpp::Tree::html_node() const {
    return Node(myhtml_tree_get_node_html(m_raw_tree));
}

myhtmlpp::Node myhtmlpp::Tree::head_node() const {
    return Node(myhtml_tree_get_node_head(m_raw_tree));
}

myhtmlpp::Node myhtmlpp::Tree::body_node() const {
    return Node(myhtml_tree_get_node_body(m_raw_tree));
}

std::string myhtmlpp::Tree::html() const {
    mycore_string_raw_t str = {nullptr, 0, 0};
    myhtml_serialization_tree_buffer(myhtml_tree_get_document(m_raw_tree),
                                     &str);

    return str.data != nullptr ? str.data : "";
}

myhtmlpp::Node myhtmlpp::Tree::create_node(myhtml_tag_id_t tag_id,
                                           myhtml_namespace_t ns) {
    myhtml_tree_node_t* n = myhtml_node_create(m_raw_tree, tag_id, ns);

    return Node(n);
}

// Iterator
myhtmlpp::Tree::Iterator::Iterator(const Node& node) : m_node(node) {}

myhtmlpp::Tree::Iterator::reference myhtmlpp::Tree::Iterator::operator*() {
    return m_node;
}

myhtmlpp::Tree::Iterator& myhtmlpp::Tree::Iterator::operator++() {
    std::vector<Node> children = m_node.children();
    m_stack.insert(m_stack.end(), children.rbegin(), children.rend());

    if (m_stack.empty()) {
        m_node = Node(nullptr);
        return *this;
    }

    m_node = m_stack.back();
    m_stack.pop_back();

    return *this;

    // Node new_node(nullptr);

    // if (auto child = m_node.first_child()) {
    //     new_node = child.value();
    // } else if (auto next = m_node.next()) {
    //     new_node = next.value();
    // } else {
    //     while (auto parent = m_node.parent()) {
    //         m_node = parent.value();

    //         if (auto parent_next = m_node.next()) {
    //             new_node = parent_next.value();
    //             break;
    //         }
    //     }
    // }

    // m_node = new_node;

    // return *this;
}

bool myhtmlpp::Tree::Iterator::operator!=(const Iterator& other) const {
    return m_node != other.m_node;
}

myhtmlpp::Tree::Iterator myhtmlpp::Tree::begin() noexcept {
    return Iterator(document_node());
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
myhtmlpp::Tree::Iterator myhtmlpp::Tree::end() noexcept {
    return Iterator(Node(nullptr));
}

// ConstIterator
myhtmlpp::Tree::ConstIterator::ConstIterator(const Node& node) : m_node(node) {}

myhtmlpp::Tree::ConstIterator::reference
    myhtmlpp::Tree::ConstIterator::operator*() {
    return m_node;
}

myhtmlpp::Tree::ConstIterator& myhtmlpp::Tree::ConstIterator::operator++() {
    std::vector<Node> children = m_node.children();
    m_stack.insert(m_stack.end(), children.rbegin(), children.rend());

    if (m_stack.empty()) {
        m_node = Node(nullptr);
        return *this;
    }

    m_node = m_stack.back();
    m_stack.pop_back();

    return *this;

    // Node new_node(nullptr);

    // if (auto child = m_node.first_child()) {
    //     new_node = child.value();
    // } else if (auto next = m_node.next()) {
    //     new_node = next.value();
    // } else {
    //     while(auto parent = m_node.parent()) {
    //         m_node = parent.value();

    //         if (auto parent_next = m_node.next()) {
    //             new_node = parent_next.value();
    //             break;
    //         }
    //     }
    // }

    // m_node = new_node;

    // return *this;
}

bool myhtmlpp::Tree::ConstIterator::operator!=(
    const ConstIterator& other) const {
    return m_node != other.m_node;
}

myhtmlpp::Tree::ConstIterator myhtmlpp::Tree::begin() const noexcept {
    return ConstIterator(document_node());
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
myhtmlpp::Tree::ConstIterator myhtmlpp::Tree::end() const noexcept {
    return ConstIterator(Node(nullptr));
}

myhtmlpp::Tree::ConstIterator myhtmlpp::Tree::cbegin() const noexcept {
    return begin();
}

myhtmlpp::Tree::ConstIterator myhtmlpp::Tree::cend() const noexcept {
    return end();
}

std::ostream& myhtmlpp::operator<<(std::ostream& os, const Tree& t) {
    os << t.html();

    return os;
}

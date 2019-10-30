#include "myhtmlpp/tree.hpp"

#include "myhtmlpp/node.hpp"

#include <mycore/myosi.h>
#include <myhtml/api.h>

myhtmlpp::Tree::Tree(myhtml_t* raw_myhtml, myhtml_tree_t* raw_tree)
    : m_raw_myhtml(raw_myhtml), m_raw_tree(raw_tree) {}

myhtmlpp::Tree::~Tree() {
    myhtml_tree_destroy(m_raw_tree);
    myhtml_destroy(m_raw_myhtml);
}

// use namespace here so we don't get a warning because it's a friend function
namespace myhtmlpp {

std::ostream& operator<<(std::ostream& os, const Tree& t) {
    mycore_string_raw_t str = {nullptr, 0, 0};
    myhtml_serialization_tree_buffer(myhtml_tree_get_document(t.m_raw_tree),
                                     &str);

    os << str.data;

    return os;
}

}  // namespace myhtmlpp

bool myhtmlpp::Tree::good() const { return m_raw_tree != nullptr; }

myhtmlpp::Node myhtmlpp::Tree::document() const {
    return Node(myhtml_tree_get_document(m_raw_tree));
}

myhtmlpp::Node myhtmlpp::Tree::root() const {
    return Node(myhtml_tree_get_node_html(m_raw_tree));
}

myhtmlpp::Node myhtmlpp::Tree::head() const {
    return Node(myhtml_tree_get_node_head(m_raw_tree));
}

myhtmlpp::Node myhtmlpp::Tree::body() const {
    return Node(myhtml_tree_get_node_body(m_raw_tree));
}

myhtmlpp::Node myhtmlpp::Tree::create_node(myhtml_tag_id_t tag_id,
                                           myhtml_namespace_t ns) {
    myhtml_tree_node_t* n = myhtml_node_create(m_raw_tree, tag_id, ns);

    return Node(n);
}

// Iterator
myhtmlpp::Tree::Iterator::Iterator(myhtml_tree_t* t, const Node& node)
    : m_data(t), m_node(node) {}

myhtmlpp::Tree::Iterator& myhtmlpp::Tree::Iterator::operator++() {
    if (auto child = m_node.first_child()) {
        m_node = child.value();
    } else if (auto next = m_node.next()) {
        m_node = next.value();
    } else {
        // TODO
    }

    return *this;
}

myhtmlpp::Tree::Iterator myhtmlpp::Tree::begin() noexcept {
    return Iterator(m_raw_tree, document());
}

myhtmlpp::Tree::Iterator myhtmlpp::Tree::end() noexcept {
    return Iterator(m_raw_tree, Node(nullptr));
}

// ConstIterator
myhtmlpp::Tree::ConstIterator::ConstIterator(myhtml_tree_t* t, const Node& node)
    : m_data(t), m_node(node) {}

myhtmlpp::Tree::ConstIterator& myhtmlpp::Tree::ConstIterator::operator++() {
    if (auto child = m_node.first_child()) {
        m_node = child.value();
    } else if (auto next = m_node.next()) {
        m_node = next.value();
    } else {
        // TODO
    }

    return *this;
}

myhtmlpp::Tree::ConstIterator myhtmlpp::Tree::begin() const noexcept {
    return ConstIterator(m_raw_tree, document());
}

myhtmlpp::Tree::ConstIterator myhtmlpp::Tree::end() const noexcept {
    return ConstIterator(m_raw_tree, Node(nullptr));
}

#include "myhtmlpp/tree.hpp"

#include "myhtmlpp/collection.hpp"
#include "myhtmlpp/node.hpp"

#include <myhtml/api.h>

myhtmlpp::Tree::Tree(myhtml_tree_t* raw_tree) : m_raw_tree(raw_tree) {}

myhtmlpp::Tree::~Tree() { myhtml_tree_destroy(m_raw_tree); }

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

myhtmlpp::Collection
myhtmlpp::Tree::nodes_by_tag_id(myhtml_tag_id_t tag_id) const {
    myhtml_collection_t* c =
        myhtml_get_nodes_by_tag_id(m_raw_tree, nullptr, tag_id, nullptr);

    return Collection(c);
}

myhtmlpp::Collection
myhtmlpp::Tree::nodes_by_name(const std::string& name) const {
    myhtml_collection_t* c = myhtml_get_nodes_by_name(
        m_raw_tree, nullptr, name.c_str(), strlen(name.c_str()), nullptr);

    return Collection(c);
}

myhtmlpp::Collection
myhtmlpp::Tree::nodes_by_attribute_key(const std::string& key) const {
    myhtml_collection_t* c = myhtml_get_nodes_by_attribute_key(
        m_raw_tree, nullptr, nullptr, key.c_str(), strlen(key.c_str()),
        nullptr);

    return Collection(c);
}

myhtmlpp::Collection
myhtmlpp::Tree::nodes_by_attribute_value(const std::string& value) const {
    myhtml_collection_t* c = myhtml_get_nodes_by_attribute_value(
        m_raw_tree, nullptr, nullptr, false, nullptr, 0, value.c_str(),
        strlen(value.c_str()), nullptr);

    return Collection(c);
}

myhtmlpp::Collection myhtmlpp::Tree::nodes_by_attribute_value_with_key(
    const std::string& key, const std::string& value) const {
    myhtml_collection_t* c = myhtml_get_nodes_by_attribute_value(
        m_raw_tree, nullptr, nullptr, false, key.c_str(), strlen(key.c_str()),
        value.c_str(), strlen(value.c_str()), nullptr);

    return Collection(c);
}

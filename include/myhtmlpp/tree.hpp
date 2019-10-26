#pragma once

#include "collection.hpp"
#include "node.hpp"

#include <myhtml/api.h>
#include <string>

namespace myhtmlpp {

class Tree {
public:
    explicit Tree(myhtml_tree_t* raw_tree);
    ~Tree();

    [[nodiscard]] bool good() const;

    [[nodiscard]] Node document() const;
    [[nodiscard]] Node root() const;
    [[nodiscard]] Node head() const;
    [[nodiscard]] Node body() const;

    Node create_node(myhtml_tag_id_t tag_id, myhtml_namespace_t ns);

    [[nodiscard]] Collection nodes_by_tag_id(myhtml_tag_id_t tag_id) const;
    [[nodiscard]] Collection nodes_by_name(const std::string& name) const;
    [[nodiscard]] Collection
    nodes_by_attribute_key(const std::string& key) const;
    [[nodiscard]] Collection
    nodes_by_attribute_value(const std::string& value) const;
    [[nodiscard]] Collection
    nodes_by_attribute_value_with_key(const std::string& key,
                                      const std::string& value) const;

private:
    myhtml_tree_t* m_raw_tree;
};

}  // namespace myhtmlpp

#pragma once

#include "collection.hpp"
#include "node.hpp"

#include <myhtml/api.h>
#include <string>

namespace myhtmlpp {

class Parser {
public:
    explicit Parser(const std::string& html);
    ~Parser();

    Node root();

    Collection nodes_by_tag_id(myhtml_tag_id_t tag_id);
    Collection nodes_by_name(const std::string& name);
    Collection nodes_by_attribute_key(const std::string& key);
    Collection nodes_by_attribute_value(const std::string& value,
                                        bool case_insensitive = false);
    Collection nodes_by_attribute_value_with_key(const std::string& key,
                                                 const std::string& value,
                                                 bool case_insensitive = false);

private:
    myhtml_t* m_raw_myhtml;
    myhtml_tree_t* m_raw_tree;
};

}  // namespace myhtmlpp

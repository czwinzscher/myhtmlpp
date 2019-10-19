#include "myhtmlpp/parser.hpp"

myhtmlpp::Parser::Parser(const std::string& html) {
    m_raw_myhtml = myhtml_create();
    myhtml_init(m_raw_myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);

    m_raw_tree = myhtml_tree_create();
    myhtml_tree_init(m_raw_tree, m_raw_myhtml);

    myhtml_parse(m_raw_tree, MyENCODING_UTF_8, html.c_str(),
                 strlen(html.c_str()));
}

myhtmlpp::Parser::~Parser() {
    myhtml_tree_destroy(m_raw_tree);
    myhtml_destroy(m_raw_myhtml);
}

bool myhtmlpp::Parser::good() const {
    return m_raw_myhtml != nullptr && m_raw_tree != nullptr;
}

myhtmlpp::Node myhtmlpp::Parser::root() const {
    return Node(myhtml_tree_get_document(m_raw_tree));
}

myhtmlpp::Collection
myhtmlpp::Parser::nodes_by_tag_id(myhtml_tag_id_t tag_id) const {
    myhtml_collection_t* c =
        myhtml_get_nodes_by_tag_id(m_raw_tree, nullptr, tag_id, nullptr);

    return Collection(c);
}

myhtmlpp::Collection
myhtmlpp::Parser::nodes_by_name(const std::string& name) const {
    myhtml_collection_t* c = myhtml_get_nodes_by_name(
        m_raw_tree, nullptr, name.c_str(), strlen(name.c_str()), nullptr);

    return Collection(c);
}

myhtmlpp::Collection
myhtmlpp::Parser::nodes_by_attribute_key(const std::string& key) const {
    myhtml_collection_t* c = myhtml_get_nodes_by_attribute_key(
        m_raw_tree, nullptr, nullptr, key.c_str(), strlen(key.c_str()),
        nullptr);

    return Collection(c);
}

myhtmlpp::Collection
myhtmlpp::Parser::nodes_by_attribute_value(const std::string& value,
                                           bool case_insensitive) const {
    myhtml_collection_t* c = myhtml_get_nodes_by_attribute_value(
        m_raw_tree, nullptr, nullptr, case_insensitive, nullptr, 0,
        value.c_str(), strlen(value.c_str()), nullptr);

    return Collection(c);
}

myhtmlpp::Collection myhtmlpp::Parser::nodes_by_attribute_value_with_key(
    const std::string& key, const std::string& value,
    bool case_insensitive) const {
    myhtml_collection_t* c = myhtml_get_nodes_by_attribute_value(
        m_raw_tree, nullptr, nullptr, case_insensitive, key.c_str(),
        strlen(key.c_str()), value.c_str(), strlen(value.c_str()), nullptr);

    return Collection(c);
}

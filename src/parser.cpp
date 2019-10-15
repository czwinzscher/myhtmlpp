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

myhtmlpp::Node myhtmlpp::Parser::root() {
    return myhtmlpp::Node(myhtml_tree_get_document(m_raw_tree));
}

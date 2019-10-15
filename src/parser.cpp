#include "myhtmlpp/parser.hpp"

myhtmlpp::Parser::Parser(const std::string& html) {
    m_myhtml = myhtml_create();
    myhtml_init(m_myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);

    m_tree = myhtml_tree_create();
    myhtml_tree_init(m_tree, m_myhtml);

    myhtml_parse(m_tree, MyENCODING_UTF_8, html.c_str(), strlen(html.c_str()));
}

myhtmlpp::Parser::~Parser() {
    myhtml_tree_destroy(m_tree);
    myhtml_destroy(m_myhtml);
}
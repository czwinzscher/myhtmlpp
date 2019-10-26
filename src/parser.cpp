#include "myhtmlpp/parser.hpp"

#include "myhtmlpp/tree.hpp"

#include <myhtml/api.h>
#include <string>

myhtmlpp::Parser::Parser() : m_raw_myhtml(nullptr) {}

myhtmlpp::Parser::~Parser() { reset(); }

myhtmlpp::Tree myhtmlpp::Parser::parse(const std::string& html) {
    reset();

    m_raw_myhtml = myhtml_create();
    myhtml_init(m_raw_myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);

    myhtml_tree_t* raw_tree = myhtml_tree_create();
    myhtml_tree_init(raw_tree, m_raw_myhtml);

    myhtml_parse(raw_tree, MyENCODING_UTF_8, html.c_str(),
                 strlen(html.c_str()));

    return Tree(raw_tree);
}

myhtmlpp::Tree myhtmlpp::Parser::parse_with_options(const std::string& html,
                                                    myhtml_options opt,
                                                    size_t thread_count,
                                                    size_t queue_size) {
    reset();

    m_raw_myhtml = myhtml_create();
    myhtml_init(m_raw_myhtml, opt, thread_count, queue_size);

    myhtml_tree_t* raw_tree = myhtml_tree_create();
    myhtml_tree_init(raw_tree, m_raw_myhtml);

    myhtml_parse(raw_tree, MyENCODING_UTF_8, html.c_str(),
                 strlen(html.c_str()));

    return Tree(raw_tree);
}

myhtmlpp::Tree myhtmlpp::Parser::parse_fragment(const std::string& html,
                                                myhtml_tag_id_t tag_id,
                                                myhtml_namespace ns) {
    reset();

    m_raw_myhtml = myhtml_create();
    myhtml_init(m_raw_myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);

    myhtml_tree_t* raw_tree = myhtml_tree_create();
    myhtml_tree_init(raw_tree, m_raw_myhtml);

    myhtml_parse_fragment(raw_tree, MyENCODING_UTF_8, html.c_str(),
                          strlen(html.c_str()), tag_id, ns);

    return Tree(raw_tree);
}

myhtmlpp::Tree myhtmlpp::Parser::parse_fragment_with_options(
    const std::string& html, myhtml_tag_id_t tag_id, myhtml_namespace ns,
    myhtml_options opt, size_t thread_count, size_t queue_size) {
    reset();

    m_raw_myhtml = myhtml_create();
    myhtml_init(m_raw_myhtml, opt, thread_count, queue_size);

    myhtml_tree_t* raw_tree = myhtml_tree_create();
    myhtml_tree_init(raw_tree, m_raw_myhtml);

    myhtml_parse_fragment(raw_tree, MyENCODING_UTF_8, html.c_str(),
                          strlen(html.c_str()), tag_id, ns);

    return Tree(raw_tree);
}

bool myhtmlpp::Parser::good() const { return m_raw_myhtml != nullptr; }

void myhtmlpp::Parser::reset() {
    if (m_raw_myhtml != nullptr) {
        myhtml_destroy(m_raw_myhtml);
        m_raw_myhtml = nullptr;
    }
}

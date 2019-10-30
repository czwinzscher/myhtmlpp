#include "myhtmlpp/parser.hpp"

#include "myhtmlpp/tree.hpp"

#include <myhtml/api.h>
#include <string>

myhtmlpp::Tree myhtmlpp::parse(const std::string& html) {
    myhtml_t* raw_myhtml = myhtml_create();
    myhtml_init(raw_myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);

    myhtml_tree_t* raw_tree = myhtml_tree_create();
    myhtml_tree_init(raw_tree, raw_myhtml);

    myhtml_parse(raw_tree, MyENCODING_UTF_8, html.c_str(),
                 strlen(html.c_str()));

    return Tree(raw_myhtml, raw_tree);
}

myhtmlpp::Tree myhtmlpp::parse_with_options(const std::string& html,
                                            myhtml_options opt,
                                            size_t thread_count,
                                            size_t queue_size) {
    myhtml_t* raw_myhtml = myhtml_create();
    myhtml_init(raw_myhtml, opt, thread_count, queue_size);

    myhtml_tree_t* raw_tree = myhtml_tree_create();
    myhtml_tree_init(raw_tree, raw_myhtml);

    myhtml_parse(raw_tree, MyENCODING_UTF_8, html.c_str(),
                 strlen(html.c_str()));

    return Tree(raw_myhtml, raw_tree);
}

myhtmlpp::Tree myhtmlpp::parse_fragment(const std::string& html,
                                        myhtml_tag_id_t tag_id,
                                        myhtml_namespace ns) {
    myhtml_t* raw_myhtml = myhtml_create();
    myhtml_init(raw_myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);

    myhtml_tree_t* raw_tree = myhtml_tree_create();
    myhtml_tree_init(raw_tree, raw_myhtml);

    myhtml_parse_fragment(raw_tree, MyENCODING_UTF_8, html.c_str(),
                          strlen(html.c_str()), tag_id, ns);

    return Tree(raw_myhtml, raw_tree);
}

myhtmlpp::Tree myhtmlpp::parse_fragment_with_options(
    const std::string& html, myhtml_tag_id_t tag_id, myhtml_namespace ns,
    myhtml_options opt, size_t thread_count, size_t queue_size) {
    myhtml_t* raw_myhtml = myhtml_create();
    myhtml_init(raw_myhtml, opt, thread_count, queue_size);

    myhtml_tree_t* raw_tree = myhtml_tree_create();
    myhtml_tree_init(raw_tree, raw_myhtml);

    myhtml_parse_fragment(raw_tree, MyENCODING_UTF_8, html.c_str(),
                          strlen(html.c_str()), tag_id, ns);

    return Tree(raw_myhtml, raw_tree);
}

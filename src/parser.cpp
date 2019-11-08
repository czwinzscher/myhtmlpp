#include "myhtmlpp/parser.hpp"

#include "myhtmlpp/constants.hpp"
#include "myhtmlpp/error.hpp"
#include "myhtmlpp/tree.hpp"

#include <cstddef>
#include <cstring>
#include <mycore/myosi.h>
#include <myencoding/myosi.h>
#include <myhtml/api.h>
#include <stdexcept>
#include <string>

template <typename ParseFunc, typename... ParseArgs>
myhtmlpp::Tree parse_helper(ParseFunc f, const std::string& html,
                            myhtmlpp::OPTION opt, size_t thread_count,
                            size_t queue_size, ParseArgs... args) {
    myhtml_t* raw_myhtml = myhtml_create();
    mystatus_t init_st = myhtml_init(
        raw_myhtml, static_cast<myhtml_options>(opt), thread_count, queue_size);
    if (init_st != MyHTML_STATUS_OK) {
        throw myhtmlpp::init_error(init_st);
    }

    myhtml_tree_t* raw_tree = myhtml_tree_create();
    mystatus_t tree_st = myhtml_tree_init(raw_tree, raw_myhtml);
    if (tree_st != MyHTML_STATUS_OK) {
        throw myhtmlpp::tree_init_error(tree_st);
    }

    mystatus_t parse_st = f(raw_tree, MyENCODING_UTF_8, html.c_str(),
                            strlen(html.c_str()), args...);
    if (parse_st != MyHTML_STATUS_OK) {
        throw myhtmlpp::parse_error(parse_st);
    }

    return myhtmlpp::Tree(raw_myhtml, raw_tree);
}

myhtmlpp::Tree myhtmlpp::parse(const std::string& html, myhtmlpp::OPTION opt,
                               size_t thread_count, size_t queue_size) {
    return parse_helper(myhtml_parse, html, opt, thread_count, queue_size);
}

myhtmlpp::Tree
myhtmlpp::parse_fragment(const std::string& html, myhtmlpp::TAG tag_id,
                         myhtmlpp::NAMESPACE ns, myhtmlpp::OPTION opt,
                         size_t thread_count, size_t queue_size) {
    return parse_helper(myhtml_parse_fragment, html, opt, thread_count,
                        queue_size, static_cast<myhtml_tag_id_t>(tag_id),
                        static_cast<myhtml_namespace_t>(ns));
}

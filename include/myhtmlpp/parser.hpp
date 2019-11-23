#pragma once

#include "constants.hpp"
#include "tree.hpp"

#include <cstddef>
#include <string>

namespace myhtmlpp {

struct ParseOptions {
    OPTION opt = OPTION::DEFAULT;
    size_t thread_count = 1;
    size_t queue_size = 4096;
};

struct ParseFragmentOptions {
    OPTION opt = OPTION::DEFAULT;
    size_t thread_count = 1;
    size_t queue_size = 4096;
    TAG tag_id = TAG::DIV;
    NAMESPACE ns = NAMESPACE::HTML;
};

/**
 * @brief Parses a HTML string into a Tree structure with the given options.
 *
 * @param html The HTML code that will be parsed.
 * @throw std::runtime_error if one of myhtml_init, myhtml_tree_init
 *        or myhtml_parse does not return MyHTML_STATUS_OK.
 * @return A Tree with the parsed HTML nodes.
 */
Tree parse(const std::string& html, ParseOptions opt = {});

/**
 * @brief Parses a fragment of a HTML string into a Tree structure.
 *
 * @param html The HTML code that will be parsed.
 * @throw std::runtime_error if one of myhtml_init, myhtml_tree_init
 *        or myhtml_parse_fragment does not return MyHTML_STATUS_OK.
 * @return A Tree with the parsed HTML nodes.
 */
Tree parse_fragment(const std::string& html, ParseFragmentOptions opt = {});

}  // namespace myhtmlpp

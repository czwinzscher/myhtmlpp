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
 * @throw `myhtmlpp::init_error` if `myhtml_init` fails,
 *        `myhtmlpp::tree_init_error` if `myhtml_tree_init` fails,
 *        `myhtmlpp::parse_error` if `myhtml_parse` fails.
 * @return A Tree with the parsed HTML nodes.
 */
Tree parse(const std::string& html, const ParseOptions& opt = {});

/**
 * @brief Parses a fragment of a HTML string into a Tree structure.
 *
 * @param html The HTML code that will be parsed.
 * @throw `myhtmlpp::init_error` if `myhtml_init` fails,
 *        `myhtmlpp::tree_init_error` if `myhtml_tree_init` fails,
 *        `myhtmlpp::parse_error` if `myhtml_parse_fragment` fails.
 * @return A Tree with the parsed HTML nodes.
 */
Tree parse_fragment(const std::string& html,
                    const ParseFragmentOptions& opt = {});

}  // namespace myhtmlpp

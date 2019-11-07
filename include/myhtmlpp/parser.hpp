#pragma once

#include "tree.hpp"

#include <cstddef>
#include <myhtml/api.h>
#include <string>

namespace myhtmlpp {

/**
 * @brief Parses a HTML string into a Tree structure with the given options.
 *
 * @param html The HTML code that will be parsed.
 * @throw std::runtime_error if one of myhtml_init, myhtml_tree_init
 *        or myhtml_parse does not return MyHTML_STATUS_OK.
 * @return A Tree with the parsed HTML nodes.
 */
Tree parse(const std::string& html, myhtml_options opt = MyHTML_OPTIONS_DEFAULT,
           size_t thread_count = 1, size_t queue_size = 0);

/**
 * @brief Parses a fragment of a HTML string into a Tree structure.
 *
 * @param html The HTML code that will be parsed.
 * @throw std::runtime_error if one of myhtml_init, myhtml_tree_init
 *        or myhtml_parse_fragment does not return MyHTML_STATUS_OK.
 * @return A Tree with the parsed HTML nodes.
 */
Tree parse_fragment(const std::string& html, myhtml_tag_id_t tag_id,
                    myhtml_namespace ns = MyHTML_NAMESPACE_HTML,
                    myhtml_options opt = MyHTML_OPTIONS_DEFAULT,
                    size_t thread_count = 1, size_t queue_size = 0);

}  // namespace myhtmlpp

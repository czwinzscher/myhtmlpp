#pragma once

#include "tree.hpp"

#include <myhtml/api.h>
#include <string>

namespace myhtmlpp {

Tree parse(const std::string& html);
Tree parse_with_options(const std::string& html, myhtml_options opt,
                        size_t thread_count, size_t queue_size);
Tree parse_fragment(const std::string& html, myhtml_tag_id_t tag_id,
                    myhtml_namespace ns);
Tree parse_fragment_with_options(const std::string& html,
                                 myhtml_tag_id_t tag_id, myhtml_namespace ns,
                                 myhtml_options opt, size_t thread_count,
                                 size_t queue_size);

}  // namespace myhtmlpp

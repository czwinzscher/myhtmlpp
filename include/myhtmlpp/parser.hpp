#pragma once

#include "collection.hpp"
#include "node.hpp"
#include "tree.hpp"

#include <myhtml/api.h>
#include <string>

namespace myhtmlpp {

class Parser {
public:
    Parser();
    ~Parser();

    [[nodiscard]] bool good() const;

    Tree parse(const std::string& html);
    Tree parse_with_options(const std::string& html, myhtml_options opt,
                            size_t thread_count, size_t queue_size);
    Tree parse_fragment(const std::string& html, myhtml_tag_id_t tag_id,
                        myhtml_namespace ns);
    Tree parse_fragment_with_options(const std::string& html,
                                     myhtml_tag_id_t tag_id,
                                     myhtml_namespace ns, myhtml_options opt,
                                     size_t thread_count, size_t queue_size);

private:
    void reset();

    myhtml_t* m_raw_myhtml;
};

}  // namespace myhtmlpp

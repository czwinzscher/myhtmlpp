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

    myhtmlpp::Tree parse(const std::string& html);
    myhtmlpp::Tree parse_with_options(const std::string& html,
                                      myhtml_options opt, size_t thread_count,
                                      size_t queue_size);

private:
    void reset();

    myhtml_t* m_raw_myhtml;
};

}  // namespace myhtmlpp

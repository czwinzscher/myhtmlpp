#include "myhtmlpp/error.hpp"

#include <mycore/myosi.h>
#include <string>

myhtmlpp::myhtml_error::myhtml_error(mystatus_t status, const char* what)
    : m_status(status), m_error(what) {}

const char* myhtmlpp::myhtml_error::what() const noexcept {
    return m_error.what();
}

mystatus_t myhtmlpp::myhtml_error::status_code() const { return m_status; }

myhtmlpp::init_error::init_error(mystatus_t status)
    : myhtml_error(status,
                   ("myhtml_init failed with status " + std::to_string(status))
                       .c_str()) {}

myhtmlpp::tree_init_error::tree_init_error(mystatus_t status)
    : myhtml_error(status, ("myhtml_tree_init failed with status " +
                            std::to_string(status))
                               .c_str()) {}

myhtmlpp::parse_error::parse_error(mystatus_t status)
    : myhtml_error(
          status,
          ("parsing failed with status " + std::to_string(status)).c_str()) {}

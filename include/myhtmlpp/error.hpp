#pragma once

#include <exception>
#include <mycore/myosi.h>
#include <stdexcept>

namespace myhtmlpp {

/// A general exception base class.
class myhtml_error : public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override;

    [[nodiscard]] mystatus_t status_code() const;

protected:
    myhtml_error(mystatus_t status_code, const char* what);

private:
    mystatus_t m_status;
    std::runtime_error m_error;
};

/// Exception indicating that `myhtml_init` failed.
class init_error : public myhtml_error {
public:
    explicit init_error(mystatus_t status);
};

/// Exception indicating that `myhtml_tree_init` failed.
class tree_init_error : public myhtml_error {
public:
    explicit tree_init_error(mystatus_t status);
};

/// Exception indicating that `myhtml_parse` or `myhtml_parse_fragment` failed.
class parse_error : public myhtml_error {
public:
    explicit parse_error(mystatus_t status);
};

}  // namespace myhtmlpp

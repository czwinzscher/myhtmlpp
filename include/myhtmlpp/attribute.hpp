#pragma once

#include <myhtml/api.h>
#include <optional>
#include <string>

namespace myhtmlpp {

class Attribute {
public:
    explicit Attribute(myhtml_tree_attr_t* raw_attribute);

    [[nodiscard]] bool operator==(const Attribute& other) const;
    [[nodiscard]] bool operator!=(const Attribute& other) const;

    [[nodiscard]] std::string key() const;
    [[nodiscard]] std::string value() const;
    [[nodiscard]] myhtml_namespace_t ns() const;

    void set_ns(myhtml_namespace_t new_ns);

    [[nodiscard]] std::optional<Attribute> previous() const;
    [[nodiscard]] std::optional<Attribute> next() const;

private:
    myhtml_tree_attr_t* m_raw_attribute;
};

}  // namespace myhtmlpp

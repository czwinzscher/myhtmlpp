#include "myhtmlpp/attribute.hpp"

#include <myhtml/api.h>
#include <optional>
#include <string>

myhtmlpp::Attribute::Attribute(myhtml_tree_attr_t* raw_attribute)
    : m_raw_attribute(raw_attribute) {}

std::string myhtmlpp::Attribute::key() const {
    if (auto k = myhtml_attribute_key(m_raw_attribute, nullptr)) {
        return k;
    }

    return "";
}

std::string myhtmlpp::Attribute::value() const {
    if (auto k = myhtml_attribute_value(m_raw_attribute, nullptr)) {
        return k;
    }

    return "";
}

myhtml_namespace_t myhtmlpp::Attribute::ns() const {
    return myhtml_attribute_namespace(m_raw_attribute);
}

void myhtmlpp::Attribute::set_ns(myhtml_namespace_t new_ns) {
    myhtml_attribute_namespace_set(m_raw_attribute, new_ns);
}

std::optional<myhtmlpp::Attribute> myhtmlpp::Attribute::previous() const {
    if (auto raw_prev = myhtml_attribute_prev(m_raw_attribute)) {
        return Attribute(raw_prev);
    }

    return std::nullopt;
}

std::optional<myhtmlpp::Attribute> myhtmlpp::Attribute::next() const {
    if (auto raw_next = myhtml_attribute_next(m_raw_attribute)) {
        return Attribute(raw_next);
    }

    return std::nullopt;
}

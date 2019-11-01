#include "myhtmlpp/attribute.hpp"

#include "utils.hpp"

#include <myhtml/api.h>
#include <optional>
#include <string>

myhtmlpp::Attribute::Attribute(myhtml_tree_attr_t* raw_attribute)
    : m_raw_attribute(raw_attribute) {}

bool myhtmlpp::Attribute::operator==(const Attribute& other) const {
    return m_raw_attribute == other.m_raw_attribute;
}

bool myhtmlpp::Attribute::operator!=(const Attribute& other) const {
    return !operator==(other);
}

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
    return optional_helper<Attribute>(myhtml_attribute_prev, m_raw_attribute);
}

std::optional<myhtmlpp::Attribute> myhtmlpp::Attribute::next() const {
    return optional_helper<Attribute>(myhtml_attribute_next, m_raw_attribute);
}

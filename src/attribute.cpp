#include "myhtmlpp/attribute.hpp"

#include "myhtmlpp/constants.hpp"
#include "utils.hpp"

#include <myhtml/tree.h>
#include <optional>
#include <string>

myhtmlpp::Attribute::Attribute(myhtml_tree_attr_t* raw_attribute)
    : m_raw_attribute(raw_attribute) {}

myhtmlpp::Attribute::Attribute(Attribute&& other) noexcept
    : m_raw_attribute(other.m_raw_attribute) {
    other.m_raw_attribute = nullptr;
}

myhtmlpp::Attribute&
myhtmlpp::Attribute::operator=(Attribute&& other) noexcept {
    m_raw_attribute = other.m_raw_attribute;

    other.m_raw_attribute = nullptr;

    return *this;
}

myhtmlpp::Attribute::operator bool() const noexcept { return good(); }

bool myhtmlpp::Attribute::operator==(const Attribute& other) const {
    return m_raw_attribute == other.m_raw_attribute;
}

bool myhtmlpp::Attribute::operator!=(const Attribute& other) const {
    return !operator==(other);
}

bool myhtmlpp::Attribute::good() const { return m_raw_attribute != nullptr; }

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

myhtmlpp::NAMESPACE myhtmlpp::Attribute::get_namespace() const {
    return static_cast<NAMESPACE>(myhtml_attribute_namespace(m_raw_attribute));
}

std::optional<myhtmlpp::Attribute> myhtmlpp::Attribute::previous() const {
    return optional_helper<Attribute>(myhtml_attribute_prev, m_raw_attribute);
}

std::optional<myhtmlpp::Attribute> myhtmlpp::Attribute::next() const {
    return optional_helper<Attribute>(myhtml_attribute_next, m_raw_attribute);
}

std::ostream& myhtmlpp::operator<<(std::ostream& os,
                                   const myhtmlpp::Attribute& attr) {
    std::string res = attr.key() + "=\"" + attr.value() + "\"";
    os << res;

    return os;
}

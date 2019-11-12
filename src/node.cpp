#include "myhtmlpp/node.hpp"

#include "myhtmlpp/attribute.hpp"
#include "myhtmlpp/constants.hpp"
#include "utils.hpp"

#include <cstring>
#include <mycore/myosi.h>
#include <mycore/mystring.h>
#include <myhtml/myhtml.h>
#include <myhtml/serialization.h>
#include <myhtml/tree.h>
#include <optional>
#include <string>
#include <utility>
#include <vector>

myhtmlpp::Node::Node(myhtml_tree_node_t* raw_node) : m_raw_node(raw_node) {}

myhtmlpp::Node::Node(Node&& other) noexcept : m_raw_node(other.m_raw_node) {
    other.m_raw_node = nullptr;
}

myhtmlpp::Node& myhtmlpp::Node::operator=(Node&& other) noexcept {
    m_raw_node = other.m_raw_node;

    other.m_raw_node = nullptr;

    return *this;
}

bool myhtmlpp::Node::operator==(const Node& other) const {
    return m_raw_node == other.m_raw_node;
}

bool myhtmlpp::Node::operator!=(const Node& other) const {
    return !operator==(other);
}

std::string myhtmlpp::Node::operator[](const std::string& key) const noexcept {
    myhtml_tree_attr_t* attr =
        myhtml_attribute_by_key(m_raw_node, key.c_str(), strlen(key.c_str()));

    return myhtml_attribute_value(attr, nullptr);
}

bool myhtmlpp::Node::good() const { return m_raw_node != nullptr; }

std::string myhtmlpp::Node::html() const {
    mycore_string_raw_t str = {nullptr, 0, 0};
    myhtml_serialization_node_buffer(m_raw_node, &str);

    std::string res = str.data != nullptr ? str.data : "";

    mycore_string_raw_destroy(&str, false);

    return res;
}

std::string myhtmlpp::Node::html_deep() const {
    mycore_string_raw_t str = {nullptr, 0, 0};
    myhtml_serialization_tree_buffer(m_raw_node, &str);

    std::string res = str.data != nullptr ? str.data : "";

    mycore_string_raw_destroy(&str, false);

    return res;
}

std::string myhtmlpp::Node::text() const {
    const char* raw_text = myhtml_node_text(m_raw_node, nullptr);

    return raw_text != nullptr ? raw_text : "";
}

std::string myhtmlpp::Node::inner_text() const {
    std::string res;

    if (tag_id() == TAG::TEXT_) {
        res += text();
    }

    for (const auto& ch : children()) {
        res += ch.inner_text();
    }

    return res;
}

myhtmlpp::TAG myhtmlpp::Node::tag_id() const {
    return static_cast<TAG>(myhtml_node_tag_id(m_raw_node));
}

std::string myhtmlpp::Node::tag_name() const {
    const char* tag_name = myhtml_tag_name_by_id(
        m_raw_node->tree, myhtml_node_tag_id(m_raw_node), nullptr);

    return tag_name != nullptr ? tag_name : "";
}

myhtmlpp::NAMESPACE myhtmlpp::Node::get_namespace() const {
    return static_cast<NAMESPACE>(myhtml_node_namespace(m_raw_node));
}

bool myhtmlpp::Node::is_void_element() const {
    if (!good()) {
        return false;
    }

    return myhtml_node_is_void_element(m_raw_node);
}

bool myhtmlpp::Node::is_text_node() const {
    return tag_id() == TAG::TEXT_ || tag_id() == TAG::COMMENT_ ||
           tag_id() == TAG::STYLE;
}

std::optional<myhtmlpp::Node> myhtmlpp::Node::first_child() const {
    return optional_helper<Node>(myhtml_node_child, m_raw_node);
}

std::optional<myhtmlpp::Node> myhtmlpp::Node::last_child() const {
    return optional_helper<Node>(myhtml_node_last_child, m_raw_node);
}

std::optional<myhtmlpp::Node> myhtmlpp::Node::previous() const {
    return optional_helper<Node>(myhtml_node_prev, m_raw_node);
}

std::optional<myhtmlpp::Node> myhtmlpp::Node::next() const {
    return optional_helper<Node>(myhtml_node_next, m_raw_node);
}

std::optional<myhtmlpp::Node> myhtmlpp::Node::parent() const {
    return optional_helper<Node>(myhtml_node_parent, m_raw_node);
}

std::vector<myhtmlpp::Node> myhtmlpp::Node::children() const {
    std::vector<myhtmlpp::Node> res;

    myhtml_tree_node_t* raw_child = myhtml_node_child(m_raw_node);
    while (raw_child != nullptr) {
        res.emplace_back(raw_child);
        raw_child = myhtml_node_next(raw_child);
    }

    return res;
}

std::vector<myhtmlpp::Node> myhtmlpp::Node::siblings() const {
    std::vector<myhtmlpp::Node> res;

    myhtml_tree_node_t* raw_prev = myhtml_node_prev(m_raw_node);
    while (raw_prev != nullptr) {
        res.emplace_back(raw_prev);
        raw_prev = myhtml_node_prev(raw_prev);
    }

    myhtml_tree_node_t* raw_next = myhtml_node_next(m_raw_node);
    while (raw_next != nullptr) {
        res.emplace_back(raw_next);
        raw_next = myhtml_node_next(raw_next);
    }

    return res;
}

std::optional<std::string> myhtmlpp::Node::at(const std::string& key) const {
    if (!good()) {
        return std::nullopt;
    }

    myhtml_tree_attr_t* attr =
        myhtml_attribute_by_key(m_raw_node, key.c_str(), strlen(key.c_str()));

    if (attr == nullptr) {
        return std::nullopt;
    }

    const char* val = myhtml_attribute_value(attr, nullptr);

    return val != nullptr ? std::make_optional(val) : std::nullopt;
}

bool myhtmlpp::Node::has_attributes() const {
    return first_attribute() != std::nullopt;
}

bool myhtmlpp::Node::has_attribute(const std::string& key) const {
    myhtml_tree_attr_t* attr =
        myhtml_attribute_by_key(m_raw_node, key.c_str(), strlen(key.c_str()));

    return attr != nullptr;
}

std::optional<myhtmlpp::Attribute> myhtmlpp::Node::first_attribute() const {
    return optional_helper<Attribute>(myhtml_node_attribute_first, m_raw_node);
}

std::optional<myhtmlpp::Attribute> myhtmlpp::Node::last_attribute() const {
    return optional_helper<Attribute>(myhtml_node_attribute_last, m_raw_node);
}

std::vector<myhtmlpp::Attribute> myhtmlpp::Node::attributes() const {
    return std::vector(begin(), end());
}

// Iterator
myhtmlpp::Node::Iterator::Iterator(Attribute attr) : m_attr(std::move(attr)) {}

myhtmlpp::Node::Iterator::reference myhtmlpp::Node::Iterator::operator*() {
    return m_attr;
}

myhtmlpp::Node::Iterator& myhtmlpp::Node::Iterator::operator++() {
    if (auto next = m_attr.next()) {
        m_attr = next.value();
    } else {
        m_attr = Attribute(nullptr);
    }

    return *this;
}

bool myhtmlpp::Node::Iterator::operator==(const Iterator& other) const {
    return m_attr == other.m_attr;
}

bool myhtmlpp::Node::Iterator::operator!=(const Iterator& other) const {
    return !operator==(other);
}

myhtmlpp::Node::Iterator myhtmlpp::Node::begin() noexcept {
    return Iterator(Attribute(myhtml_node_attribute_first(m_raw_node)));
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
myhtmlpp::Node::Iterator myhtmlpp::Node::end() noexcept {
    return Iterator(Attribute(nullptr));
}

// ConstIterator
myhtmlpp::Node::ConstIterator::ConstIterator(Attribute attr)
    : m_attr(std::move(attr)) {}

myhtmlpp::Node::ConstIterator::reference
    myhtmlpp::Node::ConstIterator::operator*() const {
    return m_attr;
}

myhtmlpp::Node::ConstIterator& myhtmlpp::Node::ConstIterator::operator++() {
    if (auto next = m_attr.next()) {
        m_attr = next.value();
    } else {
        m_attr = Attribute(nullptr);
    }

    return *this;
}

bool myhtmlpp::Node::ConstIterator::operator==(
    const ConstIterator& other) const {
    return m_attr == other.m_attr;
}

bool myhtmlpp::Node::ConstIterator::operator!=(
    const ConstIterator& other) const {
    return !operator==(other);
}

myhtmlpp::Node::ConstIterator myhtmlpp::Node::begin() const noexcept {
    return ConstIterator(Attribute(myhtml_node_attribute_first(m_raw_node)));
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
myhtmlpp::Node::ConstIterator myhtmlpp::Node::end() const noexcept {
    return ConstIterator(Attribute(nullptr));
}

myhtmlpp::Node::ConstIterator myhtmlpp::Node::cbegin() const noexcept {
    return begin();
}

myhtmlpp::Node::ConstIterator myhtmlpp::Node::cend() const noexcept {
    return end();
}

std::ostream& myhtmlpp::operator<<(std::ostream& os, const myhtmlpp::Node& n) {
    os << n.html();

    return os;
}

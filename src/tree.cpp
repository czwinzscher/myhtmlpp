#include "myhtmlpp/tree.hpp"

#include "myhtmlpp/constants.hpp"
#include "myhtmlpp/node.hpp"

#include <algorithm>
#include <cstring>
#include <iterator>
#include <modest/finder/finder.h>
#include <modest/finder/myosi.h>
#include <mycore/myosi.h>
#include <mycore/mystring.h>
#include <mycss/entry.h>
#include <mycss/mycss.h>
#include <mycss/myosi.h>
#include <mycss/selectors/init.h>
#include <mycss/selectors/list.h>
#include <mycss/selectors/myosi.h>
#include <myencoding/myosi.h>
#include <myhtml/serialization.h>
#include <myhtml/tree.h>
#include <string>
#include <utility>
#include <vector>

myhtmlpp::Tree::Tree(myhtml_t* raw_myhtml, myhtml_tree_t* raw_tree)
    : m_raw_myhtml(raw_myhtml), m_raw_tree(raw_tree) {}

myhtmlpp::Tree::~Tree() {
    myhtml_tree_destroy(m_raw_tree);
    myhtml_destroy(m_raw_myhtml);
}

myhtmlpp::Tree::Tree(Tree&& other) noexcept
    : m_raw_myhtml(other.m_raw_myhtml), m_raw_tree(other.m_raw_tree) {
    other.m_raw_tree = nullptr;
    other.m_raw_myhtml = nullptr;
}

myhtmlpp::Tree& myhtmlpp::Tree::operator=(Tree&& other) noexcept {
    // if the tree is not empty and the other tree is different
    // we have to release the resources of the tree.
    if (m_raw_myhtml != nullptr && m_raw_myhtml != other.m_raw_myhtml) {
        myhtml_destroy(m_raw_myhtml);
    }

    if (m_raw_tree != nullptr && m_raw_tree != other.m_raw_tree) {
        myhtml_tree_destroy(m_raw_tree);
    }

    m_raw_myhtml = other.m_raw_myhtml;
    m_raw_tree = other.m_raw_tree;

    other.m_raw_myhtml = nullptr;
    other.m_raw_tree = nullptr;

    return *this;
}

bool myhtmlpp::Tree::good() const {
    return m_raw_tree != nullptr && m_raw_myhtml != nullptr;
}

myhtmlpp::Node myhtmlpp::Tree::document_node() const {
    return Node(myhtml_tree_get_document(m_raw_tree));
}

myhtmlpp::Node myhtmlpp::Tree::html_node() const {
    return Node(myhtml_tree_get_node_html(m_raw_tree));
}

myhtmlpp::Node myhtmlpp::Tree::head_node() const {
    return Node(myhtml_tree_get_node_head(m_raw_tree));
}

myhtmlpp::Node myhtmlpp::Tree::body_node() const {
    return Node(myhtml_tree_get_node_body(m_raw_tree));
}

std::string myhtmlpp::Tree::html() const {
    mycore_string_raw_t str = {nullptr, 0, 0};
    myhtml_serialization_tree_buffer(myhtml_tree_get_document(m_raw_tree),
                                     &str);

    return str.data != nullptr ? str.data : "";
}

std::vector<myhtmlpp::Node>
myhtmlpp::Tree::select(const std::string& selector) const {
    std::vector<Node> res;

    mycss_t* mycss = mycss_create();
    mystatus_t status = mycss_init(mycss);
    if (status != MyCSS_STATUS_OK) {
        return res;
    }

    mycss_entry_t* entry = mycss_entry_create();
    status = mycss_entry_init(mycss, entry);
    if (status != MyCSS_STATUS_OK) {
        return res;
    }

    modest_finder_t* finder = modest_finder_create_simple();

    mycss_selectors_list_t* list = mycss_selectors_parse(
        mycss_entry_selectors(entry), MyENCODING_UTF_8, selector.c_str(),
        strlen(selector.c_str()), &status);
    if (status != MyCSS_STATUS_OK) {
        return res;
    }

    myhtml_collection_t* collection = nullptr;
    modest_finder_by_selectors_list(finder, m_raw_tree->node_html, list,
                                    &collection);

    if (collection != nullptr) {
        for (size_t i = 0; i < collection->length; ++i) {
            res.emplace_back(collection->list[i]);  // NOLINT
        }
    }

    myhtml_collection_destroy(collection);

    mycss_selectors_list_destroy(mycss_entry_selectors(entry), list, true);

    modest_finder_destroy(finder, true);

    mycss_entry_destroy(entry, true);
    mycss_destroy(mycss, true);

    return res;
}

std::vector<myhtmlpp::Node>
myhtmlpp::Tree::find_by_tag(const std::string& tag) const {
    std::vector<Node> res;
    std::copy_if(begin(), end(), std::back_inserter(res),
                 [&](const auto& node) { return node.tag_name() == tag; });

    return res;
}

std::vector<myhtmlpp::Node>
myhtmlpp::Tree::find_by_tag(myhtmlpp::TAG tag) const {
    std::vector<Node> res;
    std::copy_if(begin(), end(), std::back_inserter(res),
                 [&](const auto& node) { return node.tag_id() == tag; });

    return res;
}

std::vector<myhtmlpp::Node>
myhtmlpp::Tree::find_by_class(const std::string& cl) const {
    std::vector<Node> res;
    std::copy_if(begin(), end(), std::back_inserter(res),
                 [&](const auto& node) {
                     if (auto cl_value = node.at("class")) {
                         return cl_value.value() == cl;
                     }

                     return false;
                 });

    return res;
}

std::vector<myhtmlpp::Node>
myhtmlpp::Tree::find_by_id(const std::string& id) const {
    std::vector<Node> res;
    std::copy_if(begin(), end(), std::back_inserter(res),
                 [&](const auto& node) {
                     if (auto id_value = node.at("id")) {
                         return id_value.value() == id;
                     }

                     return false;
                 });

    return res;
}

std::vector<myhtmlpp::Node>
myhtmlpp::Tree::find_by_attr(const std::string& key,
                             const std::string& val) const {
    std::vector<Node> res;
    std::copy_if(begin(), end(), std::back_inserter(res),
                 [&](const auto& node) {
                     if (auto attr = node.at(key)) {
                         return attr.value() == val;
                     }

                     return false;
                 });

    return res;
}

// Iterator
myhtmlpp::Tree::Iterator::Iterator(Node node) : m_node(std::move(node)) {}

myhtmlpp::Tree::Iterator::reference myhtmlpp::Tree::Iterator::operator*() {
    return m_node;
}

myhtmlpp::Tree::Iterator& myhtmlpp::Tree::Iterator::operator++() {
    std::vector<Node> children = m_node.children();
    m_stack.insert(m_stack.end(), children.rbegin(), children.rend());

    if (m_stack.empty()) {
        m_node = Node(nullptr);
        return *this;
    }

    m_node = m_stack.back();
    m_stack.pop_back();

    return *this;

    // Node new_node(nullptr);

    // if (auto child = m_node.first_child()) {
    //     new_node = child.value();
    // } else if (auto next = m_node.next()) {
    //     new_node = next.value();
    // } else {
    //     while (auto parent = m_node.parent()) {
    //         m_node = parent.value();

    //         if (auto parent_next = m_node.next()) {
    //             new_node = parent_next.value();
    //             break;
    //         }
    //     }
    // }

    // m_node = new_node;

    // return *this;
}

bool myhtmlpp::Tree::Iterator::operator==(const Iterator& other) const {
    return m_node == other.m_node;
}

bool myhtmlpp::Tree::Iterator::operator!=(const Iterator& other) const {
    return !operator==(other);
}

myhtmlpp::Tree::Iterator myhtmlpp::Tree::begin() noexcept {
    return Iterator(document_node());
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
myhtmlpp::Tree::Iterator myhtmlpp::Tree::end() noexcept {
    return Iterator(Node(nullptr));
}

// ConstIterator
myhtmlpp::Tree::ConstIterator::ConstIterator(Node node)
    : m_node(std::move(node)) {}

myhtmlpp::Tree::ConstIterator::reference
    myhtmlpp::Tree::ConstIterator::operator*() const {
    return m_node;
}

myhtmlpp::Tree::ConstIterator& myhtmlpp::Tree::ConstIterator::operator++() {
    std::vector<Node> children = m_node.children();
    m_stack.insert(m_stack.end(), children.rbegin(), children.rend());

    if (m_stack.empty()) {
        m_node = Node(nullptr);
        return *this;
    }

    m_node = m_stack.back();
    m_stack.pop_back();

    return *this;

    // Node new_node(nullptr);

    // if (auto child = m_node.first_child()) {
    //     new_node = child.value();
    // } else if (auto next = m_node.next()) {
    //     new_node = next.value();
    // } else {
    //     while(auto parent = m_node.parent()) {
    //         m_node = parent.value();

    //         if (auto parent_next = m_node.next()) {
    //             new_node = parent_next.value();
    //             break;
    //         }
    //     }
    // }

    // m_node = new_node;

    // return *this;
}

bool myhtmlpp::Tree::ConstIterator::operator==(
    const ConstIterator& other) const {
    return m_node == other.m_node;
}

bool myhtmlpp::Tree::ConstIterator::operator!=(
    const ConstIterator& other) const {
    return !operator==(other);
}

myhtmlpp::Tree::ConstIterator myhtmlpp::Tree::begin() const noexcept {
    return ConstIterator(document_node());
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
myhtmlpp::Tree::ConstIterator myhtmlpp::Tree::end() const noexcept {
    return ConstIterator(Node(nullptr));
}

myhtmlpp::Tree::ConstIterator myhtmlpp::Tree::cbegin() const noexcept {
    return begin();
}

myhtmlpp::Tree::ConstIterator myhtmlpp::Tree::cend() const noexcept {
    return end();
}

std::ostream& myhtmlpp::operator<<(std::ostream& os, const Tree& t) {
    os << t.html();

    return os;
}

#pragma once

#include "node.hpp"

#include <myhtml/api.h>
#include <ostream>
#include <string>

namespace myhtmlpp {

class Tree {
public:
    Tree(myhtml_t* raw_myhtml, myhtml_tree_t* raw_tree);
    ~Tree();

    [[nodiscard]] Node document_node() const;
    [[nodiscard]] Node html_node() const;
    [[nodiscard]] Node head_node() const;
    [[nodiscard]] Node body_node() const;

    [[nodiscard]] std::string html_string() const;
    [[nodiscard]] std::string pretty_html_string() const;

    Node create_node(myhtml_tag_id_t tag_id, myhtml_namespace_t ns);

    class Iterator {
    public:
        explicit Iterator(const Node& node);

        Node& operator*() { return m_node; }

        Iterator& operator++();

        bool operator!=(const Iterator& other) const {
            return m_node != other.m_node;
        }

    private:
        Node m_node;
    };

    class ConstIterator {
    public:
        explicit ConstIterator(const Node& node);

        Node& operator*() { return m_node; }

        ConstIterator& operator++();

        bool operator!=(const ConstIterator& other) const {
            return m_node != other.m_node;
        }

    private:
        Node m_node;
    };

    Iterator begin() noexcept;
    Iterator end() noexcept;

    [[nodiscard]] ConstIterator begin() const noexcept;
    [[nodiscard]] ConstIterator end() const noexcept;

private:
    myhtml_t* m_raw_myhtml;
    myhtml_tree_t* m_raw_tree;
};

std::ostream& operator<<(std::ostream& os, const Tree& t);

}  // namespace myhtmlpp

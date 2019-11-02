#pragma once

#include "node.hpp"

#include <cstddef>
#include <myhtml/api.h>
#include <ostream>
#include <string>
#include <vector>

namespace myhtmlpp {

class Tree {
public:
    Tree(myhtml_t* raw_myhtml, myhtml_tree_t* raw_tree);
    ~Tree();
    Tree(const Tree&) = default;
    Tree& operator=(const Tree&) = default;
    Tree(Tree&&) = default;
    Tree& operator=(Tree&&) = default;

    [[nodiscard]] Node document_node() const;
    [[nodiscard]] Node html_node() const;
    [[nodiscard]] Node head_node() const;
    [[nodiscard]] Node body_node() const;

    [[nodiscard]] std::string html() const;
    [[nodiscard]] std::string pretty_html(int indent = 4) const;

    Node create_node(myhtml_tag_id_t tag_id, myhtml_namespace_t ns);

    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Node;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        explicit Iterator(const Node& node);

        reference operator*() { return m_node; }

        Iterator& operator++();

        bool operator!=(const Iterator& other) const {
            return m_node != other.m_node;
        }

    private:
        Node m_node;
        std::vector<Node> m_stack;
    };

    class ConstIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Node;
        using difference_type = std::ptrdiff_t;
        using pointer = const value_type*;
        using reference = const value_type&;

        explicit ConstIterator(const Node& node);

        reference operator*() { return m_node; }

        ConstIterator& operator++();

        bool operator!=(const ConstIterator& other) const {
            return m_node != other.m_node;
        }

    private:
        Node m_node;
        std::vector<Node> m_stack;
    };

    Iterator begin() noexcept;
    Iterator end() noexcept;

    [[nodiscard]] ConstIterator begin() const noexcept;
    [[nodiscard]] ConstIterator end() const noexcept;

    [[nodiscard]] ConstIterator cbegin() const noexcept;
    [[nodiscard]] ConstIterator cend() const noexcept;

private:
    myhtml_t* m_raw_myhtml;
    myhtml_tree_t* m_raw_tree;
};

std::ostream& operator<<(std::ostream& os, const Tree& t);

}  // namespace myhtmlpp

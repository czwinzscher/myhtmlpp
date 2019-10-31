#pragma once

#include "node.hpp"

#include <cstddef>
#include <myhtml/api.h>
#include <ostream>
#include <string>

namespace myhtmlpp {

class Tree {
public:
    Tree(myhtml_t* raw_myhtml, myhtml_tree_t* raw_tree);
    ~Tree();

    friend std::ostream& operator<<(std::ostream& os, const Tree& t);

    [[nodiscard]] Node document_node() const;
    [[nodiscard]] Node html_node() const;
    [[nodiscard]] Node head_node() const;
    [[nodiscard]] Node body_node() const;

    Node create_node(myhtml_tag_id_t tag_id, myhtml_namespace_t ns);

    class Iterator {
    public:
        Iterator(myhtml_tree_t* t, const Node& node);

        constexpr Node& operator*() { return m_node; }

        Iterator& operator++();

        constexpr bool operator!=(const Iterator& other) const {
            return m_data != other.m_data || m_node != other.m_node;
        }

    private:
        myhtml_tree_t* m_data;
        Node m_node;
    };

    class ConstIterator {
    public:
        ConstIterator(myhtml_tree_t* t, const Node& node);

        constexpr Node& operator*() { return m_node; }

        ConstIterator& operator++();

        constexpr bool operator!=(const ConstIterator& other) const {
            return m_data != other.m_data || m_node != other.m_node;
        }

    private:
        myhtml_tree_t* m_data;
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

}  // namespace myhtmlpp

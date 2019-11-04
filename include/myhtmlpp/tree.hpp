#pragma once

#include "node.hpp"

#include <cstddef>
#include <myhtml/api.h>
#include <ostream>
#include <string>
#include <vector>

namespace myhtmlpp {

/// A HTML Tree class
class Tree {
public:
    /**
     * @brief Tree constructor.
     *
     * Initialises m_raw_myhtml with `raw_myhtml` and
     * m_raw_tree with `raw_tree`.
     *
     * @param raw_myhtml A pointer to a myhtml struct.
     * @param raw_tree A pointer to a myhtml_tree struct.
     */
    Tree(myhtml_t* raw_myhtml, myhtml_tree_t* raw_tree);

    /**
     * @brief Tree destructor.
     *
     * Calls `myhtml_tree_destroy` and `myhtml_destroy`.
     */
    ~Tree();

    Tree(const Tree&) = default;
    Tree& operator=(const Tree&) = default;
    Tree(Tree&&) = default;
    Tree& operator=(Tree&&) = default;

    /**
     * @brief Check if myhtml and myhtml_tree pointers are not nullptr.
     *
     * @return Whether m_raw_myhtml and m_raw_tree are != nullptr.
     */
    [[nodiscard]] bool good() const;

    /**
     * @brief Returns the document node of the tree.
     *
     * @return The document node of the tree.
     */
    [[nodiscard]] Node document_node() const;

    /**
     * @brief Returns the html node of the tree.
     *
     * @return The html node of the tree; i.e. the node with the <html> tag.
     */
    [[nodiscard]] Node html_node() const;

    /**
     * @brief Returns the head node of the tree.
     *
     * @return The head node of the tree; i.e. the node with the <head> tag.
     */
    [[nodiscard]] Node head_node() const;

    /**
     * @brief Returns the body node of the tree.
     *
     * @return The body node of the tree; i.e. the node with the <body> tag.
     */
    [[nodiscard]] Node body_node() const;

    /**
     * Returns the HTML representation of the tree
     *
     * @return a string of the HTML code representing the tree.
     */
    [[nodiscard]] std::string html() const;

    /// Tries to return a pretty representation of the tree
    [[nodiscard]] std::string pretty_html(int indent = 4) const;

    /**
     * Creates a new node in the tree.
     *
     * @param tag_id the tag of the created node.
     * @param ns the namespace of the created node.
     *
     * @return the created node.
     */
    Node create_node(myhtml_tag_id_t tag_id,
                     myhtml_namespace_t ns = MyHTML_NAMESPACE_HTML);

    /// A Tree Iterator class.
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Node;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        explicit Iterator(const Node& node);

        reference operator*();

        Iterator& operator++();

        bool operator!=(const Iterator& other) const;

    private:
        Node m_node;
        std::vector<Node> m_stack;
    };

    /// A Tree ConstIterator class.
    class ConstIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Node;
        using difference_type = std::ptrdiff_t;
        using pointer = const value_type*;
        using reference = const value_type&;

        explicit ConstIterator(const Node& node);

        reference operator*();

        ConstIterator& operator++();

        bool operator!=(const ConstIterator& other) const;

    private:
        Node m_node;
        std::vector<Node> m_stack;
    };

    /**
     * @brief Returns an iterator to the first node.
     *
     * @return Iterator to first node if exists,
     *         Iterator to `Node(nullptr)` otherwhise.
     */
    Iterator begin() noexcept;

    /**
     * @brief Returns an iterator to after the last node.
     *
     * @return Iterator to `Node(nullptr)` otherwhise.
     */
    Iterator end() noexcept;

    /**
     * @brief Returns a const iterator to the first node.
     *
     * @return ConstIterator to first node if exists,
     *         ConstIterator to `Node(nullptr)` otherwhise.
     */
    [[nodiscard]] ConstIterator begin() const noexcept;

    /**
     * @brief Returns an const iterator to after the last node.
     *
     * @return ConstIterator to `Node(nullptr)` otherwhise.
     */
    [[nodiscard]] ConstIterator end() const noexcept;

    /**
     * @brief Returns a const iterator to the first node.
     *
     * @return ConstIterator to first node if exists,
     *         ConstIterator to `Node(nullptr)` otherwhise.
     */
    [[nodiscard]] ConstIterator cbegin() const noexcept;

    /**
     * @brief Returns an const iterator to after the last node.
     *
     * @return ConstIterator to `Node(nullptr)` otherwhise.
     */
    [[nodiscard]] ConstIterator cend() const noexcept;

private:
    /// Pointer to the underlying myhtml struct.
    myhtml_t* m_raw_myhtml;

    /// Pointer to the underlying myhtml tree struct.
    myhtml_tree_t* m_raw_tree;
};

/**
 * @brief Print the tree.
 */
std::ostream& operator<<(std::ostream& os, const Tree& t);

}  // namespace myhtmlpp

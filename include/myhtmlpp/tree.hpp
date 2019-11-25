#pragma once

#include "constants.hpp"
#include "filter.hpp"
#include "node.hpp"

#include <iterator>
#include <myhtml/myhtml.h>
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

    Tree(const Tree&) = delete;
    Tree& operator=(const Tree&) = delete;

    Tree(Tree&& other) noexcept;
    Tree& operator=(Tree&& other) noexcept;

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
     * @brief Returns all nodes in the subtree of `scope_node`
     *
     * @param scope_node The scope node of the subtree.
     * @return A vector of all nodes in the subtree of `scope_node`.
     */
    [[nodiscard]] std::vector<Node> scope(const Node& scope_node) const;

    /**
     * @brief Returns the HTML representation of the tree
     *
     * @return a string of the HTML code representing the tree.
     */
    [[nodiscard]] std::string html() const;

    /**
     * @brief Returns all nodes in the tree that match the css selector
     *        `selector`.
     *
     * @param selector The css selector.
     * @return A vector of all nodes in the tree that match `selector`.
     */
    [[nodiscard]] std::vector<Node> select(const std::string& selector) const;

    /**
     * @brief Returns all nodes in the tree where the tag matches `tag`.
     *
     * @param tag The tag to search.
     * @return A vector of all nodes in the tree where
     *         `tag_name()` returns `tag`.
     */
    [[nodiscard]] std::vector<Node> find_by_tag(const std::string& tag) const;

    /**
     * @brief Returns all nodes in the subtree of `scope_node` where the tag
     *        matches `tag`.
     *
     * @param tag The tag to search.
     * @param scope_node The scope node where searching starts.
     * @return A vector of all nodes in the subtree of `scope_node` where
     *         `tag_name()` returns `tag`.
     */
    [[nodiscard]] std::vector<Node> find_by_tag(const std::string& tag,
                                                const Node& scope_node) const;
    /**
     * @brief Returns all nodes in the tree where the tag matches `tag`.
     *
     * @param tag The tag to search.
     * @param scope_node The scope node where searching starts.
     * @return A vector of all nodes in the tree where
     *         `tag_id()` returns `tag`.
     */
    [[nodiscard]] std::vector<Node> find_by_tag(TAG tag) const;

    /**
     * @brief Returns all nodes in the subtree of `scope_node` where the tag
     *        matches `tag`.
     *
     * @param tag The tag to search.
     * @param scope_node The scope node where searching starts.
     * @return A vector of all nodes in the subtree of `scope_node` where
     *         `tag_id()` returns `tag`.
     */
    [[nodiscard]] std::vector<Node> find_by_tag(TAG tag,
                                                const Node& scope_node) const;

    /**
     * @brief Returns all nodes in the tree where the class matches `cl`.
     *
     * @param cl The value of the class to search.
     * @return A vector of all nodes in the tree that have an attribute
     *         where key() returns \"class\" and value() returns `cl`.
     */
    [[nodiscard]] std::vector<Node> find_by_class(const std::string& cl) const;

    /**
     * @brief Returns all nodes in the subtree of `scope_node` where the class
     *        matches `cl`.
     *
     * @param cl The value of the class to search.
     * @param scope_node The scope node where searching starts.
     * @return A vector of all nodes in the subtree of `scope_node` that have an
     *         attribute where key() returns \"class\" and value() returns `cl`.
     */
    [[nodiscard]] std::vector<Node> find_by_class(const std::string& cl,
                                                  const Node& scope_node) const;

    /**
     * @brief Returns all nodes in the tree where the id matches `id`.
     *
     * @param id The value of the id to search.
     * @return A vector of all nodes in the tree that have an attribute
     *         where key() returns \"id\" and value() returns `id`.
     */
    [[nodiscard]] std::vector<Node> find_by_id(const std::string& id) const;

    /**
     * @brief Returns all nodes in the subtree of `scope_node` where the id
     *        matches `id`.
     *
     * @param id The value of the id to search.
     * @param scope_node The scope node where searching starts.
     * @return A vector of all nodes in the subtree of `scope_node` that have an
     *         attribute where key() returns \"id\" and value() returns `id`.
     */
    [[nodiscard]] std::vector<Node> find_by_id(const std::string& id,
                                               const Node& scope_node) const;

    /**
     * @brief Returns all nodes in the tree that have an attribute with key
     * `key` and value `value`.
     *
     * @param key The key of the attribute.
     * @param value The value of the attribute.
     * @return A vector of all nodes in the tree that have an attribute
     *         where key() returns `key` and value() returns `value`.
     */
    [[nodiscard]] std::vector<Node> find_by_attr(const std::string& key,
                                                 const std::string& val) const;

    /**
     * @brief Returns all nodes in the subtree of `scope_node` that have an
     *        attribute with key `key` and value `value`.
     *
     * @param key The key of the attribute.
     * @param value The value of the attribute.
     * @param scope_node The scope node where searching starts.
     * @return A vector of all nodes in the subtree of `scope_node` that have an
     *         attribute where key() returns `key` and value() returns `value`.
     */
    [[nodiscard]] std::vector<Node> find_by_attr(const std::string& key,
                                                 const std::string& val,
                                                 const Node& scope_node) const;

    /**
     * @brief Returns all nodes in the tree where `f` returns true.
     *
     * @param f The filter function.
     * @return A selection of all nodes in the tree where `f` returns true.
     */
    template <typename FilterFunc>
    [[nodiscard]] Filter<FilterFunc, Tree> filter(FilterFunc f) {
        return Filter(*this, f);
    }

    /// A Tree Iterator class.
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Node;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        explicit Iterator(Node node);

        reference operator*();

        Iterator& operator++();

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        Node m_node;
    };

    /// A Tree ConstIterator class.
    class ConstIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Node;
        using difference_type = std::ptrdiff_t;
        using pointer = const value_type*;
        using reference = const value_type&;

        explicit ConstIterator(Node node);

        reference operator*() const;

        ConstIterator& operator++();

        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;

    private:
        Node m_node;
    };

    /**
     * @brief Returns an iterator to the first node.
     *
     * @return Iterator to first node if exists,
     *         Iterator to `Node(nullptr)` otherwise.
     */
    Iterator begin() noexcept;

    /**
     * @brief Returns an iterator to after the last node.
     *
     * @return Iterator to `Node(nullptr)`.
     */
    Iterator end() noexcept;

    /**
     * @brief Returns a const iterator to the first node.
     *
     * @return ConstIterator to first node if exists,
     *         ConstIterator to `Node(nullptr)` otherwise.
     */
    [[nodiscard]] ConstIterator begin() const noexcept;

    /**
     * @brief Returns an const iterator to after the last node.
     *
     * @return ConstIterator to `Node(nullptr)`.
     */
    [[nodiscard]] ConstIterator end() const noexcept;

    /**
     * @brief Returns a const iterator to the first node.
     *
     * @return ConstIterator to first node if exists,
     *         ConstIterator to `Node(nullptr)` otherwise.
     */
    [[nodiscard]] ConstIterator cbegin() const noexcept;

    /**
     * @brief Returns an const iterator to after the last node.
     *
     * @return ConstIterator to `Node(nullptr)`.
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

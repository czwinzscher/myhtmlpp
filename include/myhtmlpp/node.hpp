#pragma once

#include "myhtmlpp/attribute.hpp"

#include <iterator>
#include <myhtml/api.h>
#include <optional>
#include <ostream>
#include <string>
#include <vector>

namespace myhtmlpp {

/// A HTML Node class.
class Node {
public:
    /**
     * @brief Node constructor.
     *
     * Initialises m_raw_node with the given raw_node.
     *
     * @param raw_node A pointer to a myhtml_tree_node.
     */
    explicit Node(myhtml_tree_node_t* raw_node);

    ~Node() = default;

    Node(const Node&) = default;
    Node& operator=(const Node&) = default;

    Node(Node&& other) noexcept;
    Node& operator=(Node&& other) noexcept;

    /**
     * @brief Check if two nodes are equal.
     *
     * @return Whether both nodes point to the same myhtml struct;
     *         i.e. m_raw_node == other.m_raw_node.
     */
    [[nodiscard]] bool operator==(const Node& other) const;

    /**
     * @brief Check if two nodes are not equal.
     *
     * @return Whether both nodes point to different myhtml structs;
     *         i.e. m_raw_node != other.m_raw_node.
     */
    [[nodiscard]] bool operator!=(const Node& other) const;

    /**
     * Returns an Attribute in the node with the key `key`.
     *
     * @param key the key of the attribute to access.
     * @return Attribute with the key `key` if it exists,
     *         Attribute that gets initialised with nullptr otherwhise.
     */
    [[nodiscard]] Attribute operator[](const std::string& key) const noexcept;

    /**
     * @brief Check if myhtml pointer is not nullptr.
     *
     * @return Whether m_raw_node is != nullptr.
     */
    [[nodiscard]] bool good() const;

    /**
     * @brief Returns a HTML representation of the node.
     *
     * @return A string with the HTML code.
     */
    [[nodiscard]] std::string html() const;

    /**
     * @brief Returns a HTML representation of the tree
     *        starting at the node.
     *
     * @return A string with the HTML code.
     */
    [[nodiscard]] std::string html_deep() const;

    /**
     * @brief Returns a string of the text in the node.
     *
     * @return A string with the text, an empty string if it doesn't have text.
     */
    [[nodiscard]] std::string text() const;

    /**
     * @brief Returns the tag id of the node.
     *
     * @return An enum member of myhtml_tag_id_t with the tag id of the node.
     */
    [[nodiscard]] myhtml_tag_id_t tag_id() const;

    /**
     * @brief Returns a string of the tag_id of the node.
     *
     * @return A string corresponding to the tag_id of the node.
     *
     * @see Node::tag_id
     */
    [[nodiscard]] std::string tag_string() const;

    /**
     * @brief Returns the namespace of the node.
     *
     * @return An enum member of myhtml_namespace_t
     *         with the namespace of the node.
     */
    [[nodiscard]] myhtml_namespace_t ns() const;

    /**
     * @brief Returns if the node is a void element or not.
     *
     * @return true if the node is a void element, false otherwhise.
     *
     * @see http://w3c.github.io/html-reference/syntax.html#void-elements
     */
    [[nodiscard]] bool is_void_element() const;

    /**
     * Set the namespace of the node.
     *
     * @param new_ns The new namespace.
     */
    void set_ns(myhtml_namespace_t new_ns);

    /**
     * @brief Returns the first child in the node.
     *
     * @return An optional with the first child node if it exists,
     *         std::nullopt otherwhise.
     */
    [[nodiscard]] std::optional<Node> first_child() const;

    /**
     * @brief Returns the last child in the node.
     *
     * @return An optional with the last child node if it exists,
     *         std::nullopt otherwhise.
     */
    [[nodiscard]] std::optional<Node> last_child() const;

    /**
     * @brief Returns the previous sibling of the node.
     *
     * @return An optional with the previous sibling node if it exists,
     *         std::nullopt otherwhise.
     */
    [[nodiscard]] std::optional<Node> previous() const;

    /**
     * @brief Returns the next sibling of the node.
     *
     * @return An optional with the next sibling node if it exists,
     *         std::nullopt otherwhise.
     */
    [[nodiscard]] std::optional<Node> next() const;

    /**
     * @brief Returns the parent of the node.
     *
     * @return An optional with the parent node if it exists,
     *         std::nullopt otherwhise.
     */
    [[nodiscard]] std::optional<Node> parent() const;

    /**
     * @brief Returns a vector of all children of the node.
     *
     * @return A vector of all children nodes.
     */
    [[nodiscard]] std::vector<Node> children() const;

    /**
     * @brief Adds the Node `node` as a child.
     *
     * If the node where it will get added already has children,
     * it will be inserted after the last child.
     *
     * @param node The node to add.
     */
    void add_child(const Node& node);

    /**
     * @brief Inserts the Node `node` before the node.
     *
     * @param node The node to insert.
     */
    void insert_before(const Node& node);

    /**
     * @brief Inserts the Node `node` after the node.
     *
     * @param node The node to insert.
     */
    void insert_after(const Node& node);

    /**
     * @brief Remove the node from the tree.
     */
    void remove();

    /**
     * Returns an Attribute in the node with the key `key`.
     *
     * @param key the key of the attribute to access.
     * @throw std::out_of_range if node does not have attribute with
     *        key `key`.
     * @return Attribute with the key `key` if it exists,
     *         Attribute that gets initialised with nullptr otherwhise.
     */
    [[nodiscard]] Attribute at(const std::string& key) const;

    /**
     * @brief Returns the first attribute in the node.
     *
     * @return An optional with the first attribute in the node if it exists,
     *         std::nullopt otherwhise.
     */
    [[nodiscard]] std::optional<Attribute> first_attribute() const;

    /**
     * @brief Returns the last attribute in the node.
     *
     * @return An optional with the last attribute in the node if it exists,
     *         std::nullopt otherwhise.
     */
    [[nodiscard]] std::optional<Attribute> last_attribute() const;

    /**
     * @brief Returns a vector of all attributes of the node.
     *
     * @return A vector of all attributes of the node.
     */
    [[nodiscard]] std::vector<Attribute> attributes() const;

    /**
     * @brief Adds an attribute to the node with key `key`
     *        and value `value`.
     *
     * @param key The key of the added attribute.
     * @param value the value of the added attribute.
     *
     * @return The added attribute.
     */
    Attribute add_attribute(const std::string& key, const std::string& value);

    // void remove_attribute(const Attribute& attribute);

    /**
     * @brief Removes the attribute with key `key` from the node, if it exists.
     *
     * @param key The key of the removed attribute.
     * @return true if an attribute was removed, false otherwhise.
     */
    bool remove_attribute_by_key(const std::string& key);

    /// A Node Iterator class
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Attribute;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        explicit Iterator(const Attribute& attr);

        reference operator*();

        Iterator& operator++();

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        Attribute m_attr;
    };

    /// A Node ConstIterator class
    class ConstIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Attribute;
        using difference_type = std::ptrdiff_t;
        using pointer = const value_type*;
        using reference = const value_type&;

        explicit ConstIterator(const Attribute& attr);

        reference operator*();

        ConstIterator& operator++();

        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;

    private:
        Attribute m_attr;
    };

    /**
     * @brief Returns an iterator to the first attribute.
     *
     * @return Iterator to first attribute if it exists,
     *         Iterator to `Attribute(nullptr)` otherwhise.
     */
    Iterator begin() noexcept;

    /**
     * @brief Returns an iterator to after the last attribute.
     *
     * @return Iterator to `Attribute(nullptr)`.
     */
    Iterator end() noexcept;

    /**
     * @brief Returns a const iterator to the first attribute.
     *
     * @return ConstIterator to first attribute if it exists,
     *         ConstIterator to `Attribute(nullptr)` otherwhise.
     */
    [[nodiscard]] ConstIterator begin() const noexcept;

    /**
     * @brief Returns an const iterator to after the last attribute.
     *
     * @return ConstIterator to `Attribute(nullptr)`.
     */
    [[nodiscard]] ConstIterator end() const noexcept;

    /**
     * @brief Returns a const iterator to the first attribute.
     *
     * @return ConstIterator to first attribute if it exists,
     *         ConstIterator to `Attribute(nullptr)` otherwhise.
     */
    [[nodiscard]] ConstIterator cbegin() const noexcept;

    /**
     * @brief Returns an const iterator to after the last attribute.
     *
     * @return ConstIterator to `Attribute(nullptr)`.
     */
    [[nodiscard]] ConstIterator cend() const noexcept;

private:
    /// Pointer to the underlying myhtml node struct.
    myhtml_tree_node_t* m_raw_node;
};

/**
 * @brief Print the node.
 */
std::ostream& operator<<(std::ostream& os, const Node& n);

}  // namespace myhtmlpp

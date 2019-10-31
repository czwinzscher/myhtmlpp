#pragma once

#include "myhtmlpp/attribute.hpp"

#include <myhtml/api.h>
#include <optional>
#include <string>
#include <vector>

namespace myhtmlpp {

class Node {
public:
    explicit Node(myhtml_tree_node_t* raw_node);
    ~Node();

    bool operator==(const Node& other) const;
    bool operator!=(const Node& other) const;

    [[nodiscard]] bool good() const;

    [[nodiscard]] std::string text() const;
    [[nodiscard]] myhtml_tag_id_t tag_id() const;
    [[nodiscard]] myhtml_namespace_t ns() const;

    void set_ns(myhtml_namespace_t new_ns);

    [[nodiscard]] std::optional<Node> first_child() const;
    [[nodiscard]] std::optional<Node> last_child() const;
    [[nodiscard]] std::optional<Node> previous() const;
    [[nodiscard]] std::optional<Node> next() const;
    [[nodiscard]] std::optional<Node> parent() const;
    [[nodiscard]] std::vector<Node> children() const;

    void add_child(const Node& node);
    void insert_before(const Node& node);
    void insert_after(const Node& node);

    void remove();

    [[nodiscard]] std::optional<Attribute> first_attribute() const;
    [[nodiscard]] std::optional<Attribute> last_attribute() const;
    [[nodiscard]] std::vector<Attribute> attributes() const;
    Attribute add_attribute(const std::string& key, const std::string& value);
    void remove_attribute(const Attribute& attribute);
    void remove_attribute_by_key(const std::string& key);

private:
    myhtml_tree_node_t* m_raw_node;

    template <typename Func>
    std::optional<Node> optional_node_helper(Func f) const {
        myhtml_tree_node_t* raw_node = f(m_raw_node);

        return raw_node != nullptr ? std::make_optional(Node(raw_node))
                                   : std::nullopt;
    }

    template <typename Func>
    std::optional<Attribute> optional_attribute_helper(Func f) const {
        myhtml_tree_attr_t* raw_attr = f(m_raw_node);

        return raw_attr != nullptr
                   ? std::make_optional(Attribute(raw_attr))
                   : std::nullopt;
    }
};

}  // namespace myhtmlpp

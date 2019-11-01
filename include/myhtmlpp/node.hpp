#pragma once

#include "myhtmlpp/attribute.hpp"

#include <myhtml/api.h>
#include <optional>
#include <ostream>
#include <string>
#include <vector>

namespace myhtmlpp {

class Node {
public:
    explicit Node(myhtml_tree_node_t* raw_node);

    [[nodiscard]] bool operator==(const Node& other) const;
    [[nodiscard]] bool operator!=(const Node& other) const;

    [[nodiscard]] Attribute operator[](const std::string& key) const noexcept;

    [[nodiscard]] bool good() const;

    [[nodiscard]] std::string html_string() const;

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

    [[nodiscard]] Attribute at(const std::string& key) const;
    [[nodiscard]] std::optional<Attribute> first_attribute() const;
    [[nodiscard]] std::optional<Attribute> last_attribute() const;
    [[nodiscard]] std::vector<Attribute> attributes() const;
    Attribute add_attribute(const std::string& key, const std::string& value);
    void remove_attribute(const Attribute& attribute);
    void remove_attribute_by_key(const std::string& key);

private:
    myhtml_tree_node_t* m_raw_node;

    template <typename Ret, typename Func>
    std::optional<Ret> optional_helper(Func f) const {
        auto raw = f(m_raw_node);

        return raw != nullptr ? std::make_optional(Ret(raw)) : std::nullopt;
    }
};

std::ostream& operator<<(std::ostream& os, const Node& n);

}  // namespace myhtmlpp

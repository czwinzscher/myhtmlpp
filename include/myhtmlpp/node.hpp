#pragma once

#include <myhtml/api.h>
#include <optional>
#include <string>
#include <vector>

namespace myhtmlpp {

class Tree;

class Node {
public:
    explicit Node(myhtml_tree_node_t* raw_node);
    ~Node();

    bool operator==(const Node& other) const;
    bool operator!=(const Node& other) const;

    [[nodiscard]] bool good() const;

    [[nodiscard]] myhtmlpp::Tree tree() const;
    [[nodiscard]] std::string text() const;
    [[nodiscard]] myhtml_tag_id_t tag_id() const;

    [[nodiscard]] std::optional<Node> first_child() const;
    [[nodiscard]] std::optional<Node> last_child() const;
    [[nodiscard]] std::optional<Node> next() const;
    [[nodiscard]] std::optional<Node> previous() const;
    [[nodiscard]] std::optional<Node> parent() const;
    [[nodiscard]] std::vector<Node> children() const;

    void add_child(const Node& node);
    void insert_before(const Node& node);
    void insert_after(const Node& node);

private:
    myhtml_tree_node_t* m_raw_node;
};

}  // namespace myhtmlpp

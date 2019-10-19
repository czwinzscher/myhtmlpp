#pragma once

#include <myhtml/api.h>
#include <optional>
#include <vector>

namespace myhtmlpp {

class Node {
public:
    explicit Node(myhtml_tree_node_t* raw_node);
    ~Node();

    [[nodiscard]] bool good() const;

    [[nodiscard]] std::optional<std::string> text() const;

    [[nodiscard]] std::vector<Node> children() const;
    [[nodiscard]] std::optional<Node> next() const;
    [[nodiscard]] std::optional<Node> previous() const;
    [[nodiscard]] std::optional<Node> parent() const;
    [[nodiscard]] myhtml_tag_id_t tag_id() const;

private:
    myhtml_tree_node_t* m_raw_node;
};

}  // namespace myhtmlpp

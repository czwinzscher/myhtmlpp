#pragma once

#include <myhtml/api.h>
#include <optional>
#include <vector>

namespace myhtmlpp {

class Node {
public:
    explicit Node(myhtml_tree_node_t* raw_node);
    ~Node();

    bool good() const;

    std::optional<std::string> text() const;

    std::vector<Node> children() const;
    std::optional<Node> next() const;
    std::optional<Node> previous() const;
    std::optional<Node> parent() const;
    myhtml_tag_id_t tag_id() const;

private:
    myhtml_tree_node_t* m_raw_node;
};

}  // namespace myhtmlpp

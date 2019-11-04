# myhtmlpp

myhtmlpp is a modern C++17 wrapper around the [MyHTML C library](https://github.com/lexborisov/myhtml), a fast HTML Parser. (**WIP**)

## Usage examples
```cpp
#include <algorithm>
#include <cassert>
#include <iostream>

#include <myhtmlpp/parser.hpp>

int main() {
    std::string html(R"(<div class="test" id="bla">hello world</div>)");

    auto tree = myhtmlpp::parse(html);

    // print the tree
    std::cout << tree << "\n";

    // iterate over all nodes in the tree
    for (const auto& node : tree) {
        if (node.tag_id() == MyHTML_TAG__TEXT) {
            std::cout << node.text() << "\n";
        }
    }

    // get special nodes from the tree
    auto doc = tree.document_node();
    auto root = tree.html_node();
    auto head = tree.head_node();
    auto body = tree.body_node();

    // tree traversal with previous(), next(), parent(), first_child()
    // all these methods return std::optional<Node>
    assert(root.parent().value() == doc);
    assert(root.first_child().value() == head);
    assert(head.next().value() == body);
    assert(!head.previous().has_value());
    assert(root.children().size() == 2);

    // use stl algorithms on the tree
    auto div_node_it =
        std::find_if(tree.begin(), tree.end(), [](const auto& node) {
            return node.tag_id() == MyHTML_TAG_DIV;
        });

    assert(div_node_it != tree.end());
    auto div_node = *div_node_it;

    // add attributes to nodes
    auto style_attr = div_node.add_attribute("style", "color:green");
    assert(div_node.attributes().size() == 3);

    // access attributes with operator[]
    auto also_style_attr = div_node["style"];
    assert(style_attr == also_style_attr);

    // iterate over all attributes of a node
    // attributes support structured bindings
    for (const auto& [key, value] : div_node) {
        std::cout << key << "=\"" << value << "\"\n";
    }

    // create new nodes
    auto p_node = tree.create_node(MyHTML_TAG_P, MyHTML_NAMESPACE_HTML);

    // ... and insert them into the tree
    div_node.insert_after(p_node); // or insert_before or add_child
    assert(div_node.next().value() == p_node);
}
```

## Installation
Obviously you also need to have the [MyHTML library](https://github.com/lexborisov/myhtml) installed.

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
make test
sudo make install
```

link with `-lmyhtml` and `-lmyhtmlpp` when using the library.

## CMake options
- use `-DMYHTMLPP_BUILD_TESTS=OFF` to disable tests
- use `-DMYHTMLPP_BUILD_DOC=OFF` to disable doxygen documentation

## Documentation
You can build docs with `make doc`.

## License
- myhtmlpp - [MIT](https://github.com/czwinzscher/myhtmlpp/blob/master/LICENSE)
- MyHTML - [LGPL 2.1](https://github.com/lexborisov/myhtml/blob/master/LICENSE)

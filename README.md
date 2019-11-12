# myhtmlpp

myhtmlpp is a modern C++17 HTML parser with CSS selectors based on [MyHTML/Modest](https://github.com/lexborisov/Modest). (**WIP**)

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
        if (node.is_text_node()) {
            std::cout << node.text() << "\n";
        }
    }

    // filter out nodes
    // theses methods return a vector of nodes
    auto by_tag = tree.find_by_tag("div");
    auto by_class = tree.find_by_class("test");
    auto by_id = tree.find_by_id("bla");

    // get special nodes from the tree
    auto doc = tree.document_node();
    auto root = tree.html_node();
    auto head = tree.head_node();
    auto body = tree.body_node();

    // tree traversal with previous(), next(), parent(), first_child(), last_child()
    // all these methods return std::optional<Node>
    assert(root.parent().value() == doc);
    assert(root.first_child().value() == head);
    assert(head.next().value() == body);
    assert(!head.previous().has_value());
    assert(root.children().size() == 2);

    // use stl algorithms on the tree
    auto div_node_it =
        std::find_if(tree.begin(), tree.end(), [](const auto& node) {
            return node.tag_id() == myhtmlpp::TAG::DIV &&
                   node.has_attribute("class");
        });

    assert(div_node_it != tree.end());
    auto div_node = *div_node_it;

    // access attribute values with operator[]
    auto class_attr = div_node["class"];
    assert(class_attr == "test");

    // iterate over all attributes of a node
    // attributes support structured bindings
    for (const auto& [key, value] : div_node) {
        std::cout << key << "=\"" << value << "\"\n";
    }
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

link with `-lmyhtmlpp` and `-lmodest` when using the library.

### CMake options
- use `-DMYHTMLPP_BUILD_TESTS=OFF` to disable tests
- use `-DMYHTMLPP_BUILD_DOC=OFF` to disable doxygen documentation

## Embed into existing CMake project
Instead of installing the library systemwide you can also copy the entire project into your project (or use it as a submodule) and call `add_subdirectory()` from CMake.

```cmake
# you probably want to disable tests and docs
set(MYHTMLPP_BUILD_TESTS OFF)
set(MYHTMLPP_BUILD_DOC OFF)

add_subdirectory(path/to/myhtmlpp)
...
add_library(your_project ...)
...
target_include_directories(your_project PRIVATE ${MYHTMLPP_INCLUDE_DIR})
target_link_libraries(your_project PRIVATE ${MYHTMLPP_LIBRARIES})
```

## Documentation
You can build docs with `make doc`.

## Notes
This library was tested with MyHTML version 0.0.6.

## License
- myhtmlpp - [MIT](https://github.com/czwinzscher/myhtmlpp/blob/master/LICENSE)
- Modest - [LGPL 2.1](https://github.com/lexborisov/Modest/blob/master/LICENSE)

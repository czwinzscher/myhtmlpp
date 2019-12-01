# myhtmlpp
[![Actions Status](https://github.com/czwinzscher/myhtmlpp/workflows/build/badge.svg)](https://github.com/czwinzscher/myhtmlpp/actions)

myhtmlpp is a modern C++17 HTML parser with CSS selectors based on [MyHTML/Modest](https://github.com/lexborisov/modest). (**WIP**)

## Usage examples
```cpp
#include <algorithm>
#include <cassert>
#include <iostream>

#include <myhtmlpp/parser.hpp>

int main() {
    std::string html(
        R"(<!DOCTYPE html>
<html>
<head>
    <title>Foo</title>
</head>
<body>
    <p class="hello">Hello World</p>
    <div id="bla" class="test"><b>bold</b> div</div>
    <div>normal div</div>
    <p class="hello"></p>
    <img src="image.jpg" hidden>
</body>
</html>)");

    auto tree = myhtmlpp::parse(html);

    // print the serialized tree
    std::cout << tree << "\n";

    // iterate over all nodes in the tree
    for (const auto& node : tree) {
        // ...
    }

    // filter out nodes
    // theses methods return a std::vector<myhtmlpp::Node>
    auto by_css = tree.select("p.hello");
    auto by_tag = tree.find_by_tag("div");  // same as find_by_tag(myhtmlpp::TAG::DIV)
    auto by_class = tree.find_by_class("test");
    auto by_id = tree.find_by_id("bla");
    auto by_attr = tree.find_by_attr("src", "image.jpg");

    // get the inner text of a node
    for (const auto& node : by_tag) {
        std::cout << node.inner_text() << "\n";
    }

    // get special nodes from the tree
    auto doc = tree.document_node();
    auto root = tree.html_node();
    auto head = tree.head_node();
    auto body = tree.body_node();

    // tree traversal with previous(), next(), parent(), first_child(), last_child()
    // all these methods return std::optional<Node>
    assert(root.parent().value() == doc);
    assert(root.first_child().value() == head);
    assert(root.last_child().value() == body);
    assert(!head.previous().has_value());
    assert(root.children().size() == 3);

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

    // a safer alternative is at(), which checks if the attribute exists
    // and returns an std::optional<std::string>
    auto class_attr_opt = div_node.at("class");
    assert(class_attr_opt.has_value());

    // iterate over all attributes of a node
    // attributes support structured bindings
    for (const auto& [key, value] : div_node) {
        std::cout << key << "=\"" << value << "\"\n";
    }
}
```

## Installation
The [Modest library](https://github.com/lexborisov/modest) is included as a submodule.

```bash
git clone --recurse-submodules https://github.com/czwinzscher/myhtmlpp.git
cd myhtmlpp
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
make test
sudo make install
```

### CMake options
- use `-DMYHTMLPP_USE_SYSTEM_MODEST=ON` to use the system installation of modest
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
The build of modest might fail with gcc, you can use `export CC=clang` to fix this.

## License
- myhtmlpp - [MIT](https://github.com/czwinzscher/myhtmlpp/blob/master/LICENSE)
- Modest - [LGPL 2.1](https://github.com/lexborisov/Modest/blob/master/LICENSE)

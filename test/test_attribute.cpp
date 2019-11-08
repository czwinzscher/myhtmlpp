#include "doctest/doctest.h"
#include "myhtmlpp/attribute.hpp"
#include "myhtmlpp/constants.hpp"
#include "myhtmlpp/node.hpp"
#include "myhtmlpp/parser.hpp"
#include "myhtmlpp/tree.hpp"

#include <algorithm>
#include <optional>
#include <string>
#include <utility>

TEST_CASE("attribute") {
    std::string html(
        R"(<!DOCTYPE html>
<html>
<head>
    <title>Foo</title>
</head>
<body>
    <p class="hello">Hello World</p>
    <img src="image.jpg" hidden>
</body>
</html>)");

    auto tree = myhtmlpp::parse(html);

    auto p_node_it =
        std::find_if(tree.begin(), tree.end(), [](const auto& node) {
            return node.tag_id() == myhtmlpp::TAG::P;
        });
    REQUIRE(p_node_it != tree.end());

    auto p_node = *p_node_it;
    auto class_attr = p_node["class"];
    CHECK(class_attr.key() == "class");
    CHECK(class_attr.value() == "hello");
    CHECK(!class_attr.previous().has_value());
    CHECK(!class_attr.next().has_value());

    auto img_node_it =
        std::find_if(tree.begin(), tree.end(), [](const auto& node) {
            return node.tag_id() == myhtmlpp::TAG::IMG;
        });
    REQUIRE(img_node_it != tree.end());

    auto img_node = *img_node_it;
    auto src_attr = img_node.at("src");
    CHECK(src_attr.key() == "src");
    CHECK(src_attr.value() == "image.jpg");
    CHECK(!src_attr.previous().has_value());
    CHECK(src_attr.next().has_value());

    auto hidden_attr = src_attr.next().value();
    CHECK(hidden_attr.value().empty());
    CHECK(hidden_attr.previous().value() == src_attr);

    CHECK(class_attr != src_attr);

    SUBCASE("good") {
        CHECK(class_attr.good());
        CHECK(src_attr.good());
        CHECK(!(*p_node.end()).good());
    }

    SUBCASE("move semantics") {
        CHECK(class_attr.good());
        auto class_attr2 = std::move(class_attr);
        CHECK(class_attr2.good());
        CHECK(!class_attr.good());  // NOLINT

        CHECK(src_attr.good());
        hidden_attr = std::move(src_attr);
        CHECK(hidden_attr.good());
        CHECK(!src_attr.good());  // NOLINT
    }

    SUBCASE("structured bindings") {
        auto [key, value] = src_attr;
        CHECK(key == "src");
        CHECK(value == "image.jpg");
    }
}

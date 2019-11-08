#include "doctest/doctest.h"
#include "myhtmlpp/node.hpp"
#include "myhtmlpp/parser.hpp"
#include "myhtmlpp/tree.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <myhtml/api.h>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

TEST_CASE("tree") {
    std::string html(
        R"(<!DOCTYPE html>
<html>
<head>
    <title>Foo</title>
    <meta charset="utf-8">
</head>
<body>
    <p class="hello">Hello World</p>
    <p>boom</p>
    <p></p>
    <ul>
        <li>one</li>
        <li>two</li>
        <li>three</li>
    </ul>
    <div id="bla" class="class"></div>
    <img src="image.jpg" hidden>
</body>
</html>)");

    auto tree = myhtmlpp::parse(html);

    SUBCASE("good") {
        CHECK(tree.good());

        tree.html_node().remove();
        CHECK(tree.good());
    }

    SUBCASE("move semantics") {
        auto tree2 = std::move(tree);
        CHECK(tree2.good());
        CHECK(!tree.good());  // NOLINT

        auto tree3 = myhtmlpp::parse("");
        tree3 = std::move(tree2);
        CHECK(tree3.good());
        CHECK(!tree2.good());  // NOLINT
    }

    SUBCASE("serialization") {
        std::string html_str(
            R"(<!DOCTYPE html><html><head>
    <title>Foo</title>
    <meta charset="utf-8">
</head>
<body>
    <p class="hello">Hello World</p>
    <p>boom</p>
    <p></p>
    <ul>
        <li>one</li>
        <li>two</li>
        <li>three</li>
    </ul>
    <div id="bla" class="class"></div>
    <img src="image.jpg" hidden="">

</body></html>)");

        std::stringstream html_sstream;
        html_sstream << tree;
        CHECK(html_sstream.str() == html_str);
        CHECK(tree.html() == html_str);
    }

    SUBCASE("iterator") {
        CHECK(*tree.begin() == tree.document_node());
        CHECK(!(*tree.end()).good());

        CHECK(*tree.cbegin() == tree.document_node());
        CHECK(!(*tree.cend()).good());

        CHECK(std::distance(tree.begin(), tree.end()) == 37);

        std::vector<myhtmlpp::Node> text_nodes;
        std::copy_if(
            tree.begin(), tree.end(), std::back_inserter(text_nodes),
            [](const auto& node) { return node.tag_id() == MyHTML_TAG__TEXT; });
        CHECK(text_nodes.size() == 21);

        auto a_it =
            std::find_if(tree.begin(), tree.end(), [](const auto& node) {
                return node.tag_id() == MyHTML_TAG_A;
            });
        CHECK(a_it == tree.end());
    }

    SUBCASE("nodes") {
        CHECK(tree.document_node().good());
        CHECK(tree.html_node().good());
        CHECK(tree.head_node().good());
        CHECK(tree.body_node().good());
    }

    SUBCASE("create nodes") {
        auto node = tree.create_node(MyHTML_TAG_DIV, MyHTML_NAMESPACE_XML);

        CHECK(node.good());
        CHECK(node.tag_id() == MyHTML_TAG_DIV);
        CHECK(node.get_namespace() == MyHTML_NAMESPACE_XML);

        auto node_default_namespace = tree.create_node(MyHTML_TAG_IMG);

        CHECK(node_default_namespace.good());
        CHECK(node_default_namespace.tag_id() == MyHTML_TAG_IMG);
        CHECK(node_default_namespace.get_namespace() == MyHTML_NAMESPACE_HTML);
    }
}

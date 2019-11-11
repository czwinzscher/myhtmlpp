#include "doctest/doctest.h"
#include "myhtmlpp/constants.hpp"
#include "myhtmlpp/filter.hpp"
#include "myhtmlpp/node.hpp"
#include "myhtmlpp/parser.hpp"
#include "myhtmlpp/tree.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
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

    SUBCASE("good") { CHECK(tree.good()); }

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

    SUBCASE("nodes") {
        CHECK(tree.document_node().good());
        CHECK(tree.html_node().good());
        CHECK(tree.head_node().good());
        CHECK(tree.body_node().good());
    }

    SUBCASE("find") {
        auto p_by_string = tree.find_by_tag("p");
        std::cout << p_by_string.size() << "\n";

        auto p_by_tag = tree.find_by_tag(myhtmlpp::TAG::P);

        CHECK(p_by_string.begin() != p_by_string.end());
        CHECK(p_by_string == p_by_tag);
        CHECK(p_by_string.size() == 3);

        CHECK(tree.find_by_tag("").empty());
        CHECK(tree.find_by_tag("iudwibfoe").empty());

        CHECK(tree.find_by_tag("-text").size() == 21);
        CHECK(tree.find_by_tag(myhtmlpp::TAG::UNDEF_).size() == 1);

        CHECK(tree.find_by_class("hello").size() == 1);
        CHECK(tree.find_by_id("bla").size() == 1);
        CHECK(tree.find_by_attr("src", "image.jpg").size() == 1);
    }

    SUBCASE("iterator") {
        CHECK(*tree.begin() == tree.document_node());
        CHECK(!(*tree.end()).good());

        CHECK(*tree.cbegin() == tree.document_node());
        CHECK(!(*tree.cend()).good());

        CHECK(std::distance(tree.begin(), tree.end()) == 37);

        std::vector<myhtmlpp::Node> text_nodes;
        std::copy_if(tree.begin(), tree.end(), std::back_inserter(text_nodes),
                     [](const auto& node) {
                         return node.tag_id() == myhtmlpp::TAG::TEXT_;
                     });
        CHECK(text_nodes.size() == 21);

        auto a_it =
            std::find_if(tree.begin(), tree.end(), [](const auto& node) {
                return node.tag_id() == myhtmlpp::TAG::A;
            });
        CHECK(a_it == tree.end());
    }

    SUBCASE("filter") {
        auto nodes_with_attrs =
            tree.filter([](const auto& node) { return node.has_attributes(); });

        CHECK(nodes_with_attrs.to_vector().size() == 5);
        for (const auto& node : nodes_with_attrs) {
            CHECK(node.has_attributes());
        }

        CHECK(nodes_with_attrs.begin() != nodes_with_attrs.end());
        CHECK((*nodes_with_attrs.begin()).tag_id() == myhtmlpp::TAG::DOCTYPE_);
    }
}

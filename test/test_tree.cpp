#include "doctest/doctest.h"
#include "myhtmlpp/constants.hpp"
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

    SUBCASE("good") {
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

    SUBCASE("nodes") {
        CHECK(tree.document_node().good());
        CHECK(tree.html_node().good());
        CHECK(tree.head_node().good());
        CHECK(tree.body_node().good());
    }

    SUBCASE("find") {
        auto p_by_string = tree.find_all("p");
        auto p_by_tag = tree.find_all(myhtmlpp::TAG::P);
        CHECK(p_by_string == p_by_tag);
        CHECK(p_by_string.size() == 3);

        CHECK(tree.find_all("").empty());
        CHECK(tree.find_all("iudwibfoe").empty());

        CHECK(tree.find_all("-text").size() == 21);
        CHECK(tree.find_all(myhtmlpp::TAG::UNDEF_).size() == 1);
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
}

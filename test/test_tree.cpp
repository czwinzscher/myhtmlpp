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
    <div id="bla" class="class class2 class3"></div>
    <img src="image.jpg" id="boom" hidden>
</body>
</html>)");

    auto tree = myhtmlpp::parse(html);

    SUBCASE("good") {
        CHECK(tree.good());
        CHECK(tree);
    }

    SUBCASE("move semantics") {
        auto tree2 = std::move(tree);
        CHECK(tree2.good());
        CHECK(tree2);
        CHECK(!tree.good());  // NOLINT
        CHECK(!tree);

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
    <div id="bla" class="class class2 class3"></div>
    <img src="image.jpg" id="boom" hidden="">

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

    SUBCASE("scope") {
        auto full_scope = tree.scope(tree.document_node());
        CHECK(full_scope == std::vector(tree.begin(), tree.end()));
        CHECK(full_scope.size() == 37);

        auto body_scope = tree.scope(tree.body_node());
        CHECK(body_scope.front() == tree.body_node());
        CHECK(body_scope.size() == 26);

        auto ul_it =
            std::find_if(tree.begin(), tree.end(), [](const auto& node) {
                return node.tag_id() == myhtmlpp::TAG::UL;
            });
        REQUIRE(ul_it != tree.end());

        auto ul_scope = tree.scope(*ul_it);
        CHECK(!ul_scope.empty());
        CHECK(ul_scope.front() == *ul_it);
        CHECK(ul_scope.size() == 11);
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

    SUBCASE("select") {
        CHECK(tree.select("*").size() == 14);
        CHECK(tree.select("p.hello").size() == 1);
        CHECK(tree.select("ul > li").size() == 3);
        CHECK(tree.select("[class]").size() == 2);
        CHECK(tree.select("isfb.s oai*/bnd7").empty());
    }

    SUBCASE("find") {
        auto p_by_string = tree.find_by_tag("p");
        auto p_by_tag = tree.find_by_tag(myhtmlpp::TAG::P);

        CHECK(p_by_string.begin() != p_by_string.end());
        CHECK(p_by_string == p_by_tag);
        CHECK(p_by_string.size() == 3);
        CHECK(tree.find_by_tag("p", p_by_tag.front()).size() == 1);
        CHECK(tree.find_by_tag(myhtmlpp::TAG::P, tree.body_node()) == p_by_tag);

        CHECK(tree.find_by_tag("").empty());
        CHECK(tree.find_by_tag("iudwibfoe", tree.head_node()).empty());

        CHECK(tree.find_by_tag("-text").size() == 21);
        CHECK(
            tree.find_by_tag(myhtmlpp::TAG::UNDEF_, tree.html_node()).empty());

        CHECK(tree.find_by_class("hello").size() == 1);
        CHECK(tree.find_by_class("hello", tree.body_node()).size() == 1);
        CHECK(!tree.find_by_class("class2").empty());
        CHECK(!tree.find_by_class("class3").empty());
        CHECK(tree.find_by_class("class3 ").empty());
        CHECK(tree.find_by_class("cla").empty());
        CHECK(tree.find_by_class("class class2 class3").empty());

        CHECK(tree.find_by_id("bla").size() == 1);
        CHECK(tree.find_by_id("bla", p_by_tag.back()).empty());

        CHECK(tree.find_by_attr("src", "image.jpg").size() == 1);
        CHECK(tree.find_by_attr("src", "image.jpg", tree.head_node()).empty());

        auto starts_with = [](const auto& node, const auto& key,
                              const auto& val) -> bool {
            if (auto attr = node.at(key)) {
                return attr.value().compare(0, val.size(), val) == 0;
            }

            return false;
        };

        CHECK(tree.find_by_attr("id", "b", starts_with).size() == 2);

        CHECK(!tree.find_by_attr("id", "b", tree.body_node(), starts_with)
                   .empty());
        CHECK(tree.find_by_attr("id", "a", tree.body_node(), starts_with)
                  .empty());

        CHECK(tree.find_by_attr_key("hidden").size() == 1);
        CHECK(tree.find_by_attr_key("name").empty());
        CHECK(tree.find_by_attr_key("charset").size() == 1);
        CHECK(tree.find_by_attr_key("charset", tree.body_node()).empty());
    }

    SUBCASE("filter") {
        auto nodes_with_attrs =
            tree.filter([](const auto& node) { return node.has_attributes(); });

        CHECK(nodes_with_attrs.to_vector().size() == 5);
        for (const auto& node : nodes_with_attrs) {
            CHECK(node.has_attributes());
        }

        CHECK((*nodes_with_attrs.begin()).tag_id() == myhtmlpp::TAG::DOCTYPE_);
    }
}

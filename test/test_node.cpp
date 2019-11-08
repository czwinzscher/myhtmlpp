#include "doctest/doctest.h"
#include "myhtmlpp/attribute.hpp"
#include "myhtmlpp/node.hpp"
#include "myhtmlpp/parser.hpp"
#include "myhtmlpp/tree.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <myhtml/api.h>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

TEST_CASE("node") {
    std::string html(
        R"(<!DOCTYPE html>
<html>
<head>
    <title>Foo</title>
</head>
<body>
    <p class="hello">Hello World</p>
    <ul>
        <li>one</li>
        <li>two</li>
    </ul>
    <div id="bla" class="class"></div>
    <img src="image.jpg" hidden>
</body>
</html>)");

    auto tree = myhtmlpp::parse(html);

    auto doc = tree.document_node();
    REQUIRE(doc.children().size() == 2);
    REQUIRE(doc.get_namespace() == MyHTML_NAMESPACE_HTML);

    auto doctype_opt = doc.first_child();
    REQUIRE(doctype_opt.has_value());

    auto html_node = doctype_opt.value().next().value();
    REQUIRE(html_node == tree.html_node());
    REQUIRE(html_node != tree.document_node());

    auto html_children = html_node.children();
    REQUIRE(html_children.size() == 3);

    auto head_node = html_children.at(0);
    REQUIRE(head_node == tree.head_node());

    auto body_node = html_children.at(2);
    REQUIRE(body_node == tree.body_node());

    SUBCASE("good") {
        for (const auto& node : tree) {
            CHECK(node.good());
        }

        CHECK(!(*tree.end()).good());

        auto n = std::move(doc);
        CHECK(!doc.good());  // NOLINT
    }

    SUBCASE("move semantics") {
        head_node = std::move(doc);
        CHECK(!doc.good());  // NOLINT
        CHECK(tree.document_node() == head_node);
        CHECK(tree.head_node().good());

        auto body2 = std::move(body_node);
        CHECK(body2.good());
        CHECK(!body_node.good());  // NOLINT
    }

    SUBCASE("node attributes") {
        CHECK(doc.text().empty());
        CHECK(doc.tag_id() == MyHTML_TAG__UNDEF);
        CHECK(doc.tag_string() == "-undef");
        CHECK(doc.get_namespace() == MyHTML_NAMESPACE_HTML);

        CHECK(html_node.text().empty());
        CHECK(html_node.tag_id() == MyHTML_TAG_HTML);

        CHECK(head_node.tag_id() == MyHTML_TAG_HEAD);
        CHECK(body_node.tag_id() == MyHTML_TAG_BODY);

        auto p_node_it =
            std::find_if(tree.begin(), tree.end(), [](const auto& node) {
                return node.tag_id() == MyHTML_TAG_P;
            });
        REQUIRE(p_node_it != tree.end());

        auto p_node = *p_node_it;
        auto p_text_node = p_node.first_child().value();
        CHECK(p_text_node.text() == "Hello World");
        CHECK(p_text_node.tag_string() == "-text");
        CHECK(p_node.tag_string() == "p");
        CHECK(!p_node.is_void_element());
        CHECK(p_node.html() == R"(<p class="hello">)");

        auto img_node_it =
            std::find_if(tree.begin(), tree.end(), [](const auto& node) {
                return node.tag_id() == MyHTML_TAG_IMG;
            });
        REQUIRE(img_node_it != tree.end());

        auto img_node = *img_node_it;
        CHECK(img_node.is_void_element());
    }

    SUBCASE("node manipulation") {
        auto ul_node_it =
            std::find_if(tree.begin(), tree.end(), [](const auto& node) {
                return node.tag_id() == MyHTML_TAG_UL;
            });
        REQUIRE(ul_node_it != tree.end());

        auto ul_node = *ul_node_it;
        auto ul_children = ul_node.children();
        CHECK(std::count_if(ul_children.begin(), ul_children.end(),
                            [](const auto& node) {
                                return node.tag_id() == MyHTML_TAG_LI;
                            }) == 2);

        auto new_node = tree.create_node(MyHTML_TAG_LI, MyHTML_NAMESPACE_HTML);
        ul_node.add_child(new_node);

        ul_children = ul_node.children();
        CHECK(std::count_if(ul_children.begin(), ul_children.end(),
                            [](const auto& node) {
                                return node.tag_id() == MyHTML_TAG_LI;
                            }) == 3);

        new_node = tree.create_node(MyHTML_TAG_A, MyHTML_NAMESPACE_HTML);
        ul_node.insert_before(new_node);
        CHECK(ul_node.previous().value() == new_node);

        new_node = tree.create_node(MyHTML_TAG_CITE, MyHTML_NAMESPACE_HTML);
        ul_node.insert_after(new_node);
        CHECK(ul_node.next().value() == new_node);

        new_node.remove();
        CHECK(ul_node.next().value() != new_node);

        ul_node.set_namespace(MyHTML_NAMESPACE_XML);
        CHECK(ul_node.get_namespace() == MyHTML_NAMESPACE_XML);
    }

    SUBCASE("node traversal") {
        CHECK(doc.previous() == std::nullopt);
        CHECK(doc.next() == std::nullopt);
        CHECK(doc.parent() == std::nullopt);
        CHECK(doc.first_child() != html_node);
        CHECK(doc.children().at(0) == doc.first_child());
        CHECK(doc.siblings().size() == 0);
        CHECK(html_node.parent().value() == doc);
        CHECK(html_node.first_child().value().previous() == std::nullopt);
        CHECK(body_node.siblings().size() == 2);
        CHECK(body_node.siblings().at(0).tag_id() == MyHTML_TAG__TEXT);
        CHECK(body_node.siblings().at(1) == head_node);

        auto ul_node_it =
            std::find_if(tree.begin(), tree.end(), [](const auto& node) {
                return node.tag_id() == MyHTML_TAG_UL;
            });
        REQUIRE(ul_node_it != tree.end());

        auto ul_node = *ul_node_it;
        CHECK(ul_node.siblings().size() == 8);
        CHECK(ul_node.siblings().at(1).tag_string() == "p");
        CHECK(ul_node.siblings().at(6).tag_string() == "img");

        for (const auto& child_node : ul_node.children()) {
            CHECK(child_node.parent().value() == ul_node);
        }
    }

    SUBCASE("html string") {
        CHECK(head_node.html() == "<head>");
        CHECK(head_node.html_deep() == R"(<head>
    <title>Foo</title>
</head>)");

        auto img_node_it =
            std::find_if(tree.begin(), tree.end(), [](const auto& node) {
                return node.tag_id() == MyHTML_TAG_IMG;
            });
        REQUIRE(img_node_it != tree.end());

        auto img_node = *img_node_it;
        CHECK(img_node.html() == R"(<img src="image.jpg" hidden="">)");
    }

    SUBCASE("attributes") {
        CHECK(!doc.has_attributes());
        CHECK(!html_node.has_attributes());
        CHECK(!body_node.has_attributes());

        auto div_node_it =
            std::find_if(tree.begin(), tree.end(), [](const auto& node) {
                return node.tag_id() == MyHTML_TAG_DIV;
            });
        REQUIRE(div_node_it != tree.end());

        auto div_node = *div_node_it;
        CHECK(div_node.has_attributes());
        auto class_attr = div_node["class"];
        auto [k, v] = class_attr;
        CHECK(class_attr.key() == "class");
        CHECK(k == "class");
        CHECK(class_attr.value() == "class");
        CHECK(v == "class");
        CHECK(div_node.last_attribute().value() == class_attr);
        CHECK(class_attr.previous().has_value());
        CHECK(class_attr.previous().value() ==
              div_node.first_attribute().value());
        CHECK(!class_attr.next().has_value());
        CHECK(class_attr.get_namespace() == MyHTML_NAMESPACE_HTML);

        CHECK_NOTHROW(auto c = div_node.at("class"));
        CHECK_THROWS_WITH_AS(auto s = div_node.at("style"),
                             "attribute with key style does not exist.",
                             std::out_of_range);

        auto style_attr = div_node.add_attribute("style", "bold");
        CHECK(style_attr == div_node.at("style"));

        CHECK(!div_node.remove_attribute_by_key("href"));
        CHECK(div_node.remove_attribute_by_key("id"));
        CHECK_THROWS(auto a = div_node.at("id"));
    }

    SUBCASE("iterator") {
        auto div_node_it =
            std::find_if(tree.begin(), tree.end(), [](const auto& node) {
                return node.tag_id() == MyHTML_TAG_DIV;
            });
        REQUIRE(div_node_it != tree.end());

        auto div_node = *div_node_it;

        CHECK(div_node.attributes().size() == 2);
        CHECK(std::distance(div_node.begin(), div_node.end()) == 2);

        for (const auto& [k, v] : div_node) {
            CHECK(!k.empty());
            CHECK(!v.empty());
        }

        auto it_begin = div_node.begin();
        CHECK((*it_begin).key() == "id");
        CHECK((*it_begin).value() == "bla");
        CHECK(++it_begin != div_node.end());
        CHECK(++it_begin == div_node.end());

        auto it_cbegin = div_node.cbegin();
        CHECK((*it_cbegin).key() == "id");
        CHECK((*it_cbegin).value() == "bla");
        CHECK(++it_cbegin != div_node.cend());
        CHECK(++it_cbegin == div_node.cend());
    }
}

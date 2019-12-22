#include "doctest/doctest.h"
#include "myhtmlpp/matchers.hpp"
#include "myhtmlpp/parser.hpp"

#include <algorithm>

namespace matchers = myhtmlpp::matchers;

TEST_CASE("matchers") {
    std::string html(
        R"(<div id="bla" class="class  class2 third-class "></div>
<img src="image.jpg" hidden>)");

    auto tree = myhtmlpp::parse(html);

    auto div_node =
        *(std::find_if(tree.begin(), tree.end(), [](const auto& node) {
            return node.tag_name() == "div";
        }));

    auto img_node =
        *(std::find_if(tree.begin(), tree.end(), [](const auto& node) {
            return node.tag_name() == "img";
        }));

    SUBCASE("exact match") {
        CHECK(matchers::exact_match(div_node, "class",
                                    "class  class2 third-class "));
        CHECK(!matchers::exact_match(div_node, "class", "class"));

        CHECK(matchers::exact_match(img_node, "src", "image.jpg"));
        CHECK(!matchers::exact_match(img_node, "src", "image"));
        CHECK(!matchers::exact_match(img_node, "hidden", ""));
    }

    SUBCASE("whitespace seperated") {
        CHECK(matchers::whitespace_seperated(div_node, "class", "class"));
        CHECK(matchers::whitespace_seperated(div_node, "class", "class2"));
        CHECK(matchers::whitespace_seperated(div_node, "class", "third-class"));
        CHECK(!matchers::whitespace_seperated(div_node, "class", ""));
        CHECK(!matchers::whitespace_seperated(div_node, "class",
                                              "class  class2 third-class "));
        CHECK(matchers::whitespace_seperated(div_node, "id", "bla"));

        CHECK(matchers::whitespace_seperated(img_node, "src", "image.jpg"));
    }
}

#include "doctest/doctest.h"
#include "myhtmlpp/constants.hpp"
#include "myhtmlpp/parser.hpp"

#include <myhtml/api.h>
#include <string>

TEST_CASE("parser") {
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
        <li>three</li>
    </ul>
    <div id="bla" class="class"></div>
    <img src="image.jpg" hidden/>
</body>
</html>)");

    REQUIRE_NOTHROW(myhtmlpp::parse(html));
    REQUIRE_NOTHROW(
        myhtmlpp::parse(html, myhtmlpp::OPTION::PARSE_MODE_SEPARATELY));
    REQUIRE_NOTHROW(myhtmlpp::parse(html, myhtmlpp::OPTION::DEFAULT, 3));
    REQUIRE_NOTHROW(
        myhtmlpp::parse(html, myhtmlpp::OPTION::PARSE_MODE_SINGLE, 2, 4096));
    REQUIRE_NOTHROW(myhtmlpp::parse_fragment(html));
    REQUIRE_NOTHROW(myhtmlpp::parse_fragment(html, myhtmlpp::TAG::UL));
    REQUIRE_NOTHROW(myhtmlpp::parse_fragment(html, myhtmlpp::TAG::A,
                                             myhtmlpp::NAMESPACE::XML));
    REQUIRE_NOTHROW(myhtmlpp::parse_fragment(
        html, myhtmlpp::TAG::DIV, myhtmlpp::NAMESPACE::HTML,
        myhtmlpp::OPTION::PARSE_MODE_SEPARATELY));
    REQUIRE_NOTHROW(myhtmlpp::parse_fragment(html, myhtmlpp::TAG::DIV,
                                             myhtmlpp::NAMESPACE::HTML,
                                             myhtmlpp::OPTION::DEFAULT, 4));
    REQUIRE_NOTHROW(myhtmlpp::parse_fragment(
        html, myhtmlpp::TAG::A, myhtmlpp::NAMESPACE::HTML,
        myhtmlpp::OPTION::PARSE_MODE_SEPARATELY, 2, 0));
}

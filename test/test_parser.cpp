#include "doctest/doctest.h"
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
        myhtmlpp::parse(html, MyHTML_OPTIONS_PARSE_MODE_SEPARATELY));
    REQUIRE_NOTHROW(myhtmlpp::parse(html, MyHTML_OPTIONS_DEFAULT, 3));
    REQUIRE_NOTHROW(
        myhtmlpp::parse(html, MyHTML_OPTIONS_PARSE_MODE_SINGLE, 2, 4096));
    REQUIRE_NOTHROW(myhtmlpp::parse_fragment(html));
    REQUIRE_NOTHROW(myhtmlpp::parse_fragment(html, MyHTML_TAG_UL));
    REQUIRE_NOTHROW(
        myhtmlpp::parse_fragment(html, MyHTML_TAG_A, MyHTML_NAMESPACE_XML));
    REQUIRE_NOTHROW(
        myhtmlpp::parse_fragment(html, MyHTML_TAG_DIV, MyHTML_NAMESPACE_HTML,
                                 MyHTML_OPTIONS_PARSE_MODE_SEPARATELY));
    REQUIRE_NOTHROW(myhtmlpp::parse_fragment(html, MyHTML_TAG_DIV,
                                             MyHTML_NAMESPACE_HTML,
                                             MyHTML_OPTIONS_DEFAULT, 4));
    REQUIRE_NOTHROW(
        myhtmlpp::parse_fragment(html, MyHTML_TAG_A, MyHTML_NAMESPACE_HTML,
                                 MyHTML_OPTIONS_PARSE_MODE_SEPARATELY, 2, 0));
}

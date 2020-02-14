#include "doctest/doctest.h"
#include "myhtmlpp/constants.hpp"
#include "myhtmlpp/parser.hpp"

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

    REQUIRE_NOTHROW(myhtmlpp::parse(
        html, {
                  .opt = myhtmlpp::OPTION::PARSE_MODE_SEPARATELY,
              }));

    REQUIRE_NOTHROW(
        myhtmlpp::parse(html, {
                                  .opt = myhtmlpp::OPTION::PARSE_MODE_SINGLE,
                                  .thread_count = 3,
                              }));

    REQUIRE_NOTHROW(myhtmlpp::parse_fragment(html));

    myhtmlpp::ParseFragmentOptions opts{
        .opt = myhtmlpp::OPTION::DEFAULT,
        .thread_count = 2,
        .queue_size = 0,
        .tag_id = myhtmlpp::TAG::A,
        .ns = myhtmlpp::NAMESPACE::XML,
    };
    REQUIRE_NOTHROW(myhtmlpp::parse_fragment(html, opts));
}

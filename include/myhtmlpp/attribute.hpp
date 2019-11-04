#pragma once

#include <myhtml/api.h>
#include <optional>
#include <string>

namespace myhtmlpp {

class Attribute {
public:
    explicit Attribute(myhtml_tree_attr_t* raw_attribute);

    [[nodiscard]] bool operator==(const Attribute& other) const;
    [[nodiscard]] bool operator!=(const Attribute& other) const;

    [[nodiscard]] std::string key() const;
    [[nodiscard]] std::string value() const;
    [[nodiscard]] myhtml_namespace_t ns() const;

    void set_ns(myhtml_namespace_t new_ns);

    [[nodiscard]] std::optional<Attribute> previous() const;
    [[nodiscard]] std::optional<Attribute> next() const;

    // structured bindings
    // auto [key, value] = attr;
    template <std::size_t N>
    decltype(auto) get() const {
        if constexpr (N == 0) {
            return key();
        } else if constexpr (N == 1) {
            return value();
        }
    }

private:
    myhtml_tree_attr_t* m_raw_attribute;
};

}  // namespace myhtmlpp

namespace std {
template <>
struct tuple_size<myhtmlpp::Attribute>
    : std::integral_constant<std::size_t, 2> {};

template <std::size_t N>
struct tuple_element<N, myhtmlpp::Attribute> {
    using type = decltype(std::declval<myhtmlpp::Attribute>().get<N>());
};

}  // namespace std

#pragma once

#include <optional>

template <typename Ret, typename Func, typename Arg>
std::optional<Ret> optional_helper(Func f, Arg a) {
    if (a == nullptr) {
        return std::nullopt;
    }

    auto raw = f(a);

    return raw != nullptr ? std::make_optional(Ret(raw)) : std::nullopt;
}

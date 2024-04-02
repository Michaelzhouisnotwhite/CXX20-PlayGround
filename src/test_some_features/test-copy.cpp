#include <fmt/core.h>
#include <toy/type.h>
#include <backward.hpp>
#include <coroutine>
#include <functional>
#include <iostream>
#include <string>
#define BACKWARD_HAS_DW 1
#include <nlohmann/json.hpp>
#include <ranges>
#include "backward.hpp"
#include "boost/range.hpp"
#include "boost/range/any_range.hpp"
template <typename T>
concept Hashable = requires(T t) {
    { std::hash<T>{}(t) } -> std::convertible_to<std::size_t>;
};
template <typename T>
concept Integer = std::is_integral_v<T>;
template <Hashable T>
void foo(T t) {
    // ...
}

template <Integer T>
void bar(T t) {
    // ...
}

void enumerate_sth(std::ranges::range auto& any_range) {
    for (const auto& val : any_range) {
        (void)val;
    }
}
template <typename T>
void boost_enumerate_sth(const boost::any_range<T(), boost::incrementable_traversal_tag>& ar) {
    for (const auto& val : ar) {
        (void)ar;
    }
}
struct SomeType {};
int main(int args, char* argv[]) {
    foo(10);
    SomeType st;
    if (not false) {
    }
    std::set<int> some_set{1, 2, 3};
    enumerate_sth(some_set);
    // boost_enumerate_sth(some_set);
    return 0;
}
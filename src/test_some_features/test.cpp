#include <fmt/core.h>
#include <toy/type.h>
#include <backward.hpp>
#include <coroutine>
#include <functional>
#include <iostream>
#include <string>
#ifndef WIN32
#define BACKWARD_HAS_DW 1
#include "backward.hpp"
#endif
#include <nlohmann/json.hpp>
#include <ranges>
#include <iterator>
#include <coroutine>
int main(int args, char* argv[]) {
    std::vector<int> v(100);
    for (int i : std::views::iota(1, 10) | std::views::filter([](int i) {
                     return i % 2 == 0;
                 }) | std::views::transform([](int i) {
                     return i + 1;
                 }) ) {
        fmt::println("{}", i);
    }
    
    return 0;
}
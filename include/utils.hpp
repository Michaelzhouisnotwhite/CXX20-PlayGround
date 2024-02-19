#ifndef UTILS_HPP
#define UTILS_HPP
#include <fmt/core.h>
#if _WIN32
#include <windows.h>
#endif
#include <iostream>
#include <type_traits>
#include <utility>
#include <chrono>
namespace ch = std::chrono;
using namespace std::literals;

#ifndef FUNC_NAME
#define FUNC_NAME(...) function_name(__PRETTY_FUNCTION__, ("", ##__VA_ARGS__))
inline void function_name(const char* name, const char* comments) {
    printf("%s %s\n", name, comments);
}
#endif

class Timer{
    public:
    using hr_clock = ch::high_resolution_clock ;
    ch::time_point<hr_clock> start_;
    ch::time_point<hr_clock> end_;
    Timer() {
        start_ = ch::high_resolution_clock::now();
    }
    ~Timer() {
        end_ = hr_clock::now();
        fmt::print("The function takes {}ns\n", (end_ - start_) / 1ns);
    }
};

template <typename FunctionTemplate, typename... Args>
auto timeit(FunctionTemplate&& test_func, Args&&... args) {
#ifdef _WIN32
    LARGE_INTEGER t1, t2, tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);

#else
    clock_t start = clock();
#endif
    using return_type =
        typename std::result_of<FunctionTemplate(Args...)>::type;
    if constexpr (std::is_same<void, return_type>::value) {
        test_func(std::forward<Args>(args)...);
#ifdef _WIN32
        QueryPerformanceCounter(&t2);
        auto time = (long double)(t2.QuadPart - t1.QuadPart) / tc.QuadPart;
#else
        auto time = (double)(clock() - start);
#endif
        fmt::print("The function takes {:.3f}ms\n", time * 1000);
    } else {
        auto res = test_func(std::forward<Args>(args)...);

#ifdef _WIN32
        QueryPerformanceCounter(&t2);
        auto time = (long double)(t2.QuadPart - t1.QuadPart) / tc.QuadPart;
#else
        auto time = (double)(clock() - start);
#endif
        fmt::print("The function takes {:.3f}ms\n", time * 1000);
        return res;
    }
}
#endif
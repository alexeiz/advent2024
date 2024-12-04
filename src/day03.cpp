#include "advent24/common.hpp"
#include "advent24/puzzle_reg.hpp"
#include "advent24/day03.hpp"

using namespace std;

namespace {
int to_int(auto const & m)
{
    return stoi(string{m.first, m.second});
}

/// Multiply some numbers.
/// https://adventofcode.com/2024/day/3
puzzle_reg _1{"3.1", []{
    using day3::memory;

    int sum = 0;
    boost::regex mul_re{R"(mul\((\d{1,3}),(\d{1,3})\))"};
    boost::match_results<string_view::const_iterator> what;
    for (auto start = begin(memory);
         boost::regex_search(start, end(memory), what, mul_re);
         start = what[0].second)
    {
        sum += to_int(what[1]) * to_int(what[2]);
    }

    fmt::println("sum of muls: {}", sum);
}};

/// Conditional multipliers.
/// https://adventofcode.com/2024/day/3#part2
puzzle_reg _2{"3.2", []{
    using day3::memory;

    int sum = 0;
    bool enabled = true;
    boost::regex mul_re{R"(do\(\)|don't\(\)|mul\((\d{1,3}),(\d{1,3})\))"};
    boost::match_results<string_view::const_iterator> what;
    for (auto start = begin(memory);
         boost::regex_search(start, end(memory), what, mul_re);
         start = what[0].second)
    {
        string_view m{what[0].first, what[0].second};
        if (m == "do()"sv)
            enabled = true;
        else if (m == "don't()"sv)
            enabled = false;
        else if (enabled)
            sum += to_int(what[1]) * to_int(what[2]);
    }

    fmt::println("sum of conditional muls: {}", sum);
}};
}

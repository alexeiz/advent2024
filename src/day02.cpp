#include "advent24/common.hpp"
#include "advent24/puzzle_reg.hpp"
#include "advent24/day02.hpp"

using namespace std;

namespace {
auto make_tester(int low, int high)
{
    return [low, high](auto const & p) {
        int diff = get<0>(p) - get<1>(p);
        return low <= diff and diff <= high;
    };
}

auto test_decr = make_tester(1, 3);
auto test_incr = make_tester(-3, -1);

/// Find safe level reports.
/// https://adventofcode.com/2024/day/2
puzzle_reg _1{"2.1", []{
    using day2::levels;

    int safe_count = 0;
    for (auto const & lev: levels)
    {
        auto adj_lev = flux::ref(lev).pairwise();
        if (adj_lev.all(test_decr) or adj_lev.all(test_incr))
            ++safe_count;
    }

    fmt::println("safe reports: {}", safe_count);
}};

/// Count safe level reports with dampener.
/// https://adventofcode.com/2024/day/2#part2
puzzle_reg _2{"2.2", []{
    using day2::levels;

    int safe_count = 0;
    for (auto const & lev: levels)
    {
        auto adj_lev = flux::ref(lev).pairwise();
        if (adj_lev.all(test_decr) or adj_lev.all(test_incr))
            ++safe_count;
        else
        {
            // try without one element
            for (auto n: flux::iota(0l, ssize(lev)))
            {
                auto dampened = flux::zip(flux::ints(), flux::ref(lev))
                    .filter([n](auto const & p) { return get<0>(p) != n; })
                    .map([](auto const & p) { return get<1>(p); })
                    .to<vector>();
                auto adj_lev = flux::ref(dampened).pairwise();
                if (adj_lev.all(test_decr) or adj_lev.all(test_incr))
                {
                    ++safe_count;
                    break;
                }
            }
        }
    }

    fmt::println("safe reports: {}", safe_count);
}};
}

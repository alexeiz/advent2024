#include "advent24/common.hpp"
#include "advent24/puzzle_reg.hpp"
#include "advent24/day02.hpp"

using namespace std;

namespace {
/// Find safe level reports.
/// https://adventofcode.com/2024/day/2
puzzle_reg _1{"2.1", []{
    using day2::levels;

    struct safety
    {
        bool safe;
        strong_ordering order;
        int prev;
    };

    int count_safe = 0;
    for (auto const & lev: levels)
    {
        auto res = flux::fold(
            lev,
            [](safety acc, int v) -> safety {
                if (!acc.safe) return acc;
                if (!acc.prev) return {true, strong_ordering::equal, v};
                int diff = abs(v - acc.prev);
                if (diff < 1 or diff > 3) return {false, acc.order, v};
                if (acc.order == strong_ordering::equal) return {true, acc.prev <=> v, v};
                return {acc.order == (acc.prev <=> v), acc.order, v};
            },
            safety{true, strong_ordering::equal, 0});
        if (res.safe)
            ++count_safe;
    }

    fmt::println("safe reports: {}", count_safe);
}};

/// Count safe level reports with dampener.
/// https://adventofcode.com/2024/day/2#part2
puzzle_reg _2{"2.2", []{
    using day2::levels;

    struct safety
    {
        bool safe;
        strong_ordering order;
        int prev;
        int pos;
    };

    auto tester = [](safety acc, int v) -> safety {
        auto [safe, order, prev, pos] = acc;
        if (!safe) return acc;
        if (pos == 0) return {true, order, v, pos + 1};
        int diff = abs(v - prev);
        if (diff < 1 or diff > 3) return {false, order, v, pos + 1};
        if (pos == 1) return {true, prev <=> v, v, pos + 1};
        return {order == (acc.prev <=> v), order, v, pos + 1};
    };

    int count_safe = 0;
    for (auto const & lev: levels)
    {
        auto res = flux::fold(lev, tester, safety{true, strong_ordering::equal, 0, 0});
        if (!res.safe)
        {
            // try without one element
            for (auto n: flux::iota(0l, ssize(lev)))
            {
                res = flux::ref(lev)
                    .filter([n=n](auto &) mutable { return n-- != 0; })
                    .fold(tester, safety{true, strong_ordering::equal, 0, 0});
                if (res.safe)
                    break;
            }
        }
        if (res.safe)
            ++count_safe;
    }

    fmt::println("safe reports: {}", count_safe);
}};
}

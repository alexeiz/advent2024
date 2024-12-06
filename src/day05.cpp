#include "advent24/common.hpp"
#include "advent24/puzzle_reg.hpp"
#include "advent24/day05.hpp"

using namespace std;

namespace {
/// Find correctly ordered updates.
/// https://adventofcode.com/2024/day/5
puzzle_reg _1{"5.1", []{
    auto const & ordering = day5::ordering;
    using day5::updates;

    auto cmp = [&ordering](int x, int y) { return !ordering.contains({y, x}); };
    int middles = 0;
    for (auto const & upd: updates)
    {
        auto cpy = upd;
        ranges::stable_sort(cpy, cmp);

        if (upd == cpy)
            middles += upd[upd.size() / 2];
    }

    fmt::println("correctly ordered updates: {}", middles);
}};

/// Fix incorrectly ordered updates.
/// https://adventofcode.com/2024/day/5#part2
puzzle_reg _2{"5.2", []{
    auto const & ordering = day5::ordering;
    using day5::updates;

    auto cmp = [&ordering](int x, int y) { return !ordering.contains({y, x}); };
    int middles = 0;
    for (auto const & upd: updates)
    {
        auto cpy = upd;
        ranges::stable_sort(cpy, cmp);

        if (upd != cpy)
            middles += cpy[cpy.size() / 2];
    }

    fmt::println("incorrectly ordered updates: {}", middles);
}};
}

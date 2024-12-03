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
    for (auto & lev : levels)
    {
        auto res = flux::ref(lev).fold(
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
}

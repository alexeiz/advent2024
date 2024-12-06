#include "advent24/common.hpp"
#include "advent24/puzzle_reg.hpp"
#include "advent24/day05.hpp"

using namespace std;

namespace {
using ordering_t = set<pair<int, int>>;

class page_cmp
{
public:
    page_cmp(ordering_t const & ordering)
        : ordering_{ordering}
    {}

    bool operator()(int x, int y) const
    {
        return !ordering_.contains({y, x});
    }

private:
    ordering_t const & ordering_;
};

/// Find correctly ordered updates.
/// https://adventofcode.com/2024/day/5
puzzle_reg _1{"5.1", []{
    using day5::ordering;
    using day5::updates;

    page_cmp cmp{ordering};
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
    using day5::ordering;
    using day5::updates;

    page_cmp cmp{ordering};
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

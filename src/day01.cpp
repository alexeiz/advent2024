#include "advent24/common.hpp"
#include "advent24/puzzle_reg.hpp"
#include "advent24/day01.hpp"

using namespace std;

namespace {
auto split_id_lists(auto const & loc_id_lists)
{
    auto ids1 = flux::ref(loc_id_lists)
            .map([](auto & id_pair) { return std::get<0>(id_pair); })
            .template to<std::vector>();

    auto ids2 = flux::ref(loc_id_lists)
            .map([](auto & id_pair) { return std::get<1>(id_pair); })
            .template to<std::vector>();

    std::ranges::sort(ids1);
    std::ranges::sort(ids2);

    return std::tuple{ids1, ids2};
}

/// Find total distance between location id lists.
/// https://adventofcode.com/2024/day/1
puzzle_reg _1{"1.1", []{
    using day1::loc_id_lists;
    auto [ids1, ids2] = split_id_lists(loc_id_lists);

    // compute distance
    int dist = 0;
    for (auto [id1, id2] : flux::zip(flux::ref(ids1), flux::ref(ids2)))
        dist += std::abs(id1 - id2);

    fmt::println("total distance: {}", dist);
}};

/// Calculate similarity score.
/// https://adventofcode.com/2024/day/1#part2
puzzle_reg _2{"1.2", []{
    using day1::loc_id_lists;
    auto [ids1, ids2] = split_id_lists(loc_id_lists);

    // compute similarity
    int sim = 0;
    auto p1 = flux::begin(ids1);
    auto p2 = flux::begin(ids2);
    while (p1 != flux::end(ids1) and p2 != flux::end(ids2))
    {
        auto cmp = *p1 <=> *p2;
        if (cmp < 0)
            ++p1;
        else if (cmp > 0)
            ++p2;
        else
        {
            auto q1 = p1;
            for (; p1 != flux::end(ids1) && *p1 == *q1; ++p1)
                ;

            auto q2 = p2;
            for (; p2 != flux::end(ids2) && *p2 == *q2; ++p2)
                ;

            sim += *q1 * (p1 - q1) * (p2 - q2);
        }
    }

    fmt::println("similarity: {}", sim);
}};
}

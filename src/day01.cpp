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
    int last_val = -1;
    int count = 0;
    auto p1 = flux::begin(ids1);
    auto p2 = flux::begin(ids2);
    for (; p1 != flux::end(ids1) and p2 != flux::end(ids2); ++p1)
    {
        if (*p1 == last_val)
            sim += *p1 * count;
        else
        {
            for (; p2 != flux::end(ids2) && *p2 < *p1; ++p2)
                ;

            last_val = *p1;
            for (count = 0; p2 != flux::end(ids2) && *p1 == *p2; ++p2, ++count)
                ;

            sim += *p1 * count;
        }
    }

    fmt::println("similarity: {}", sim);
}};
}

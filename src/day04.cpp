#include "advent24/common.hpp"
#include "advent24/puzzle_reg.hpp"
#include "advent24/day04.hpp"

using namespace std;

namespace {
template <typename Field>
struct Matcher
{
    Field mask;
    vector<Field> patterns;
};

template <typename Field>
unsigned count_words(auto const & word_search, vector<Matcher<Field>> const & matchers)
{
    auto rows = size(word_search);
    auto cols = strlen(word_search[0]);

    unsigned words = 0;
    for (size_t x = 0; x != rows; ++x)
    {
        for (size_t y = 0; y != cols; ++y)
        {
            for (auto & m: matchers)
            {
                Field impr{};
                for (size_t i = 0; i != size(impr); ++i)
                {
                    for (size_t j = 0; j != size(impr[i]); ++j)
                    {
                        if (x + i >= rows or y + j >= cols)
                            impr[i][j] = 0;
                        else
                            impr[i][j] = word_search[x + i][y + j] & m.mask[i][j];
                    }
                }

                for (auto & p: m.patterns)
                    words += impr == p;
            }
        }
    }

    return words;
}

/// Xmas word search.
/// https://adventofcode.com/2024/day/4

using field_t = array<array<char, 4>, 4>;
constexpr char X = '\xff';

constexpr field_t mask_v = {{
    {X, 0, 0, 0},
    {X, 0, 0, 0},
    {X, 0, 0, 0},
    {X, 0, 0, 0},
}};

constexpr field_t pattern_v1 = {{
    {'X', 0, 0, 0},
    {'M', 0, 0, 0},
    {'A', 0, 0, 0},
    {'S', 0, 0, 0},
}};

constexpr field_t pattern_v2 = {{
    {'S', 0, 0, 0},
    {'A', 0, 0, 0},
    {'M', 0, 0, 0},
    {'X', 0, 0, 0},
}};

constexpr field_t mask_h = {{
    {X, X, X, X},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
}};

constexpr field_t pattern_h1 = {{
    {'X', 'M', 'A', 'S'},
    { 0,   0,   0,   0 },
    { 0,   0,   0,   0 },
    { 0,   0,   0,   0 },
}};

constexpr field_t pattern_h2 = {{
    {'S', 'A', 'M', 'X'},
    { 0,   0,   0,   0 },
    { 0,   0,   0,   0 },
    { 0,   0,   0,   0 },
}};

constexpr field_t mask_x = {{
    {X, 0, 0, 0},
    {0, X, 0, 0},
    {0, 0, X, 0},
    {0, 0, 0, X},
}};

constexpr field_t pattern_x1 = {{
    {'X', 0,  0,  0 },
    { 0, 'M', 0,  0 },
    { 0,  0, 'A', 0 },
    { 0,  0,  0, 'S'},
}};

constexpr field_t pattern_x2 = {{
    {'S', 0,  0,  0 },
    { 0, 'A', 0,  0 },
    { 0,  0, 'M', 0 },
    { 0,  0,  0, 'X'},
}};

constexpr field_t mask_y = {{
    {0, 0, 0, X},
    {0, 0, X, 0},
    {0, X, 0, 0},
    {X, 0, 0, 0},
}};

constexpr field_t pattern_y1 = {{
    { 0,  0,  0, 'X'},
    { 0,  0, 'M', 0 },
    { 0, 'A', 0,  0 },
    {'S', 0,  0,  0},
}};

constexpr field_t pattern_y2 = {{
    { 0,  0,  0, 'S'},
    { 0,  0, 'A', 0 },
    { 0, 'M', 0,  0 },
    {'X', 0,  0,  0},
}};

puzzle_reg _1{"4.1", []{
    using day4::word_search;

    using matcher = Matcher<field_t>;
    auto const matchers = vector{
        matcher{mask_v, vector{pattern_v1, pattern_v2}},
        matcher{mask_h, vector{pattern_h1, pattern_h2}},
        matcher{mask_x, vector{pattern_x1, pattern_x2}},
        matcher{mask_y, vector{pattern_y1, pattern_y2}},
    };

    fmt::println("XMAS words found: {}", count_words<field_t>(word_search, matchers));
}};

/// X-mas pattern search.
/// https://adventofcode.com/2024/day/4#part2

using field3_t = array<array<char, 3>, 3>;

constexpr field3_t mask_c = {{
    {X, 0, X},
    {0, X, 0},
    {X, 0, X},
}};

constexpr field3_t pattern_c1 = {{
    {'M', 0, 'S'},
    { 0, 'A', 0 },
    {'M', 0, 'S'},
}};

constexpr field3_t pattern_c2 = {{
    {'S', 0, 'M'},
    { 0, 'A', 0 },
    {'S', 0, 'M'},
}};

constexpr field3_t pattern_c3 = {{
    {'M', 0, 'M'},
    { 0, 'A', 0 },
    {'S', 0, 'S'},
}};

constexpr field3_t pattern_c4 = {{
    {'S', 0, 'S'},
    { 0, 'A', 0 },
    {'M', 0, 'M'},
}};

puzzle_reg _2{"4.2", []{
    using day4::word_search;

    using matcher = Matcher<field3_t>;
    auto const matchers = vector{
        matcher{mask_c, vector{pattern_c1, pattern_c2, pattern_c3, pattern_c4}},
    };

    fmt::println("X-MAS patterns found: {}", count_words<field3_t>(word_search, matchers));
}};
}

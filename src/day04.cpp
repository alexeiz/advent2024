#include "advent24/common.hpp"
#include "advent24/puzzle_reg.hpp"
#include "advent24/day04.hpp"

using namespace std;

namespace {

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

struct matcher
{
    field_t mask;
    vector<field_t> patterns;
};

auto const matchers = vector{
    matcher{mask_v, vector{pattern_v1, pattern_v2}},
    matcher{mask_h, vector{pattern_h1, pattern_h2}},
    matcher{mask_x, vector{pattern_x1, pattern_x2}},
    matcher{mask_y, vector{pattern_y1, pattern_y2}},
};

/// Xmas word search.
/// https://adventofcode.com/2024/day/4
puzzle_reg _1{"4.1", []{
    using day4::word_search;
    auto rows = size(word_search);
    auto cols = strlen(word_search[0]);

    unsigned words = 0;
    for (size_t x = 0; x != rows; ++x)
    {
        for (size_t y = 0; y != cols; ++y)
        {
            for (auto & m: matchers)
            {
                field_t impr{};
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

    fmt::println("XMAS words found: {}", words);
}};
}

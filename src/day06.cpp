#include "advent24/common.hpp"
#include "advent24/puzzle_reg.hpp"
#include "advent24/day06.hpp"

using namespace std;
using namespace boost;

namespace {
auto msize(day6::matrix_t const & m, size_t dim)
{
    return day6::matrix_t::index(m.shape()[dim]);
}

auto find_guard(day6::matrix_t const & m)
{
    using enum day6::cell;

    for (day6::matrix_t::index x = 0; x != msize(m, 0); ++x)
    {
        for (day6::matrix_t::index y = 0; y != msize(m, 1); ++y)
            switch (day6::cell{m[x][y]})
            {
            case guard_up:
            case guard_down:
            case guard_left:
            case guard_right:
                return tuple{x, y};
            default:
                break;
            }
    }

    std::unreachable();
}

auto guard_dir(day6::matrix_t const & m, int x, int y)
{
    using enum day6::cell;

    switch (day6::cell{m[x][y]})
    {
    case guard_up:
        return 0;
    case guard_right:
        return 1;
    case guard_down:
        return 2;
    case guard_left:
        return 3;
    default:
        std::unreachable();
    }
}

auto is_inside(day6::matrix_t const & m, int x, int y)
{
    return 0 <= x && x < msize(m, 0) && 0 <= y && y < msize(m, 1);
}

tuple<int, int> dirs[] = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
};

/// Find guard visited positions.
/// https://adventofcode.com/2024/day/6
puzzle_reg _1{"6.1", []{
    using namespace day6;

    matrix_t::index lab_dimy = (ssize(lab_map) - 1) / lab_dimx;
    matrix_t lab{lab_map, extents[lab_dimx][lab_dimy]};

    auto [gx, gy] = find_guard(lab);
    int gdir = guard_dir(lab, gx, gy);
    auto [dx, dy] = dirs[gdir];

    int visited = 0;
    while (true)
    {
        for (; is_inside(lab, gx, gy) && cell{lab[gx][gy]} != cell::obst; gx += dx, gy += dy)
        {
            if (cell{lab[gx][gy]} != cell::visited)
            {
                lab[gx][gy] = char(cell::visited);
                ++visited;
            }
        }

        if (!is_inside(lab, gx, gy))
            break;

        // step back and rotate right
        gx -= dx, gy -= dy;
        gdir = (gdir + 1) % size(dirs);
        tie(dx, dy) = dirs[gdir];
    }

    fmt::println("guard visited positions: {}", visited);
}};
}

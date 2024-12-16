#include "advent24/common.hpp"
#include "advent24/puzzle_reg.hpp"
#include "advent24/day06.hpp"

using namespace std;
using namespace boost;

namespace {
enum class cell : char
{
    obst = '#',
    empty = '.',
    guard_up = '^',
    guard_down = 'v',
    guard_left = '<',
    guard_right = '>',
};

constexpr tuple<int, int> dirs[] = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
};

constexpr char visitor[] = {
    '\x41',
    '\x42',
    '\x44',
    '\x48',
};

constexpr char visit_mask = '\x40';

auto msize(day6::matrix_ref const & m, size_t dim)
{
    return day6::matrix_ref::index(m.shape()[dim]);
}

auto find_guard(day6::matrix_ref const & m)
{
    using enum cell;

    for (day6::matrix_ref::index x = 0; x != msize(m, 0); ++x)
    {
        for (day6::matrix_ref::index y = 0; y != msize(m, 1); ++y)
            switch (cell{m[x][y]})
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

auto guard_dir(day6::matrix_ref const & m, int x, int y)
{
    using enum cell;

    switch (cell{m[x][y]})
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

auto is_inside(day6::matrix_ref const & m, int x, int y)
{
    return 0 <= x && x < msize(m, 0) && 0 <= y && y < msize(m, 1);
}

void clean_lab(day6::matrix_ref & m)
{
    for (day6::matrix_ref::index x = 0; x != msize(m, 0); ++x)
        for (day6::matrix_ref::index y = 0; y != msize(m, 1); ++y)
            if (m[x][y] == char(cell::empty))
                m[x][y] = 0;
}

/// Find guard visited positions.
/// https://adventofcode.com/2024/day/6
puzzle_reg _1{"6.1", []{
    using namespace day6;

    matrix_ref::index lab_dimy = (ssize(lab_map) - 1) / lab_dimx;
    matrix_ref lab{lab_map, extents[lab_dimx][lab_dimy]};
    clean_lab(lab);

    auto [gx, gy] = find_guard(lab);
    int gdir = guard_dir(lab, gx, gy);
    auto [dx, dy] = dirs[gdir];

    int visited = 0;
    lab[gx][gy] = 0;
    while (true)
    {
        for (; is_inside(lab, gx, gy) && cell{lab[gx][gy]} != cell::obst; gx += dx, gy += dy)
        {
            if ((lab[gx][gy] & visit_mask) == 0)
            {
                lab[gx][gy] |= visitor[gdir];
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

/// Find new obstruction positions.
/// https://adventofcode.com/2024/day/6#part2
puzzle_reg _2{"6.2", []{
    using namespace day6;

    matrix_ref::index lab_dimy = (ssize(lab_map) - 1) / lab_dimx;
    matrix_ref lab_ref{lab_map, extents[lab_dimx][lab_dimy]};
    clean_lab(lab_ref);

    auto [gx, gy] = find_guard(lab_ref);
    int gdir = guard_dir(lab_ref, gx, gy);
    lab_ref[gx][gy] = 0;

    auto guard_path = [](matrix_ref const & lab_ref, int gx, int gy, int gdir) {
        vector<tuple<int, int>> guard_path;
        matrix_t lab{lab_ref};
        auto [dx, dy] = dirs[gdir];

        while (true)
        {
            for (; is_inside(lab, gx, gy) && cell{lab[gx][gy]} != cell::obst; gx += dx, gy += dy)
            {
                if ((lab[gx][gy] & visit_mask) == 0)
                {
                    lab[gx][gy] |= visitor[gdir];
                    guard_path.push_back({gx, gy});
                }
            }

            if (!is_inside(lab, gx, gy))
                break;

            // step back and rotate right
            gx -= dx, gy -= dy;
            gdir = (gdir + 1) % size(dirs);
            tie(dx, dy) = dirs[gdir];
        }

        return guard_path;
    }(lab_ref, gx, gy, gdir);

    auto has_loop = [](matrix_t & lab, int gx, int gy, int gdir) {
        auto [dx, dy] = dirs[gdir];

        while (true)
        {
            for (; is_inside(lab, gx, gy) && cell{lab[gx][gy]} != cell::obst; gx += dx, gy += dy)
            {
                if ((lab[gx][gy] & visitor[gdir]) == visitor[gdir])
                    return true;

                lab[gx][gy] |= visitor[gdir];
            }

            if (!is_inside(lab, gx, gy))
                return false;

            // step back and rotate right
            gx -= dx, gy -= dy;
            gdir = (gdir + 1) % size(dirs);
            tie(dx, dy) = dirs[gdir];
        }

        std::unreachable();
    };

    int loop_obst = 0;
    for (auto [x, y]: guard_path)
    {
        if (x == gx and y == gy)
            continue;

        matrix_t lab{lab_ref};
        lab[x][y] = char(cell::obst);
        loop_obst += has_loop(lab, gx, gy, gdir);
    }

    fmt::println("loop obstructions: {}", loop_obst);
}};
}

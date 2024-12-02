#include "advent24/common.hpp"
#include "advent24/puzzle_reg.hpp"

int main(int argc, char * argv[])
{
    if (argc < 2)
    {
        fmt::println(std::cerr, "options: day.puzzle (e.g: 1.1)");
        return 1;
    }

    auto & puzzles = puzzle_reg::puzzles;
    auto puz_name = argv[1];
    if (auto puzzle = puzzles.find(puz_name); puzzle != puzzles.end())
        puzzle->second();
    else
    {
        fmt::println(std::cerr, "puzzle '{}' not found", puz_name);
        return 1;
    }
}

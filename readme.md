# Advent of Code 2024

## Configure and build the project

Configure with:

``` shell
cmake --preset default .
```

Then build:

``` shell
cmake --build build --config Debug --target all
```

You can also open the project in VS Code and choose the **default** as your CMake present.

### Notes

If you want to make changes in `CMakeUserPresets.json` or in `.vscode/`,
add them to `.git/info/exclude` to avoid committing those changes.

## Run puzzle solvers

``` shell
# day 1 puzzle 2
build/advent24 1.2
```

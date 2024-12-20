#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <compare>
#include <cstdint>
#include <cctype>
#include <exception>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <ranges>
#include <regex>
#include <set>
#include <span>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_set>
#include <variant>
#include <vector>

#include <fmt/core.h>
#include <fmt/ostream.h>
#include <fmt/ranges.h>

#include <flux.hpp>
#include <boost/regex.hpp>
#include <boost/multi_array.hpp>

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

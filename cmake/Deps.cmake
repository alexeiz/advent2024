# CPM libraries
include(cmake/CPM.cmake)

CPMAddPackage("gh:fmtlib/fmt#11.0.2")
list(APPEND LIBRARIES fmt::fmt)

CPMAddPackage("gh:tcbrindle/flux#v0.4.0")
list(APPEND LIBRARIES flux::flux)

CPMAddPackage(
  NAME Boost
  VERSION 1.87.0
  URL https://github.com/boostorg/boost/releases/download/boost-1.87.0.beta1/boost-1.87.0.beta1-cmake.tar.xz
  URL_HASH SHA256=31dd2b0aa588d110b96abc1f0e9d9bd894f21f9dd2d28b52ee360fa69a20d09e
  OPTIONS "BOOST_ENABLE_CMAKE ON" "BOOST_INCLUDE_LIBRARIES regex\\\;multi_array"
)
list(APPEND LIBRARIES Boost::regex Boost::multi_array)

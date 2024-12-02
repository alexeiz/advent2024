# CPM libraries
include(cmake/CPM.cmake)

CPMAddPackage("gh:fmtlib/fmt#11.0.2")
list(APPEND LIBRARIES fmt::fmt)

CPMAddPackage("gh:tcbrindle/flux#v0.4.0")
list(APPEND LIBRARIES flux::flux)

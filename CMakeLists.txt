cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

project(
  advent24
  VERSION 0.1
  LANGUAGES CXX)

MESSAGE(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")

# set build type
set(default_build_type "Debug")
if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "Setting build type to '${default_build_type}'")

  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose build type." FORCE)

  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY
      STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif ()

# set compiler flags
set(CMAKE_CXX_STANDARD   23)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Deps.cmake)

# include directories and source files
include_directories(include)
set(SOURCES
    src/main.cpp
    src/day01.cpp
    src/day02.cpp
    src/day03.cpp)

# executable
add_executable(advent24 ${SOURCES})
target_link_libraries(advent24 PRIVATE ${LIBRARIES})

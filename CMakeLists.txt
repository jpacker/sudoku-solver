cmake_minimum_required(VERSION 3.9)

project(sudoku_solver)

include_directories(include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -march=native")

set(THIRDPARTY_DIR ${CMAKE_SOURCE_DIR}/thirdparty)

include(CTest)
enable_testing()
add_subdirectory(test)

set(SOLVER_SOURCES )
set(SOLVER_HEADERS include/solver.h)

set(BINARY_SOURCES src/main.cpp)

add_executable(sudoku_solver ${SOLVER_SOURCES} ${SOLVER_HEADERS} ${BINARY_SOURCES})

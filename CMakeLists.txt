cmake_minimum_required(VERSION 3.12)
project(not_ai)

set(CMAKE_CXX_STANDARD 14)

add_executable(not_ai main.cpp solvers/exact.cpp solvers/exact.h solvers/base.h solvers/base.cpp utils/TestReader.cpp utils/TestReader.h)
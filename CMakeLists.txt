#add_library() Not AI Project CMake File
cmake_minimum_required(VERSION 3.1)
project(not_ai)

# C++ Standard: C++11
set(CMAKE_CXX_STANDARD 11)

# Set Compiler flag for build targets
if (NOT ${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_compile_options(-DDEBUG=true)
else ()
    add_compile_options(-DDEBUG=false)
endif()

# Option: Should check old success submit for intersection?
add_compile_options(-DCHECK_OLD_SUBMIT=true)

# Build process
file(GLOB not_ai_SRCS "src/**/*.cpp")
message("File to be included in build: ${not_ai_SRCS}")

include_directories("opencv/include")
include_directories("opencv/include/opencv")

set(OPENCV_LIBS opencv_core opencv_highgui opencv_imgproc opencv_imgcodecs)
foreach(lib ${OPENCV_LIBS})
    add_library(${lib} SHARED IMPORTED)
    set_property(TARGET ${lib} PROPERTY IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/opencv/lib/lib${lib}.so")
    message("${lib} == ${CMAKE_SOURCE_DIR}/opencv/lib/lib${lib}.so")
endforeach()

add_executable(not_ai src/main.cpp ${not_ai_SRCS})
target_link_libraries(not_ai ${OPENCV_LIBS})

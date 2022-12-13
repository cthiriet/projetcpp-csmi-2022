# minimal version of cmake
cmake_minimum_required(VERSION 3.3)

# project name
project(finite_element)

# include directory path
include_directories(include)

# source files
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

# type of compilation
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RELEASE)
endif()

# compilation options
set(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wall")

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message("   Compiler CXX:         ${CMAKE_CXX_COMPILER}")
message("   Compiler CXX flags:         ${CMAKE_CXX_FLAGS}")
if(CMAKE_BUILD_TYPE MATCHES "DEBUG")
message("   Compiler CXX debug flags:   ${CMAKE_CXX_FLAGS_DEBUG}")
endif(CMAKE_BUILD_TYPE MATCHES "DEBUG")
if(CMAKE_BUILD_TYPE MATCHES "RELEASE")
message("   Compiler CXX release flags: ${CMAKE_CXX_FLAGS_RELEASE}")
endif(CMAKE_BUILD_TYPE MATCHES "RELEASE")

# add eigen library
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
include_directories(${EIGEN3_INCLUDE_DIR})

# create library libfinel.a
add_library(finel ${SOURCE_FILES})

# create executable
add_executable(run src/main.cpp)

# link libraries
target_link_libraries(run finel Eigen3::Eigen)

# generate tests binary
enable_testing()

file(GLOB_RECURSE TEST_FILES tests/*.cpp)

foreach(test_full_path ${TEST_FILES})
  get_filename_component(test_filename ${test_full_path} NAME)
  string(CONCAT test_filename "tests/" ${test_filename})
  get_filename_component(test_name ${test_filename} NAME_WE)
  add_executable(${test_name} ${test_filename})
  add_test(${test_name} ${test_name})
  target_link_libraries(${test_name} finel Eigen3::Eigen)
endforeach()

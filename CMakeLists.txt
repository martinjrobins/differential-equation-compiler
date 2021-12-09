# This CMakeLists was derived from 
# https://github.com/cpp-best-practices/cpp_starter_project
cmake_minimum_required(VERSION 3.15)
project(DiffEqCompiler CXX)

include(cmake/PreventInSourceBuilds.cmake)
include(cmake/StaticAnalyzers.cmake)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

include(cmake/CompilerWarnings.cmake)
enable_sanitizers(project_options)

option(ENABLE_CONAN "Use Conan for dependency management" ON)
if(ENABLE_CONAN)
  include(cmake/Conan.cmake)
  run_conan()
endif()

option(ENABLE_TESTING "Enable Test Builds" ON)
if(ENABLE_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif()

add_subdirectory(src)




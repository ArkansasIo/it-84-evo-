cmake_minimum_required(VERSION 3.20)
project(TI84EvoClone VERSION 0.1.0 LANGUAGES CXX)
option(TI84EVO_BUILD_TESTS "Build unit tests" ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(ti84core
  src/core/expression.cpp
  src/core/calculator.cpp
  src/graph/graph.cpp
  src/math/matrix.cpp
  src/math/statistics.cpp
  src/storage/memory_store.cpp
  src/program/basic_runtime.cpp)
target_include_directories(ti84core PUBLIC include)
if(MSVC)
  target_compile_options(ti84core PRIVATE /W4 /permissive-)
else()
  target_compile_options(ti84core PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(ti84evo src/app/main.cpp)
target_link_libraries(ti84evo PRIVATE ti84core)
if(TI84EVO_BUILD_TESTS)
  enable_testing()
  add_executable(ti84evo_tests tests/test_main.cpp)
  target_link_libraries(ti84evo_tests PRIVATE ti84core)
  add_test(NAME ti84evo_tests COMMAND ti84evo_tests)
endif()

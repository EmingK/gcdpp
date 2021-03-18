cmake_minimum_required(VERSION 3.12)
project(gcdpp)

if(NOT APPLE)
  include(cmake/FindDispatch.cmake)
endif()

add_library(gcdpp STATIC
  src/work.cpp
  src/queue.cpp
  src/group.cpp
  src/semaphore.cpp
  )

target_compile_features(
  gcdpp PUBLIC
  cxx_std_11
  )

target_include_directories(
  gcdpp PUBLIC
  src/include
  )
if(NOT APPLE)
  target_include_directories(
    gcdpp PUBLIC
    ${LIBDISPATCH_INCLUDE_DIR}
    )
endif()

option(BUIULD_TESTS "Build test programs" OFF)
if (BUILD_TESTS)
  add_executable(gcdpp_test
    examples/test.cpp
    )

  add_dependencies(gcdpp_test gcdpp)
  target_link_libraries(gcdpp_test gcdpp)
endif()

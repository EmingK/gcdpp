cmake_minimum_required(VERSION 3.12)
project(gcdpp)

add_library(gcdpp STATIC
  src/work.cpp
  src/queue.cpp
  src/group.cpp
  src/semaphore.cpp
  src/data.cpp
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
    ${GCDPP_LIBDISPATCH_DIR}/include
    )
endif()

include(GNUInstallDirs)
file(GLOB GCDPP_INCLUDE_FILES "src/include/gcdpp/*.h")
install(
  TARGETS gcdpp
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
install(
  FILES ${GCDPP_INCLUDE_FILES}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/gcdpp)

option(BUIULD_TESTS "Build test programs" OFF)
if (BUILD_TESTS)
  add_executable(gcdpp_test
    examples/test.cpp
    )

  add_dependencies(gcdpp_test gcdpp)
  target_link_directories(gcdpp_test PRIVATE
    ${GCDPP_LIBDISPATCH_DIR}/lib
    )
  target_link_libraries(gcdpp_test gcdpp)
  if (NOT APPLE)
    target_link_libraries(gcdpp_test dispatch BlocksRuntime)
  endif()
endif()

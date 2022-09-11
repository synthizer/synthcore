cmake_minimum_required(VERSION 3.15.0)
project(synthcore VERSION 0.1.0 LANGUAGES C CXX)

include(ctest)
enable_testing()

# Do this first; some things will quietly pick it up and it's
# really hard to tell which.
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(deps)

set(SZC_DEPS
  boost_partial
  concurrentqueue
  cpp11-on-multicore
  dr_libs
  hedley
  miniaudio
  pdqsort
)

# We handle this as a Synthizer option a few levels above, which propagates down if set globally. Disables tests etc.
# for bindings generation.
if(NOT "${SYZ_INTEGRATING}")
  set(SZC_TEST_DEPS catch2)
endif()

FetchContent_MakeAvailable(${SZC_DEPS} ${SZC_TEST_DEPS})

add_library(synthcore STATIC
  src/check_all_headers.cpp
  src/data/primes.cpp
)
target_include_directories(synthcore PUBLIC include)
target_link_libraries(synthcore ${SZC_DEPS})
if(NOT SYZ_INTEGRATING)
  list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
  INCLUDE(Catch)

  add_executable(tests
    tests/block_delay_line.cpp
    tests/generation_thread.cpp
    tests/latch.cpp
    tests/math.cpp
    tests/mod_pointer.cpp
    tests/random_float.cpp
  )
  target_link_libraries(tests PRIVATE Catch2::Catch2WithMain synthcore)
  catch_discover_tests(tests)
endif()

cmake_minimum_required(VERSION 3.15.0)
project(synthcore VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
include(FetchContent)

enable_testing()

find_package(Threads)

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
# for bindings integrations.
if(NOT "${SYZ_INTEGRATING}")
  set(SZC_TEST_DEPS catch2)
endif()

FetchContent_MakeAvailable(${SZC_DEPS} ${SZC_TEST_DEPS})

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Xclang -fno-caret-diagnostics
    -Wno-deprecated-declarations
    -Wno-logical-op-parentheses
    -Wno-unknown-pragmas
    # We have warning pragmas that are GCC specific.
    -Wno-unknown-warning-option
  )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  add_compile_options(
    # Lets us use Clang pragmas.
    /wd4068
    # Lets us use non-MSVC attributes.
    /wd5030
    # allows implicit casts to smaller types. We need this because we can't i.e. std::copy(double, float) without
    # hitting it.
    /wd4244
    /wd4267
    # Lets property generation work, namely property_impl.hpp
    /Zc:preprocessor
    # And now we need to silence a winbase.h warning because it's got a macro expanding to undefined somehow. Noe that
    # this isn't our code:
    /wd5105
    # Not all compilers give us constexpr if, but MSVC likes to warn us when we can use it.
    /wd4127
    # Documented here: https://devblogs.microsoft.com/cppblog/broken-warnings-theory/
    # By using this and putting Synthizer dependency headers behind <>, we can suppress warnings in dependencies.
    /experimental:external
    /external:W0
    /external:anglebrackets
    # Apparently we have to globally disable unreachable code warnings; MSVC isn't letting us do it in a
    # targeted fashion.
    /wd4702
  )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  ADD_COMPILE_OPTIONS(-Wno-unknown-pragmas)
endif()

add_library(synthcore STATIC
  src/check_all_headers.cpp
  src/data/primes.cpp
)
target_include_directories(synthcore PUBLIC include)
target_link_libraries(synthcore ${SZC_DEPS} Threads::Threads)

if(MSVC)
  target_compile_options(synthcore PRIVATE /W4 /WX)
else()
  target_compile_options(synthcore PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

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

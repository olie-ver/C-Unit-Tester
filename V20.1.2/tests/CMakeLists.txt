cmake_minimum_required(VERSION 3.20)

set(TEST_SOURCES
    src/assert.cpp
    src/bool.cpp
    src/cmp.cpp 
    src/flt.cpp
    src/iterable.cpp 
    src/meta.cpp
    src/null.cpp 
    src/predicate.cpp 
    src/set.cpp 
    src/short.cpp 
    src/string.cpp
    src/throws.cpp
)

add_executable(cliTest
   ${TEST_SOURCES}
)

target_compile_features(cliTest PUBLIC cxx_std_20)

target_link_libraries(cliTest PUBLIC testpp_main)
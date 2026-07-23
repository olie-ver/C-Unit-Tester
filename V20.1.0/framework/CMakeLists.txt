#testpp contains all the static files/dependencies such as testing functions
#   macros, etc
#testpp_main is a library built on top of testpp containing the main() function
#   so it can actually run tests

cmake_minimum_required(VERSION 3.20)

option(ENABLE_SANITIZERS "Enable sanitizers" OFF)

if(ENABLE_SANITIZERS AND NOT MSVC)
    message(STATUS "Sanitizers enabled")

    add_compile_options(
        -fsanitize=address
        -fsanitize=undefined
        -fno-omit-frame-pointer
        -g
    )

    add_link_options(
        -fsanitize=address
        -fsanitize=undefined
    )
endif()

find_package(Threads REQUIRED)

set(TESTPP_SOURCES
    src/Multithread.cpp
    src/ProcessArgs.cpp
    src/RenderConsole.cpp
    src/Renderer.cpp
    src/RenderJson.cpp
    src/RenderXml.cpp
    src/Runner.cpp
)

if(WIN32)
    list(APPEND TESTPP_SOURCES
        src/platform/windows/isolation_windows.cpp
    )
else()
    list(APPEND TESTPP_SOURCES
        src/platform/unix/isolation_unix.cpp
    )
endif()

add_library(testpp ${TESTPP_SOURCES})

set_target_properties(testpp PROPERTIES
    UNITY_BUILD ON
)

target_precompile_headers(testpp PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/testpp/internal/PCH/impl_pch.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/testpp/internal/PCH/core_pch.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/testpp/internal/PCH/src_pch.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/testpp/internal/PCH/pch.hpp"
)

target_compile_features(testpp PUBLIC cxx_std_20)

target_include_directories(testpp
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(testpp PUBLIC Threads::Threads)

if (MSVC)
    target_compile_options(testpp PRIVATE /W4)
else()
    target_compile_options(testpp PRIVATE
        -Wall
        -Wextra
        -pedantic
        -Winvalid-pch
    )
endif()

add_library(testpp_main STATIC
    src/Main.cpp
)

target_compile_features(testpp_main PUBLIC cxx_std_20)
target_precompile_headers(
    testpp_main
    REUSE_FROM testpp
)

target_link_libraries(testpp_main PUBLIC testpp)

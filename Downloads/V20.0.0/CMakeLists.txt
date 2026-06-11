# Need to make a modification so that it compiles relative to this directory so __FILE__ doesn't print full path?

cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

project(
    testpp
    VERSION 20.0.0
    LANGUAGES CXX
)

option(ENABLE_SANITIZERS "Enable sanitizers" OFF)

if(ENABLE_SANITIZERS)
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

add_library(testpp
    src/Multithread.cpp
    src/ProcessArgs.cpp
    src/RenderConsole.cpp
    src/Renderer.cpp
    src/RenderJson.cpp
    src/RenderXml.cpp
    src/Runner.cpp
    src/platform/unix/isolation_unix.cpp
)

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

add_executable(runTests
    src/Main.cpp
    #your tests go here
    yourTests/example.cpp
)

target_link_libraries(runTests PRIVATE testpp)

enable_testing()

add_test(NAME framework_tests COMMAND runTests)

install(
    TARGETS testpp
    EXPORT testppTargets
)

install(
    DIRECTORY include/
    DESTINATION include
)

install(
    EXPORT testppTargets
    FILE testppTargets.cmake
    NAMESPACE testpp::
    DESTINATION lib/cmake/testpp
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    cmake/testppConfig.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/testppConfig.cmake"
    INSTALL_DESTINATION lib/cmake/testpp
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/testppConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/testppConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/testppConfigVersion.cmake"
    DESTINATION
        lib/cmake/testpp
)
cmake_minimum_required(VERSION 3.20)

project (
    testpp
    VERSION 20.1.0
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(framework)
add_subdirectory(cli)
# add_subdirectory(tests)

#install the framework into lib
install(TARGETS
    testpp
    testpp_main
    EXPORT testppTargets
    ARCHIVE DESTINATION lib
)

#install the include folder into include
install(
    DIRECTORY framework/include/
    DESTINATION include
)

#install the CLI into bin
install(TARGETS
    testpp_cli
    RUNTIME DESTINATION bin
)

#install the default config and CMake template into var
#if either or these are deleted => "now that wasn't very smart of you now was it?"
install(
    FILES
        resources/default.conf
        resources/CMakeLists.txt.in
    DESTINATION var
)

#ensure that the user has a config file upon installation in the run/ folder
install(
    FILES resources/default.conf
    DESTINATION run
    RENAME config.conf
)

#Create and install empty directories for runtime
install(DIRECTORY DESTINATION run)
install(DIRECTORY DESTINATION run/build)
install(DIRECTORY DESTINATION run/build/bin)

# cmake_minimum_required(VERSION 3.20)

# project(
#     testpp
#     VERSION 20.0.6
#     LANGUAGES CXX
# )

# option(ENABLE_SANITIZERS "Enable sanitizers" OFF)

# if(ENABLE_SANITIZERS AND NOT MSVC)
#     message(STATUS "Sanitizers enabled")

#     add_compile_options(
#         -fsanitize=address
#         -fsanitize=undefined
#         -fno-omit-frame-pointer
#         -g
#     )

#     add_link_options(
#         -fsanitize=address
#         -fsanitize=undefined
#     )
# endif()

# find_package(Threads REQUIRED)

# set(TESTPP_SOURCES
#     src/Multithread.cpp
#     src/ProcessArgs.cpp
#     src/RenderConsole.cpp
#     src/Renderer.cpp
#     src/RenderJson.cpp
#     src/RenderXml.cpp
#     src/Runner.cpp
# )

# if(WIN32)
#     list(APPEND TESTPP_SOURCES
#         src/platform/windows/isolation_windows.cpp
#     )
# else()
#     list(APPEND TESTPP_SOURCES
#         src/platform/unix/isolation_unix.cpp
#     )
# endif()

# add_library(testpp ${TESTPP_SOURCES})

# set_target_properties(testpp PROPERTIES
#     UNITY_BUILD ON
# )

# target_precompile_headers(testpp PRIVATE
#     "${CMAKE_CURRENT_SOURCE_DIR}/include/testpp/internal/PCH/impl_pch.hpp"
#     "${CMAKE_CURRENT_SOURCE_DIR}/include/testpp/internal/PCH/core_pch.hpp"
#     "${CMAKE_CURRENT_SOURCE_DIR}/include/testpp/internal/PCH/src_pch.hpp"
#     "${CMAKE_CURRENT_SOURCE_DIR}/include/testpp/internal/PCH/pch.hpp"
# )

# target_compile_features(testpp PUBLIC cxx_std_20)

# target_include_directories(testpp
#     PUBLIC
#         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#         $<INSTALL_INTERFACE:include>
# )

# target_link_libraries(testpp PUBLIC Threads::Threads)

# if (MSVC)
#     target_compile_options(testpp PRIVATE /W4)
# else()
#     target_compile_options(testpp PRIVATE
#         -Wall
#         -Wextra
#         -pedantic
#         -Winvalid-pch
#     )
# endif()

# add_library(testpp_main STATIC
#     src/Main.cpp
# )

# target_link_libraries(
#     testpp_main
#     PUBLIC
#     testpp
# )

# add_executable(runTests
#     src/Main.cpp
# )

# target_link_libraries(
#     runTests
#     PRIVATE
#     testpp_main
#     testpp
# )

# add_executable(cliTest
#     # src/Main.cpp
#     tests/string.cpp
#     tests/flt.cpp
# )

# target_link_libraries(
#     cliTest
#     PRIVATE
#     testpp_main
#     testpp
# )

# add_executable(testpp_cli
#     cli/Main.cpp
#     cli/CreateCMake.cpp
#     cli/Installation.cpp
#     cli/CreateConfig.cpp
# )

# target_compile_features(testpp_cli PRIVATE cxx_std_20)

# set_target_properties(testpp_cli PROPERTIES
#     OUTPUT_NAME testpp
# )

# enable_testing()

# add_test(NAME framework_tests COMMAND runTests)

# install(
#     TARGETS
#         testpp
#         testpp_main
#     EXPORT testppTargets
# )

# install(
#     DIRECTORY include/
#     DESTINATION include
# )

# install(
#     EXPORT testppTargets
#     FILE testppTargets.cmake
#     NAMESPACE testpp::
#     DESTINATION lib/cmake/testpp
# )

# install(
#     TARGETS testpp_cli
#     RUNTIME DESTINATION bin
# )

# install (
#     DIRECTORY templates/
#     DESTINATION share
# )

# include(CMakePackageConfigHelpers)

# configure_package_config_file(
#     cmake/testppConfig.cmake.in
#     "${CMAKE_CURRENT_BINARY_DIR}/testppConfig.cmake"
#     INSTALL_DESTINATION lib/cmake/testpp
# )

# write_basic_package_version_file(
#     "${CMAKE_CURRENT_BINARY_DIR}/testppConfigVersion.cmake"
#     VERSION ${PROJECT_VERSION}
#     COMPATIBILITY SameMajorVersion
# )

# install(
#     FILES
#         "${CMAKE_CURRENT_BINARY_DIR}/testppConfig.cmake"
#         "${CMAKE_CURRENT_BINARY_DIR}/testppConfigVersion.cmake"
#     DESTINATION
#         lib/cmake/testpp
# )
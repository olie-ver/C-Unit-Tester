cmake_minimum_required(VERSION 3.20)

project (
    testpp
    VERSION 20.1.3
    LANGUAGES CXX
)

include(CMakePackageConfigHelpers)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# // Source - https://stackoverflow.com/a/41361741
# // Posted by Angew is no longer proud of SO, modified by community. See post 'Timeline' for change history
# // Retrieved 2026-08-04, License - CC BY-SA 3.0

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# end of SO code

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
        resources/default_cxx.conf
        resources/default_flag.conf
        resources/CMakeLists.txt.in
    DESTINATION var
)

#ensure that the user has a config file upon installation in the run/ folder
install(
    FILES resources/default_flag.conf
    DESTINATION run
    RENAME config_flags.conf
)

install (
    FILES resources/default_cxx.conf
    DESTINATION run
    RENAME config_cxx.conf
)

#Create and install empty directories for runtime
install(DIRECTORY DESTINATION run)

#TODO: Want to have no dependency on a build directory in the future
# install(DIRECTORY DESTINATION run/build)

#install Test++ as a package
install(
    EXPORT testppTargets
    FILE testppTargets.cmake
    NAMESPACE testpp::
    DESTINATION lib/cmake/testpp
)

#generate the package config
configure_package_config_file(
    cmake/testppConfig.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/testppConfig.cmake"
    INSTALL_DESTINATION lib/cmake/testpp
)

#generate the version file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/testppConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

#install them
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/testppConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/testppConfigVersion.cmake"
    DESTINATION lib/cmake/testpp
)
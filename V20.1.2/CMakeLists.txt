cmake_minimum_required(VERSION 3.20)

project (
    testpp
    VERSION 20.1.2
    LANGUAGES CXX
)

include(CMakePackageConfigHelpers)

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
#The CLI contains the files needed to create a CLI executable

cmake_minimum_required(VERSION 3.20)

add_executable(testpp_cli
    src/Main.cpp
    src/Installation.cpp
    src/CreateConfig.cpp
    src/Helpers.cpp
)

target_compile_features(testpp_cli PRIVATE cxx_std_20)

set_target_properties(testpp_cli PROPERTIES
    OUTPUT_NAME testpp
)
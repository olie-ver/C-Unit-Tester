#The CLI contains the files needed to create a CLI executable

cmake_minimum_required(VERSION 3.20)

set(CLI_SOURCES
    src/Main.cpp
    src/Installation.cpp
    src/CreateConfig.cpp
    src/CreateCMake.cpp 
)

add_executable(testpp_cli
    ${CLI_SOURCES}
)

target_compile_features(testpp_cli PRIVATE cxx_std_20)

set_target_properties(testpp_cli PROPERTIES
    OUTPUT_NAME testpp
)
This directory for the C++20 version of Test++ is an downloadable/installable directory
If you want a development version, you should go to V20.0.0 and use that one.

(DON'T DO THIS YET ITS NOT STABLE!!!!)
In order to install:
Make sure you are in the V20.0.0 directory (this one).
Run: 
cmake -S . -B build
cmake --build build --parallel
sudo cmake --install build

Then in a CMakeLists.txt:
cmake_minimum_required(VERSION 3.20)

project(TestConsumer) #replace TestConsumer with your own project name

find_package(testpp REQUIRED)

#you can change the name of the executable
#as well as what files go into it
add_executable(main main.cpp)

#no need to write your own main(), just like normal
target_link_libraries(
    main
    PRIVATE
    testpp::testpp_main
)
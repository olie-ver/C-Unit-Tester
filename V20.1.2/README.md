This directory for the C++20 version of Test++ is an experimentation/development directory.
If you want a downloadable version, you should go to Downloads/V20.0.0 and use it there

To test install:

In the root folder (V20.X.X):
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=install
cmake --build build --parallel
cmake --install build

This will make it so that it's installed in a build directory instead of on your system
in case you (me) want to try it out/debug 
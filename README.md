# Test++
Test++ is a header-only C++ unit testing library and framework. 
It is available for download and installation on Mac, Windows, and Linux, 
however, its development is done on Mac, and its usage in other operating 
systems is largely untested. It is completely open source and free to use. 
It is currently built using C++20, and usage with other languages/C++ standards 
has not yet been tested.

# Installation

In order to use Test++ as a CLI tool, you will need CMake installed on your system.
This CMake requirement is not present when you use Test++ as a library. 

## Homebrew (Preferred)
If you have a Mac, you can install Test++ via Homebrew.

```bash
brew trust olie-ver/testpp
brew tap olie-ver/testpp
brew install testpp
```
After this you can start using the testpp command immediately without needing to register the path. 
To uninstall, run 

```bash
brew uninstall testpp
```

## Manual Installation

In order to manually install Test++, go to the Downloads folder and download the V20.1.2.zip file.
Extract the files. Open a new terminal inside the V20.1.2 folder and then run the following commands:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
sudo cmake --install build
```

Then to register the `testpp` command in your system, you can run:
```bash
echo 'export PATH="$HOME/testpp-install/bin:$PATH"' >> ~/.zshrc
```
# Test++
A C++ Unit Testing library I'm building to be used in my other projects
because even though I know how to use someone else's library, I don't want to include
every file in every project. I know I could probably just compile someone else's 
into a static library and call it a day, but I want the learning experience as well. 

6/12/26
This is now installable on Mac, Linux, and Windows either via the command line or Homebrew.

Mac/Linux (CLI)
Download the Downloads/V20.0.0 folder
cd into it
Run these commands:
rm -rf build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
sudo cmake --install build

With that, you can now use the testpp command in your terminal. 
Read the documentation for further details.

Mac/Linux (Homebrew)
Run these commands:
brew tap olie-ver/testpp
brew install testpp

With that, you can now use the testpp command in your terminal. 
Read the documentation for further details.
(I recommend this way so you can also uninstall easier)

To add to your includes (So VSCode can find it):
"includePath": [
    "/opt/homebrew/opt/testpp/include"
],

Windows (CLI)
I have no clue. I don't have a Windows computer, and using a Windows VM is absolute torture

5/19/26
TODO:
Create a concept that detects mixed sign types and disallow comparisons unless the user opts out of it
Create tests for failing an Assert test actually stops testing for a test suite
Redo the documentation for after these changes are implemented

5/18/26
Refactored all tests in the V20.0.0 folder. Created a new meta test for failing with a message

5/16/26
Implemented from the list of tests to be implemented:
7. All of, any of, none of (predicate testing)

Total tests implemented:
1. Same set/Not same set
2. Ordered not equals/Unordered not equals
3. Subset/Superset
4. Strict subset
5. Contains/Does not contain
6. Container size, container empty/not empty
7. All of, any of, none of (predicate testing)
8. Float infinity/negative infinity
9. String contains
10. String starts/ends with
11. Throws with message

As of now, my C++ unit tester is complete! Is it 100% done? No, but it is functional now.
LinkedIn post time!!!!

5/14/25
Implemented from the list of tests to be implemented:
1. Same set/Not same set
2. Ordered not equals/Unordered not equals
3. Subset/Superset
4. Strict subset

Total tests implemented:
1. Same set/Not same set
2. Ordered not equals/Unordered not equals
3. Subset/Superset
4. Strict subset
5. Contains/Does not contain
6. Container size, container empty/not empty
8. Float infinity/negative infinity
9. String contains
10. String starts/ends with
11. Throws with message

Still need:
7. All of, any of, none of (predicate testing)

5/13/26
Implemented from the list of tests to be implemented:
5. Contains/Does not contain
6. Container size, container empty/not empty
8. Float infinity/negative infinity
11. Throws with message

Total tests implemented:
5. Contains/Does not contain
6. Container size, container empty/not empty
8. Float infinity/negative infinity
9. String contains
10. String starts/ends with
11. Throws with message

Still need:
1. Same set/Not same set
2. Ordered not equals/Unordered not equals
3. Subset/Superset
4. Strict subset
7. All of, any of, none of (predicate testing)

5/2/26
Implemented from the previous entry:
9. String contains
10. String starts/ends with

4/30/26
Future tests that will be implemented:
1. Same set/Not same set
2. Ordered not equals/Unordered not equals
3. Subset/Superset
4. Strict subset
5. Contains/Does not contain
6. Container size, container empty/not empty
7. All of, any of, none of (predicate testing)
8. Float infinity/negative infinity
9. String contains
10. String starts/ends with
11. Throws with message

4/18/26
I moved away from writing and compiling with C++17 in favor for C++20.

4/16/26
At the moment I will be writing and compiling with C++ 17, as seen with the v17.0.0 folder.
However, I may eventually write and compile with a later version of C++ as a way of maintenance
and keeping it modern.

If you're feeling gutsy, you should use it in your projects and tell me what you think. Otherwise, just take a look around. Be sure to read the Documentation.md file in the v20.0.0 folder if you are thinking of using in your projects before downloading.

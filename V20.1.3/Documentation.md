# C++ Unit Tester V20.1.3
A C++ Unit Tester for C++20 written by Oliver Lie. Even as a more or less stable release, I still make no guarantees that future versions will work the same, and implementations could change.

### License/Conditions of Usage
This software is released under the MIT license.

MIT License

Copyright (c) 2026 Oliver A. Lie

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## Table of Contents
1. [Adding To Your Projects](#adding-to-your-projects)
    1. [Installation](#installation)
    2. [Compiling And Linking](#compiling-and-linking)
    3. [Include Inside Your Projects](#include-inside-your-project)
    4. [CLI Usage](#cli-usage)
        1. [Verbosity](#verbosity)
        2. [Threads](#threads)
        3. [Timeout](#timeouts)
        3. [Skipping Tests](#skipping-tests)
        4. [Specifying Tests](#test-specific)
        5. [Streaming Output](#streaming-output)
        6. [JSON Output](#json-output)
        7. [XML Output](#xml-output)
        8. [stdout/stderr Output](#stdoutstderr-output)
2. [Testing](#testing)
    1. [Registering Tests](#registering-tests)
    2. [Different Types Of Tests](#different-types-of-tests)
3. [Boolean Tests](#boolean-tests)
    1. [Assert True](#assert_true)
    2. [Assert False](#assert_false)
    3. [Expect True](#expect_true)
    4. [Expect False](#expect_false)
4. [Comparison Tests](#comparison-tests)
    1. [Assert Equals](#assert_eq)
    2. [Assert Not Equals](#assert_ne)
    3. [Assert Less Than](#assert_lt)
    4. [Assert Less Than or Equals](#assert_le)
    5. [Assert Greater Than](#assert_gt)
    6. [Assert Greater Than or Equals](#assert_ge)
    7. [Expect Equals](#expect_eq)
    8. [Expect Not Equals](#expect_ne)
    9. [Expect Less Than](#expect_lt)
    10. [Expect Less Than or Equals](#expect_le)
    11. [Expect Greater Than](#expect_gt)
    12. [Expect Greater Than or Equals](#expect_ge)
5. [Float Tests](#float-tests)
    1. [Assert Near](#assert_near)
    2. [Assert Absolutely Near](#assert_abs_near)
    3. [Assert Relatively Near](#assert_rel_near)
    4. [Assert NaN](#assert_nan)
    5. [Assert Not NaN](#assert_not_nan)
    6. [Assert Infinity](#assert_inf)
    7. [Assert Positive Infinity](#assert_pos_inf)
    8. [Assert Negative Infinity](#assert_neg_inf)
    9. [Expect Near](#expect_near)
    10. [Expect Absolutely Near](#expect_abs_near)
    11. [Expect Relatively Near](#expect_rel_near)
    12. [Expect NaN](#expect_nan)
    13. [Expect Not NaN](#expect_not_nan)
    14. [Expect Infinity](#expect_inf)
    15. [Expect Positive Infinity](#expect_pos_inf)
    16. [Expect Negative Infinity](#expect_neg_inf)
6. [Iterable Tests](#iterable-tests)
    1. [Assert Ordered Equals](#assert_ordered_eq)
    2. [Assert Unordered Equals](#assert_unordered_eq)
    3. [Assert Ordered Not Equals](#assert_ordered_ne)
    4. [Assert Unordered Not Equals](#assert_unordered_ne)
    5. [Assert Empty](#assert_empty)
    6. [Assert Not Empty](#assert_nempty)
    7. [Assert Size](#assert_size)
    8. [Assert Contains](#assert_contains)
    9. [Assert Does Not Contain](#assert_does_not_contain)
    10. [Expect Ordered Equals](#expect_ordered_eq)
    11. [Expect Unordered Equals](#expect_unordered_eq)
    12. [Expect Ordered Not Equals](#expect_ordered_ne)
    13. [Expect Unordered Not Equals](#expect_unordered_ne)
    14. [Expect Empty](#expect_empty)
    15. [Expect Not Empty](#expect_nempty)
    16. [Expect Size](#expect_size)
    17. [Expect Contains](#expect_contains)
    18. [Expect Does Not Contain](#expect_does_not_contain)
7. [Meta Tests](#meta-tests)
    1. [Assert Passes](#assert_passes)
    2. [Assert Fails](#assert_fails)
    3. [Expect Passes](#expect_passes)
    4. [Expect Fails](#expect_fails)
8. [Null Tests](#null-tests)
    1. [Assert Null](#assert_null)
    2. [Assert Not Null](#assert_not_null)
    3. [Expect Null](#expect_null)
    4. [Expect Not Null](#expect_not_null)
9. [Predicate Tests](#predicate-tests)
    1. [Assert All](#assert_all)
    2. [Assert Some](#assert_some)
    3. [Assert None](#assert_none)
    4. [Expect All](#expect_all)
    5. [Expect Some](#expect_some)
    6. [Expect None](#expect_none)
10. [Set Tests](#set-tests)
    1. [Assert Set Equals](#assert_set_eq)
    2. [Assert Set Not Equals](#assert_set_ne)
    3. [Assert Subset](#assert_subset)
    4. [Assert Superset](#assert_superset)
    5. [Assert Strict Subset](#assert_strict_subset)
    6. [Expect Set Equals](#expect_set_eq)
    7. [Expect Set Not Equals](#expect_set_ne)
    8. [Expect Subset](#expect_subset)
    9. [Expect Superset](#expect_superset)
    10. [Expect Strict Subset](#expect_strict_subset)
11. [String Tests](#string-tests)
    1. [Assert String Equals](#assert_str_eq)
    2. [Assert String Not Equals](#assert_str_ne)
    3. [Assert String Empty](#assert_str_emt)
    4. [Assert String Not Empty](#assert_str_nemt)
    5. [Assert String Contains](#assert_str_contains)
    6. [Assert String Starts With](#assert_str_starts_with)
    7. [Assert String Ends With](#assert_str_ends_with)
    8. [Expect String Equals](#expect_str_eq)
    9. [Expect String Not Equals](#expect_str_ne)
    10. [Expect String Empty](#expect_str_emt)
    11. [Expect String Not Empty](#expect_str_nemt)
    12. [Expect String Contains](#expect_str_contains)
    13. [Expect String Starts With](#expect_str_starts_with)
    14. [Expect String Ends With](#expect_str_ends_with)
12. [Throws Tests](#throws-tests)
    1. [Assert Throws](#assert_throws)
    2. [Assert Does Not Throw](#assert_does_not_throw)
    3. [Assert Throws With Message](#assert_throws_msg)
    4. [Expect Throws](#expect_throws)
    5. [Expect Does Not Throw](#expect_does_not_throw)
    6. [Expect Throws With Message](#expect_throws_msg)
13. [Isolation Tests](#isolation-tests)
    1. [Types of Execution Statuses](#types-of-execution-statuses)
    2. [Types of Crash Types](#types-of-crash-types)
    3. [Assert Death](#assert_death)
    4. [Assert Segmentation Fault](#assert_segfault)
    5. [Assert Abort](#assert_abort)
    6. [Assert Fatal](#assert_fatal)
    7. [Assert Nonfatal](#assert_nonfatal)
    8. [Assert Success](#assert_success)
    9. [Assert Failure](#assert_failure)
    10. [Assert Nonzero Exit](#assert_nonzero_exit)
    11. [Assert Exit Code](#assert_exitcode)
    12. [Assert Completes](#assert_completes)
    13. [Assert stdout Contains](#assert_stdout_contains)
    14. [Assert stderr Contains](#assert_stderr_contains)
    15. [Assert No stdout](#assert_no_stdout)
    16. [Assert No stderr](#assert_no_stderr)
    17. [Assert stdout Matches](#assert_stdout_matches)
    18. [Assert stderr Matches](#assert_stderr_matches)
    19. [Assert Address Sanitizer Failure](#assert_asan_failure)
    20. [Assert No Address Sanitizer Failure](#assert_nasan_failure)
    21. [Assert Undefined-Behavior Sanitizer Failure](#assert_ubsan_failure)
    22. [Assert No Undefined-Behavior Sanitizer Failure](#assert_nubsan_failure)
    23. [Assert Thread Sanitizer Failure](#assert_tsan_failure)
    24. [Assert No Thread Sanitizer Failure](#assert_ntsan_failure)
    25. [Assert Leak Sanitizer Failure](#assert_lsan_failure)
    26. [Assert No Leak Sanitizer Failure](#assert_nlsan_failure)
    27. [Assert Sanitizer Failure](#assert_san_failure)
    28. [Assert No Sanitizer Failure](#assert_nsan_failure)
    29. [Assert Timeout](#assert_timeout)
    30. [Assert Completes Within](#assert_completes_within)
    31. [Assert Execution Status](#assert_status)
    32. [Assert Crash Type](#assert_crash_type)
    33. [Assert Signal](#assert_signal)
    34. [Assert Killed](#assert_killed)
    35. [Expect Death](#expect_death)
    36. [Expect Segmentation Fault](#expect_segfault)
    37. [Expect Abort](#expect_abort)
    38. [Expect Fatal](#expect_fatal)
    39. [Expect Nonfatal](#expect_nonfatal)
    40. [Expect Success](#expect_success)
    41. [Expect Failure](#expect_failure)
    42. [Expect Nonzero Exit](#expect_nonzero_exit)
    43. [Expect Exit Code](#expect_exitcode)
    44. [Expect Completes](#expect_completes)
    45. [Expect stdout Contains](#expect_stdout_contains)
    46. [Expect stderr Contains](#expect_stderr_contains)
    47. [Expect No stdout](#expect_no_stdout)
    48. [Expect No stderr](#expect_no_stderr)
    49. [Expect stdout Matches](#expect_stdout_matches)
    50. [Expect stderr Matches](#expect_stderr_matches)
    51. [Expect Address Sanitizer Failure](#expect_asan_failure)
    52. [Expect No Address Sanitizer Failure](#expect_nasan_failure)
    53. [Expect Undefined-Behavior Sanitizer Failure](#expect_ubsan_failure)
    54. [Expect No Undefined-Behavior Sanitizer Failure](#expect_nubsan_failure)
    55. [Expect Thread Sanitizer Failure](#expect_tsan_failure)
    56. [Expect No Thread Sanitizer Failure](#expect_ntsan_failure)
    57. [Expect Leak Sanitizer Failure](#expect_lsan_failure)
    58. [Expect No Leak Sanitizer Failure](#expect_nlsan_failure)
    59. [Expect Sanitizer Failure](#expect_san_failure)
    60. [Expect No Sanitizer Failure](#expect_nsan_failure)
    61. [Expect Timeout](#expect_timeout)
    62. [Expect Completes Within](#expect_completes_within)
    63. [Expect Execution Status](#expect_status)
    64. [Expect Crash Type](#expect_crash_type)
    65. [Expect Signal](#expect_signal)
    66. [Expect Killed](#expect_killed)

## Adding To Your Projects

### Installing
If you want to use this as a standalone library, see [Compiling And Linking](#compiling-and-linking). In order to install, be inside the V20.1.3 folder and run these commands:

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
sudo cmake --install build
```

This will install Test++ as a command line command you can use directly in the terminal. It has 3 ways to call it:

```
testpp
```

This command will run the last build made by Test++. If there is none, then it will say that there is nothing to run.

```
testpp (files)
```

This command will compile and run the passed in files. These files will be compiled by C++20 standards, so they must be compatible to be compiled with those standards. 

```
testpp (directories)
```

This command will compile and run the passed in directories. These files will be compiled by C++20 standards, so they must be compatible to be compiled with those standards. Only .cpp files will be compiled.

The `testpp` command can also be passed in the same kind of flags as if it were an executable.

### Compiling And Linking
In order to add to your projects, you need the libtester.a library file. As a static library, it will need to be linked to in the compilation phase. A minimum working directory to compile and link the library is as follows: <br> 
Root/ <br> 
&emsp;include/ <br>
&emsp;&emsp;tester/ <br> 
&emsp;libtester.a <br> 
&emsp;Main.cpp <br> 
With this, the compile command would be: <br> 
`g++ -std=c++20 -Wall -Wextra -I./include -c Main.cpp` <br>
`g++ -std=c++20 -Wall -Wextra -I./include Main.o libtester.a -o NAME_OF_EXECUTABLE` <br> 
There are more ways to compile and link, and I expect the general user to have more complicated file systems. 

### Include Inside Your Project
Inside your project, you can include the library like so:
<br>
At the top of your file add:
`#include <testpp/testpp.hpp>`.
<br>
And now you can start testing right away.

### CLI Usage
As of now, the way to use the unit tester is like so:
<br>
`PATH_TO_EXECUTABLE --flags`  
<br>
There are four flags supported: Verbosity, Threads, Skip, and TestOnly. The flags and the flag values can be typed in either lowercase/uppercase/a mix of both

#### Verbosity
To add a verbosity flag, you may type in any of the following (lower vs uppercase doesn't matter):
1. `--v=`
2. `--verbosity=`

The supported verbosity values are:
1. `default`: renders the output in the default manner
2. `minimum`: renders only the status of each test
3. `passonly`/`pass_only`: renders only which tests passed
4. `failonly`/`fail_only`/`failonlyall`/`fail_only_all`: renders only which tests failed with failure messages
5. `failonlymin`/`fail_only_min`: renders only which tests failed and without failure messages (status only).


#### Threads
To specify the number of threads to be used, you may type in any of the following (lower vs uppercase doesn't matter):

1. `--t=`
2. `--threads=`
3. `--num_threads=`

You can type in any integer value to the number of threads, however, you cannot exceed the number of threads from `std::thread::hardware_concurrency()` and you cannot go below 1 thread. The default value for the number of threads is 1 thread. Because you can specify the number of threads you can use, it is important that your tests are thread-safe. Or not. Free will.

#### Timeouts
Timeouts are a great way to ensure that the framework doesn't run forever. To specify how long a timeout should be, you can use the following (lower vs uppercase doesn't matter):
1. `--timeout=`
2. `--timeout_sec=`
3. `--timeout_ms=`

If you don't specify a unit, like in the `--timeout=` case, the resulting unit is in seconds. For good measure, these are the units and their abbreviations:

1. sec = seconds
2. ms = milliseconds

If there is no timeout flag included, the framework will run for as long as it takes for the tests to complete. This means that if you have an infinite loop, deadlock, or unperformant code, the framework won't alert you.

Upon a timeout, the framework aborts and it will tell you which test was being run by each thread.

#### Skipping Tests
In order to skip test suites, you can type in any of the following (lower vs uppercase doesn't matter):

1. `--s=`
2. `--skip=`

In order to specify which test suites to be skipped, you need to type in the test suite's name AS IT IS REGISTERED. To specify multiple suites, you can type in multiple suite names, each separated solely by a comma ','.

By default, excluding this flag will make every test run, unless the [test only](#test-specific) flag is included (with suites attached).

#### Test Specific
In order to test only specific test suites, you can type in any of the following (lower vs uppercase doesn't matter):

1. `--to=`
2. `--t_o=`
3. `--testonly=`
4. `--test_only=`

In order to specify which test suites are to be tested, you need to type in the test suite's name AS IT IS REGISTERED. To specify multiple suites, you can type in multiple suite names, each separated solely by a comma ','.

By default, excluding this flag will make every test be run unless the [skip](#skipping-tests) flag is included (with suites attached).

Notice how skipping tests and specifying tests to be run are basically identical behavior. They are for your own convenience. If you specify a test suite to be skipped and to be tested: `--skip=Suite --test_only=Suite`, then the suite will still be skipped. 

#### Streaming Output
If you are running lots of tests that will take some (noticeable) time to complete, it can be helpful to stream a status report
instead of waiting for the run summary to print out at the end. For this purpose, you can use the following flag:
`--stream`.

This flag when used will print out a status report of each test including their number, start/end/skip status, their suite name, and their test name. Some sample output when using this below:

```
[3/145][STARTED]: boolean_torture -> literal_true_passes
[4/145][STARTED]: boolean_torture -> literal_false_fails
[3/145][ENDED]: boolean_torture -> literal_true_passes
[5/145][STARTED]: boolean_torture -> false_passes_expect_false
[1/145][STARTED]: timeout -> fail
...
[141/145][ENDED]: String -> Equality
[138/145][STARTED]: null -> Torture_Optional_Basic
[138/145][ENDED]: null -> Torture_Optional_Basic
[1/145][ENDED]: timeout -> fail
...
--------------------------------------------------
Ran 145 tests...

[PASS] FloatBasic -> AbsoluteEquality (0 ms)
[PASS] FloatBasic -> RelativeEquality (0 ms)
...
[PASS] null -> Torture_WeirdCases (0 ms)
[PASS] timeout -> fail (10005 ms)
--------------------------------------------------
Total: 145 | Passed: 145 | Failed: 0 | Skipped: 0
Time: 10006 ms
```

Streaming only streams console output, and therefore is completely compatible with outputting JSON or XML (it has no impact on the resulting JSON or XML output).

#### JSON Output
In order to have JSON output of a test run, type in the following flag:
`--json PATH_TO_FILE`. 

When you stream JSON output to an external file, no output will be rendered in the console.

Some examples of JSON output on each verbosity flag:
`--verbosity=default`:

```
{
	"suites": [
		{
			"suite_name": "Default",
			"tests": [
				{
					"suiteName": "Default",
					"testName": "1",
					"status": "Passed",
					"durationMs": "0",
					"failures": [
						
					]
				},
                {
					"suiteName": "Default",
					"testName": "fail2",
					"status": "Failed",
					"durationMs": "0",
					"failures": [
						{
							"message": "Expected: true to be false",
							"file": "tests/failingTests.cpp",
							"line": "32"
						}
					]
				}
            ]
        }
    ]
}
```

On this level of verbosity, every detail gets streamed.

`--verbosity=minimum`:

```
{
	"suites": [
		{
			"suite_name": "Default",
			"tests": [
				{
					"suiteName": "Default",
					"testName": "1",
					"status": "Passed",
					"durationMs": "0",
					"failures": []
				},
				{
					"suiteName": "Default",
					"testName": "fail1",
					"status": "Failed",
					"durationMs": "0",
					"failures": []
				},
            ]
        }
    ]
}
```

On this level of verbosity, none of the failure messages are recorded.

`--verbosity=passOnly`:

```
{
	"suites": [
		{
			"suite_name": "Default",
			"tests": [
				{
					"suiteName": "Default",
					"testName": "1",
					"status": "Passed",
					"durationMs": "0",
					"failures": []
				}
			]
		},
		{
			"suite_name": "FloatBasic",
			"tests": [
				{
					"suiteName": "FloatBasic",
					"testName": "AbsoluteEquality",
					"status": "Passed",
					"durationMs": "0",
					"failures": []
				}
            ]
        }
    ]
}
```

On this level, only the suites and tests that pass will be rendered. If a suite has no passing test cases, it will not be rendered in the output.

`--verbosity=failOnly`:

```
{
	"suites": [
		{
			"suite_name": "Default",
			"tests": [
				{
					"suiteName": "Default",
					"testName": "fail1",
					"status": "Failed",
					"durationMs": "0",
					"failures": [
						{
							"message": "Expected: true to be false",
							"file": "tests/failingTests.cpp",
							"line": "4"
						}
                        ...
                    ]
                }
            ]
        }
    ]
}
```

On this level, only suites and tests that fail are rendered, with all failure messages. Suites that have no failures are not rendered in the output.

`--verbosity=failOnlyMin`:

```
{
	"suites": [
		{
			"suite_name": "Default",
			"tests": [
				{
					"suiteName": "Default",
					"testName": "fail1",
					"status": "Failed",
					"durationMs": "0",
					"failures": []
				},
				{
					"suiteName": "Default",
					"testName": "fail2",
					"status": "Failed",
					"durationMs": "0",
					"failures": []
				},
                ...
            ]
        }
    ]
}
```

On this level, only suites and tests that fail are rendered, without failure messages. Suites that have no failures are not rendered in the output.

Note that you can combine to have JSON and XML output by adding both flags

#### XML Output
In order to have XML output of a test run, type in the one of the following flags:
1. `--junit PATH_TO_FILE`
2. `--xml PATH_TO_FILE`

When you stream XML output to an external file, no output will be rendered in the console.

Some examples of XML output on each verbosity flag:
`--verbosity=default`:

```
<testsuites>
	<testsuite name="Default" tests="6" successes="1" failures="5" skips="0">
		<testcase name="1" status="passed"/>
		<testcase name="fail1" status="failed">
			<failure message="Expected: true to be false"/>
			<failure message="Expected: 1 to be false"/>
			<failure message="Expected: false to be true"/>
			<failure message="Expected test: EXPECT_TRUE(true) to fail, but it passed"/>
		</testcase>
		<testcase name="fail2" status="failed">
			<failure message="Expected: true to be false"/>
			<failure message="Expected: 1 to be false"/>
			<failure message="Expected: false to be true"/>
			<failure message="Expected test: EXPECT_TRUE(true) to fail, but it passed"/>
		</testcase>
    </testsuite>
</testsuites>
```

On this level of verbosity, every detail gets streamed.

`--verbosity=minimum`:

```
<testsuites>
	<testsuite name="Default" tests="6" successes="1" failures="5" skips="0">
		<testcase name="1" status="passed"/>
		<testcase name="fail1" status="failed"/>
		<testcase name="fail2" status="failed"/>
		<testcase name="fail3" status="failed"/>
		<testcase name="fail4" status="failed"/>
		<testcase name="fail5" status="failed"/>
	</testsuite>
	<testsuite name="FloatBasic" tests="3" successes="3" failures="0" skips="0">
		<testcase name="AbsoluteEquality" status="passed"/>
		<testcase name="RelativeEquality" status="passed"/>
		<testcase name="CombinedNear" status="passed"/>
	</testsuite>
    ...
</testsuites>
```

On this level of verbosity, none of the failure messages are recorded.

`--verbosity=passOnly`:

```
<testsuites>
	<testsuite name="Default" tests="6" successes="1" failures="5" skips="0">
		<testcase name="1" status="passed"/>
	</testsuite>
	<testsuite name="FloatBasic" tests="3" successes="3" failures="0" skips="0">
		<testcase name="AbsoluteEquality" status="passed"/>
		<testcase name="RelativeEquality" status="passed"/>
		<testcase name="CombinedNear" status="passed"/>
	</testsuite>
    ...
</testsuites>
```

On this level, only the suites and tests that pass will be rendered. If a suite has no passing test cases, it will not be rendered in the output.

`--verbosity=failOnly`:

```
<testsuites>
	<testsuite name="Default" tests="5" successes="0" failures="5" skips="0">
		<testcase name="fail1" status="failed">
			<failure message="Expected: true to be false"/>
			<failure message="Expected: 1 to be false"/>
			<failure message="Expected: false to be true"/>
			<failure message="Expected test: EXPECT_TRUE(true) to fail, but it passed"/>
		</testcase>
		<testcase name="fail2" status="failed">
			<failure message="Expected: true to be false"/>
			<failure message="Expected: 1 to be false"/>
			<failure message="Expected: false to be true"/>
			<failure message="Expected test: EXPECT_TRUE(true) to fail, but it passed"/>
		</testcase>
        ...
    </testsuite>
</testsuites>
```

On this level, only suites and tests that fail are rendered, with all failure messages. Suites that have no failures are not rendered in the output.

`--verbosity=failOnlyMin`:

```
<testsuites>
	<testsuite name="Default" tests="6" successes="1" failures="5" skips="0">
		<testcase name="fail1" status="failed"/>
		<testcase name="fail2" status="failed"/>
		<testcase name="fail3" status="failed"/>
		<testcase name="fail4" status="failed"/>
		<testcase name="fail5" status="failed"/>
	</testsuite>
</testsuites>
```

Note that you can combine to have JSON and XML output by adding both flags

#### stdout/stderr Output
To specify what length you want to capture stdout and stderr output from [Isolation Tests](#isolation-tests) use the following flags:

1. `--truncatestdout=`
2. `--truncstdout=`
3. `--truncatestderr=`
4. `--truncstderr=`
5. `--truncate=`

Following by a nonnegative integer. Inputting a value of `0` reverts to the default behavior of printing out the full subprocess's `stdout` and `stderr` output. `--truncate=` truncates both `stdout` and `stderr` output to the same length. Truncating does not affect JSON and XML output and when printing JSON and/or XML, the FULL `stdout` and `stderr` output will be recorded. This flag ONLY affects CONSOLE rendering.

## Testing

### Registering Tests
In order to register a test, there are two options: `TEST(suite_name, test_name)` or `D_TEST(test_name)`. Providing a suite_name is a great way to sort tests instead of having them all in random order. Suite names must be unique, and test names must be unique within a suite.

Some usage examples below:
```
#include <testpp/testpp.hpp>

//No main() is required

D_TEST(name) { //Notice name has no quotes inside the macro
    ...
    NAME_OF_TEST(parameters...);
}
```

```
#include <testpp/testpp.hpp>

//No main() is required

TEST(suite_name, test_name) { //Notice neither name have quotes
    ...
    NAME_OF_TEST(parameters...);
}
```

An example of an disallowed naming:

```
#include <testpp/testpp.hpp>

D_TEST(not_unique_name) {
    ...
    NAME_OF_TEST(parameters...);
}

D_TEST(not_unique_name) {
    ...
    NAME_OF_ANOTHER_TEST(parameters...);
}
```
In the above example, compilation will fail because the test is defined twice. One more example with TEST() to drive it home:

```
#include <testpp/testpp.hpp>

TEST(suite_name, not_unique_name) {
    ...
    NAME_OF_TEST(parameters...);
}

//Totally fine because it's registered under a different test suite

TEST(another_suite_name, not_unique_name) {
    ...
    NAME_OF_ANOTHER_TEST(parameters...);
}

//Not fine because this test is defined twice under the same suite

TEST(another_suite_name, not_unique_name) {
    ...
    NAME_OF_ANOTHER_TEST(parameters...);
}
```

### Different Types of Tests
There are two types of tests supported: Expects and Asserts. Expects tests will always run to fruition no matter what (failure or throws), but Asserts tests will stop testing the current test function upon failure.

```
TEST(expect_example, name) {
    ...
    EXPECT_SOMETHING(); //suppose this fails
    EXPECT_ANOTHER(); //this one still runs
    ...
}
```

```
TEST(assert_example, name) {
    ...
    ASSERT_SOMETHING(); //suppose this fails
    ASSERT_ANOTHER(); //this one (and everything after) WONT RUN
    ...
}

//this test function will still run even though
//  a failing assert happened in the same suite
TEST(assert_example, another_test) {
    ...
    ASSERT_SOMETHING();
    ASSERT_ANOTHER(); 
    ...
}
```

## Boolean Tests
Boolean tests are used to check the truthiness of a value/condition.

1. [Assert True](#assert_true)
2. [Assert False](#assert_false)
3. [Expect True](#expect_true)
4. [Expect False](#expect_false)

### ASSERT_TRUE()
`ASSERT_TRUE(cond)` takes in a single parameter which is a condition that evaluates to a boolean value. It passes iff the condition evaluates to `true` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>

D_TEST(assert_true) {
    ASSERT_TRUE(true); //passes
    ASSERT_TRUE(5 != 10); //passes
    ASSERT_TRUE(1 == 2); //fails
    ASSERT_TRUE("cool" == "nice"); //doesn't get run
}
```

### ASSERT_FALSE()
`ASSERT_FALSE(cond)` takes in a single parameter which is a condition that evaluates to a boolean value. It passes iff the condition evaluates to `false` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>

D_TEST(assert_false) {
    ASSERT_FALSE(false); //passes
    ASSERT_FALSE(5 == 10); //passes
    ASSERT_FALSE(1 != 2); //fails
    ASSERT_FALSE("cool" == "nice"); //doesn't get run
}
```

### EXPECT_TRUE()
`EXPECT_TRUE(cond)` takes in a single parameter which is a condition that evaluates to a boolean value. It passes iff the condition evaluates to `true` and fails otherwise.

```
#include <testpp/testpp.hpp>

D_TEST(expect_true) {
    EXPECT_TRUE(true); //passes
    EXPECT_TRUE(5 != 10); //passes
    EXPECT_TRUE(1 == 2); //fails
    EXPECT_TRUE("cool" == "nice"); //runs and fails
}
```

### EXPECT_FALSE()
`EXPECT_FALSE(cond)` takes in a single parameter which is a condition that evaluates to a boolean value. It passes iff the condition evaluates to `false` and fails otherwise.

```
#include <testpp/testpp.hpp>

D_TEST(expect_false) {
    EXPECT_FALSE(false); //passes
    EXPECT_FALSE(5 == 10); //passes
    EXPECT_FALSE(1 != 2); //fails
    EXPECT_FALSE("cool" == "nice"); //runs and passes
}
```

## Comparison Tests
Comparison tests are used to compare the relation between two different values. These tests can fail if you mixed signed vs unsigned types due to implicit conversions done by C++. If you think that's a bug that should be fixed, let me know so I can update the framework.

1. [Assert Equals](#assert_eq)
2. [Assert Not Equals](#assert_ne)
3. [Assert Less Than](#assert_lt)
4. [Assert Less Than or Equals](#assert_le)
5. [Assert Greater Than](#assert_gt)
6. [Assert Greater Than or Equals](#assert_ge)
7. [Expect Equals](#expect_eq)
8. [Expect Not Equals](#expect_ne)
9. [Expect Less Than](#expect_lt)
10. [Expect Less Than or Equals](#expect_le)
11. [Expect Greater Than](#expect_gt)
12. [Expect Greater Than or Equals](#expect_ge)

### ASSERT_EQ()
`ASSERT_EQ(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `==` operator. It passes iff `a == b` is `true` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>
#include <vector>

D_TEST(assert_equals) {
    ASSERT_EQ(5, 5); //passes
    std::vector<int> numbers = {1, 2, 3};
    std::vector<int>& ref = numbers;
    ASSERT_EQ(ref, numbers); //passes
    ASSERT_EQ(numbers, ref);
}
```

### ASSERT_NE()
`ASSERT_NE(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `!=` operator. If the `!=` operator is not defined between the two parameters, it will fall back on using `==` for comparison. In the case that `!=` is defined on `a` and `b`, the test will pass iff `a != b` is `true` and fails otherwise. In the case that `!=` is not defined on `a` and `b`, the test will pass iff `!(a == b)` is `true` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>
#include <vector>

D_TEST(assert_not_equals) {
    ASSERT_NE(10, 5); //passes
    std::vector<int> numbers = {1, 2, 3};
    std::vector<int>& ref = numbers;
    ASSERT_NE(ref, numbers); //fails
    ASSERT_NE(numbers, ref); //doesn't run
}
```

### ASSERT_LT()
`ASSERT_LT(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `<` operator. It passes iff `a < b` is `true` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>

D_TEST(assert_less_than) {
    ASSERT_LT(-1, 5); //passes
    ASSERT_LT(-5.00, 0); //passes
}
```

### ASSERT_LE()
`ASSERT_LE(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `<=` operator. It passes iff `a <= b` is `true` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>

D_TEST(assert_less_than_equals) {
    ASSERT_LE(-1, 5); //passes
    ASSERT_LE(5, 5); //passes
    ASSERT_LE(1, 0); //fails
}
```

### ASSERT_GT()
`ASSERT_GT(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `>` operator. It passes iff `a > b` is `true` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>

D_TEST(assert_greater_than) {
    ASSERT_GT(0x105, 5); //passes
    ASSERT_GT(-5.00, 0); //fails
}
```

### ASSERT_GE()
`ASSERT_GE(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `>=` operator. It passes iff `a >= b` is `true` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>

D_TEST(assert_greater_than_equals) {
    ASSERT_GE(0x105, 5); //passes
    ASSERT_GE(0x105, 0x104); //passes
}
```

### EXPECT_EQ()
`EXPECT_EQ(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `==` operator. It passes iff `a == b` is `true` and fails otherwise.

```
#include <testpp/testpp.hpp>
#include <vector>

D_TEST(assert_equals) {
    EXPECT_EQ(5, 5); //passes
    std::vector<int> numbers = {1, 2, 3};
    std::vector<int>& ref = numbers;
    EXPECT_EQ(ref, numbers); //passes
    EXPECT_EQ(numbers, ref);
}
```

### EXPECT_NE()
`EXPECT_NE(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `!=` operator. If the `!=` operator is not defined between the two parameters, it will fall back on using `==` for comparison. In the case that `!=` is defined on `a` and `b`, the test will pass iff `a != b` is `true` and fails otherwise. In the case that `!=` is not defined on `a` and `b`, the test will pass iff `!(a == b)` is `true` and fails otherwise.

```
#include <testpp/testpp.hpp>
#include <vector>

D_TEST(assert_not_equals) {
    EXPECT_NE(10, 5); //passes
    std::vector<int> numbers = {1, 2, 3};
    std::vector<int>& ref = numbers;
    EXPECT_NE(ref, numbers); //fails
    EXPECT_NE(numbers, ref); //runs and fails
}
```

### EXPECT_LT()
`EXPECT_LT(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `<` operator. It passes iff `a < b` is `true` and fails otherwise.

```
#include <testpp/testpp.hpp>

D_TEST(assert_less_than) {
    EXPECT_LT(-1, 5); //passes
    EXPECT_LT(-5.00, 0); //passes
}
```

### EXPECT_LE()
`EXPECT_LE(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `<=` operator. It passes iff `a <= b` is `true` and fails otherwise.
```
#include <testpp/testpp.hpp>

D_TEST(assert_less_than_equals) {
    EXPECT_LE(-1, 5); //passes
    EXPECT_LE(5, 5); //passes
    EXPECT_LE(1, 0); //fails
}
```

### EXPECT_GT()
`EXPECT_GT(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `>` operator. It passes iff `a > b` is `true` and fails otherwise.

```
#include <testpp/testpp.hpp>

D_TEST(assert_greater_than) {
    EXPECT_GT(0x105, 5); //passes
    EXPECT_GT(-5.00, 0); //fails
}
```

### EXPECT_GE()
`EXPECT_GE(a, b)` takes in two parameters, `a` and `b`, and compares as defined by the `<=` operator. It passes iff `a <= b` is `true` and fails otherwise.
```
#include <testpp/testpp.hpp>

D_TEST(assert_greater_than_equals) {
    EXPECT_GE(0x105, 5); //passes
    EXPECT_GE(0x105, 0x104); //passes
}
```

## Float Tests
Float tests are used to check something about a float, generally absolute/relative tolerance. These can also be used to check for `NaN`. Each test can take in any combination of floating point types. Ie, for tests that take in multiple floating point values, it's possible to mix the type parameters (eg. pass in a `float` and `double`). In this case, they are cast to the common floating point type and these commonly cast versions are used in the tests.

1. [Assert Near](#assert_near)
2. [Assert Absolutely Near](#assert_abs_near)
3. [Assert Relatively Near](#assert_rel_near)
4. [Assert NaN](#assert_nan)
5. [Assert Not NaN](#assert_not_nan)
6. [Assert Infinity](#assert_inf)
7. [Assert Positive Infinity](#assert_pos_inf)
8. [Assert Negative Infinity](#assert_neg_inf)
9. [Expect Near](#expect_near)
10. [Expect Absolutely Near](#expect_abs_near)
11. [Expect Relatively Near](#expect_rel_near)
12. [Expect NaN](#expect_nan)
13. [Expect Not NaN](#expect_not_nan)
14. [Expect Infinity](#expect_inf)
15. [Expect Positive Infinity](#expect_pos_inf)
16. [Expect Negative Infinity](#expect_neg_inf)

### ASSERT_NEAR()
`ASSERT_NEAR(a, b, abs_tol, rel_tol)` takes in up to four arguments. `a` and `b` are two floating point values of any two floating point types. `abs_tol` is the absolute tolerance that should be between `a` and `b`. `rel_tol` is an optional parameter that defines how relatively near `a` and `b` should be.

In the case that `rel_tol` is not provided, this test becomes the same as [Assert Absolutely Near](#assert_abs_near). 

In the case that `rel_tol` is provided, this test passes iff `|a - b| <= max(|abs_tol|, |rel_tol| * max(|a|, |b|))`. That is, the absolute difference of `a` and `b` must be smaller than the larger of the absolute value of `abs_tol` and the product of the absolute value of `rel_tol` and the larger of `|a|` and `|b|`. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>

TEST(assert_near, three_param) {
    float a = 5.0;
    double b = 6.0;
    long double abs_tol = 0.01;

    ASSERT_NEAR(a, b, abs_tol); //fails
}

TEST(assert_near, four_param) {
    float a = 5.0;
    double b = 6.0;
    long double abs_tol = 0.01;
    long double rel_tol_pass = 0.5;
    long double rel_tol_fail = 0.05;

    ASSERT_NEAR(a, b, abs_tol, rel_tol_pass); //passes
    ASSERT_NEAR(a, b, abs_tol, rel_tol_fail); //fails
}
```

### ASSERT_ABS_NEAR()
`ASSERT_ABS_NEAR(a, b, abs_tol)` takes in three arguments. `a` and `b` are two floating point values of an two floating point types. `abs_tol` defines the maximum difference `a` and `b` can be from each other. This test passes iff `|a - b| <= |abs_tol|`. That is, the absolute difference of `a` and `b` must be smaller than the absolute value of `abs_tol`. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>

D_TEST(assert_abs_near) {
    float a = 5.0;
    double b = 6.0;
    long double abs_tol = 2.0;

    ASSERT_ABS_NEAR(a, b, abs_tol); //passes

    long double abs_tol_two = 0.5;
    ASSERT_ABS_NEAR(a, b, abs_tol_two); //fails because |a - b| > 0.5
}
```

### ASSERT_REL_NEAR()
`ASSERT_REL_NEAR(a, b, rel_tol)` takes in three arguments. `a` and `b` are two floating point values of an two floating point types. `rel_tol` defines how relatively near `a` and `b` should be. This test passes iff `|a - b| <= |rel_tol| * max(|a|, |b|)`. That is, the absolute difference of `a` and `b` must be smaller than the product of `rel_tol` and the larger of `|a|` and `|b|`. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>

D_TEST(assert_rel_near) {
    float a = 5.0;
    double b = 6.0;
    long double rel_tol = 0.5;

    ASSERT_REL_NEAR(a, b, rel_tol); //passes

    long double rel_tol_two = 0.1;
    ASSERT_REL_NEAR(a, b, rel_tol_two); //fails because 0.1 * 0.6 = 0.06 < |a - b|
}
```

### ASSERT_NAN()
`ASSERT_NAN(a)` takes in one parameter, `a`, which is a floating point value. It passes iff `a` is equivalent to `NAN` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>

D_TEST(assert_nan) {
    float a = 5.0;

    ASSERT_NAN(a); //fails
}
```

### ASSERT_NOT_NAN()
`ASSERT_NOT_NAN(a)` takes in one parameter, `a`, which is a floating point value. It passes iff `a` is not equivalent to `NAN` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>

D_TEST(assert_nan) {
    float a = 5.0;

    ASSERT_NOT_NAN(a); //passes
}
```

### ASSERT_INF()
`ASSERT_INF(number)` takes in one parameter, a floating point value. If passes iff `number` is positive infinity or negative infinity and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>

D_TEST(assert_int) {
    float a = 5.0;

    ASSERT_INF(a); //fails

    double b = std::numeric_limits<double>::infinity();

    ASSERT_INF(b); //passes

    float c = -std::numeric_limits<double>::infinity();

    ASSERT_INF(c); //passes
}
```

### ASSERT_POS_INF()
`ASSERT_POS_INF(number)` takes in one parameter, a floating point value. If passes iff `number` is positive infinity and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>

D_TEST(assert_pos_int) {
    float a = 5.0;

    ASSERT_POS_INF(a); //fails

    double b = std::numeric_limits<double>::infinity();

    ASSERT_POS_INF(b); //passes

    float c = -std::numeric_limits<double>::infinity();

    ASSERT_POS_INF(c); //fails
}
```

### ASSERT_NEG_INF()
`ASSERT_NEG_INF(number)` takes in one parameter, a floating point value. If passes iff `number` is negative infinity and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>

D_TEST(assert_neg_int) {
    float a = 5.0;

    ASSERT_NEG_INF(a); //fails

    double b = std::numeric_limits<double>::infinity();

    ASSERT_NEG_INF(b); //fails

    float c = -std::numeric_limits<double>::infinity();

    ASSERT_NEG_INF(c); //passes
}
```

### EXPECT_NEAR()
`EXPECT_NEAR(a, b, abs_tol, rel_tol)` takes in up to four arguments. `a` and `b` are two floating point values of any two floating point types. `abs_tol` is the absolute tolerance that should be between `a` and `b`. `rel_tol` is an optional parameter that defines how relatively near `a` and `b` should be.

In the case that `rel_tol` is not provided, this test becomes the same as [Expect Absolutely Near](#expect_abs_near). 

In the case that `rel_tol` is provided, this test passes iff `|a - b| <= max(|abs_tol|, |rel_tol| * max(|a|, |b|))`. That is, the absolute difference of `a` and `b` must be smaller than the larger of the absolute value of `abs_tol` and the product of the absolute value of `rel_tol` and the larger of `|a|` and `|b|`.

```
#include <testpp/testpp.hpp>

TEST(expect_near, three_param) {
    float a = 5.0;
    double b = 6.0;
    long double abs_tol = 0.01;

    EXPECT_NEAR(a, b, abs_tol); //fails
}

TEST(expect_near, four_param) {
    float a = 5.0;
    double b = 6.0;
    long double abs_tol = 0.01;
    long double rel_tol_pass = 0.5;
    long double rel_tol_fail = 0.05;

    EXPECT_NEAR(a, b, abs_tol, rel_tol_pass); //passes
    EXPECT_NEAR(a, b, abs_tol, rel_tol_fail); //fails
}
```

### EXPECT_ABS_NEAR()
`EXPECT_ABS_NEAR(a, b, abs_tol)` takes in three arguments. `a` and `b` are two floating point values of an two floating point types. `abs_tol` defines the maximum difference `a` and `b` can be from each other. This test passes iff `|a - b| <= |abs_tol|`. That is, the absolute difference of `a` and `b` must be smaller than the absolute value of `abs_tol`.

```
#include <testpp/testpp.hpp>

D_TEST(expect_abs_near) {
    float a = 5.0;
    double b = 6.0;
    long double abs_tol = 2.0;

    EXPECT_ABS_NEAR(a, b, abs_tol); //passes

    long double abs_tol_two = 0.5;
    EXPECT_ABS_NEAR(a, b, abs_tol_two); //fails because |a - b| > 0.5
}
```

### EXPECT_REL_NEAR()
`EXPECT_REL_NEAR(a, b, rel_tol)` takes in three arguments. `a` and `b` are two floating point values of an two floating point types. `rel_tol` defines how relatively near `a` and `b` should be. This test passes iff `|a - b| <= |rel_tol| * max(|a|, |b|)`. That is, the absolute difference of `a` and `b` must be smaller than the product of `rel_tol` and the larger of `|a|` and `|b|`.

```
#include <testpp/testpp.hpp>

D_TEST(expect_rel_near) {
    float a = 5.0;
    double b = 6.0;
    long double rel_tol = 0.5;

    EXPECT_REL_NEAR(a, b, rel_tol); //passes

    long double rel_tol_two = 0.1;
    EXPECT_REL_NEAR(a, b, rel_tol_two); //fails because 0.1 * 0.6 = 0.06 < |a - b|
}
```

### EXPECT_NAN()
`EXPECT_NAN(a)` takes in one parameter, `a`, which is a floating point value. It passes iff `a` is equivalent to `NAN` and fails otherwise.

```
#include <testpp/testpp.hpp>

D_TEST(expect_nan) {
    float a = 5.0;

    EXPECT_NAN(a); //fails
}
```

### EXPECT_NOT_NAN()
`ASSERT_NOT_NAN(a)` takes in one parameter, `a`, which is a floating point value. It passes iff `a` is not equivalent to `NAN` and fails otherwise.

```
#include <testpp/testpp.hpp>

D_TEST(expect_nan) {
    float a = 5.0;

    EXPECT_NOT_NAN(a); //passes
}
```

### EXPECT_INF()
`EXPECT_INF(number)` takes in one parameter, a floating point value. If passes iff `number` is positive infinity or negative infinity and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>

D_TEST(expect_int) {
    float a = 5.0;

    EXPECT_INF(a); //fails

    double b = std::numeric_limits<double>::infinity();

    EXPECT_INF(b); //passes

    float c = -std::numeric_limits<double>::infinity();

    EXPECT_INF(c); //passes
}
```

### EXPECT_POS_INF()
`EXPECT_POS_INF(number)` takes in one parameter, a floating point value. If passes iff `number` is positive infinity and fails otherwise.

```
#include <testpp/testpp.hpp>

D_TEST(expect_pos_int) {
    float a = 5.0;

    EXPECT_POS_INF(a); //fails

    double b = std::numeric_limits<double>::infinity();

    EXPECT_POS_INF(b); //passes

    float c = -std::numeric_limits<double>::infinity();

    EXPECT_POS_INF(c); //fails
}
```

### EXPECT_NEG_INF()
`EXPECT_NEG_INF(number)` takes in one parameter, a floating point value. If passes iff `number` is negative infinity and fails otherwise.

```
#include <testpp/testpp.hpp>

D_TEST(expect_neg_int) {
    float a = 5.0;

    EXPECT_NEG_INF(a); //fails

    double b = std::numeric_limits<double>::infinity();

    EXPECT_NEG_INF(b); //fails

    float c = -std::numeric_limits<double>::infinity();

    EXPECT_NEG_INF(c); //passes
}
```

## Iterable Tests
Iterable tests are used for iterable containers, such as arrays, maps, sets, etc. They require that whatever types are within the containers to have `==` defined. Items in the passed in containers don't necessarily need to be the same type.

In order to be an iterable container, the passed in container needs to satisfy the `std::ranges::range` concept.

1. [Assert Ordered Equals](#assert_ordered_eq)
2. [Assert Unordered Equals](#assert_unordered_eq)
3. [Assert Ordered Not Equals](#assert_ordered_ne)
4. [Assert Unordered Not Equals](#assert_unordered_ne)
5. [Assert Empty](#assert_empty)
6. [Assert Not Empty](#assert_nempty)
7. [Assert Size](#assert_size)
8. [Assert Contains](#assert_contains)
9. [Assert Does Not Contain](#assert_does_not_contain)
10. [Expect Ordered Equals](#expect_ordered_eq)
11. [Expect Unordered Equals](#expect_unordered_eq)
12. [Expect Ordered Not Equals](#expect_ordered_ne)
13. [Expect Unordered Not Equals](#expect_unordered_ne)
14. [Expect Empty](#expect_empty)
15. [Expect Not Empty](#expect_nempty)
16. [Expect Size](#expect_size)
17. [Expect Contains](#expect_contains)
18. [Expect Does Not Contain](#expect_does_not_contain)

### ASSERT_ORDERED_EQ
`EXPECT_ORDERED_EQ(first, second)` takes in two arguments: two iterable containers. The two containers do not necessarily have to be the same type. However, you are responsible for passing in the correct container types into the function. Ie, passing in unordered containers such as `unordered_map` and `unordered_set` are not guaranteed to work properly. This test passes iff every element in each container are `==` at the same index, and fails otherwise. This test will also automatically fail when given two containers with different item counts. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <set>
#include <unordered_set>

D_TEST(assert_ordered_eq) {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {1, 2, 3, 4, 5};

    ASSERT_ORDERED_EQ(a, b); //passes

    int c[] = {5, 4, 3, 2, 1};

    ASSERT_ORDERED_EQ(a, c); // fails

    std::vector<int> d = {8, 6, 7, 5, 3, 0, 9};
    int e[] = {8, 6, 7, 5, 3, 0, 9};

    ASSERT_ORDERED_EQ(d, e); //would pass

    std::set<std::vector<int>> f = {{1, 2, 3}, {4, 5, 6}};
    std::set<std::vector<int>> g = {{1, 2, 3}, {4, 5, 6}};

    ASSERT_ORDERED_EQ(f, g); //would pass

    std::unordered_set<int> h = {1, 2, 3, 4, 5, 6};
    std::unordered_set<int> i = {1, 2, 3, 4, 5, 6};

    ASSERT_ORDERED_EQ(h, i); //undefined behavior, but most likely would fail
}
```

### ASSERT_UNORDERED_EQ
`EXPECT_ORDERED_EQ(first, second)` takes in two arguments: two iterable containers. The two containers do not necessarily have to be the same type. However, you are responsible for passing in the correct container types into the function. Ie, passing in unordered containers such as `unordered_map` and `unordered_set` are not guaranteed to work properly. This test passes iff every element in each container are `==` at the same index, and fails otherwise. This test will also automatically fail when given two containers with different item counts. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <set>
#include <unordered_set>

D_TEST(assert_unordered_eq) {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {1, 2, 3, 4, 5};

    ASSERT_UNORDERED_EQ(a, b); //passes

    int c[] = {5, 4, 3, 2, 1};

    ASSERT_UNORDERED_EQ(a, c); // passes

    std::vector<int> d = {8, 6, 7, 5, 3, 0, 9};
    int e[] = {8, 6, 7, 5, 3, 0, 9};

    ASSERT_UNORDERED_EQ(d, e); //passes

    std::set<std::vector<int>> f = {{1, 2, 3}, {4, 5, 6}};
    std::set<std::vector<int>> g = {{1, 2, 3}, {4, 5, 6}};

    ASSERT_UNORDERED_EQ(f, g); //passes

    std::unordered_set<int> h = {1, 2, 3, 4, 5, 6};
    std::unordered_set<int> i = {1, 2, 3, 4, 5, 6};

    ASSERT_UNORDERED_EQ(h, i); //passes, unlike ASSERT_ORDERED_EQ()

    int j[] = {1, 1, 2, 3};
    int k[] = {1, 2, 3, 3};
    ASSERT_UNORDERED_EQ(j, k); //fails because there is a mismatch in counts on 1 and 3
}
```

### ASSERT_ORDERED_NE()
`ASSERT_ORDERED_NE(first, second)` takes in two parameters: two iterable containers that satisfy the `ranges` concept whose elements are capable of being compared by the `==` operator. It passes iff `first` and `second` have at least one element that do not pass a comparison by the `==` operator and fails otherwise. This function should only be called on containers that have some deterministic method of ordering its elements, ie, passing in `unordered` containers yields undefined behavior. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <set>
#include <unordered_set>

D_TEST(assert_ordered_ne) {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {1, 2, 3, 4, 5};

    ASSERT_ORDERED_NE(a, b); //fails

    int c[] = {5, 4, 3, 2, 1};

    ASSERT_ORDERED_NE(a, c); //passes

    std::vector<int> d = {8, 6, 7, 5, 3, 0, 9};
    int e[] = {8, 6, 7, 5, 3, 0, 9};

    ASSERT_ORDERED_NE(d, e); //fails

    std::set<std::vector<int>> f = {{1, 2, 3}, {4, 5, 6}};
    std::set<std::vector<int>> g = {{1, 2, 3}, {4, 5, 6}};

    ASSERT_ORDERED_NE(f, g); //fails

    std::unordered_set<int> h = {1, 2, 3, 4, 5, 6};
    std::unordered_set<int> i = {1, 2, 3, 4, 5, 6};

    ASSERT_ORDERED_NE(h, i); //undefined behavior, but will most likely fail

    int j[] = {1, 1, 2, 3};
    int k[] = {1, 2, 3, 3};
    ASSERT_ORDERED_NE(j, k); //passes because there is a mismatch in counts on 1 and 3
}
```

### ASSERT_UNORDERED_NE()
`ASSERT_UNORDERED_NE(first, second)` takes in two parameters: two iterable containers that satisfy the `ranges` concept whose elements are capable of being compared by the `==` operator. It passes iff `first` and `second` have at least one element that do not pass a comparison by the `==` operator and fails otherwise. Unlike `ASSERT_ORDERED_NE()`, this function can be used on any kind of container, eg. the ones that don't maintain any ordering. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <set>
#include <unordered_set>

D_TEST(assert_unordered_ne) {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {1, 2, 3, 4, 5};

    ASSERT_UNORDERED_NE(a, b); //fails

    int c[] = {5, 4, 3, 2, 1};

    ASSERT_UNORDERED_NE(a, c); //fails

    std::vector<int> d = {8, 6, 7, 5, 3, 0, 9};
    int e[] = {8, 6, 7, 5, 3, 0, 9};

    ASSERT_UNORDERED_NE(d, e); //fails

    std::set<std::vector<int>> f = {{1, 2, 3}, {4, 5, 6}};
    std::set<std::vector<int>> g = {{2, 2, 3}, {4, 5, 6}};

    ASSERT_UNORDERED_NE(f, g); //passes

    std::unordered_set<int> h = {1, 2, 3, 5, 5, 6};
    std::unordered_set<int> i = {1, 2, 3, 4, 5, 6};

    ASSERT_UNORDERED_NE(h, i); //passes

    int j[] = {1, 1, 2, 3};
    int k[] = {1, 2, 3, 3};
    ASSERT_UNORDERED_NE(j, k); //passes
}
```

### ASSERT_EMPTY()
`ASSERT_EMPTY(container)` takes in one parameter, a container with the `size()` method. It passes iff `container.size() == 0` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <set>

D_TEST(assert_empty) {
    std::vector<int> a = {1, 2, 3, 4, 5};
    ASSERT_EMPTY(a); //fails

    std::set<int> b = {};
    ASSERT_EMPTY(b); //passes
}
```

### ASSERT_NEMPTY()
`ASSERT_NEMPTY(container)` takes in one parameter. takes in one parameter, a container with the `size()` method. It passes iff `container.size() != 0` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <set>

D_TEST(assert_nempty) {
    std::vector<int> a = {1, 2, 3, 4, 5};
    ASSERT_NEMPTY(a); //passes

    std::set<int> b = {};
    ASSERT_NEMPTY(b); //fails
}
```

### ASSERT_SIZE()
`ASSERT_SIZE(container, size)` takes in two parameters, takes in one parameter, a container with the `size()` method and a `size_t`. It passes iff `container.size() == size` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <set>

D_TEST(assert_size) {
    std::vector<int> a = {1, 2, 3, 4, 5};
    ASSERT_SIZE(a, 5); //passes

    std::set<int> b = {};
    ASSERT_SIZE(b, 0); //passes

    ASSERT_SIZE(b, 5); //fails
}
```

### ASSERT_CONTAINS()
`ASSERT_CONTAINS(container, value)` takes in two parameters, a `ranges` container and a value to search for. It passes iff `container` contains `value` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <set>

D_TEST(assert_contains) {
    std::vector<int> a = {1, 2, 3, 4, 5};
    ASSERT_CONTAINS(a, 5); //passes

    std::set<int> b = {};
    ASSERT_CONTAINS(b, 11); //fails

    ASSERT_CONTAINS(a, -1); //fails
}
```

### ASSERT_DOES_NOT_CONTAIN()
`ASSERT_DOES_NOT_CONTAIN(container, value)` takes in two parameters, a `ranges` container and a value to search for. It passes iff `container` does not contain `value` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <set>

D_TEST(assert_does_not_contain) {
    std::vector<int> a = {1, 2, 3, 4, 5};
    ASSERT_DOES_NOT_CONTAIN(a, 5); //fails

    std::set<int> b = {};
    ASSERT_DOES_NOT_CONTAIN(b, 11); //passes

    ASSERT_DOES_NOT_CONTAIN(a, -1); //passes
}
```

### EXPECT_ORDERED_EQ()
`EXPECT_ORDERED_EQ(first, second)` takes in two arguments: two iterable containers. The two containers do not necessarily have to be the same type. However, you are responsible for passing in the correct container types into the function. Ie, passing in unordered containers such as `unordered_map` and `unordered_set` are not guaranteed to work properly. This test passes iff every element in each container are `==` at the same index, and fails otherwise. This test will also automatically fail when given two containers with different item counts.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <set>
#include <unordered_set>

D_TEST(expect_ordered_eq) {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {1, 2, 3, 4, 5};

    EXPECT_ORDERED_EQ(a, b); //passes

    int c[] = {5, 4, 3, 2, 1};

    EXPECT_ORDERED_EQ(a, c); // fails

    std::vector<int> d = {8, 6, 7, 5, 3, 0, 9};
    int e[] = {8, 6, 7, 5, 3, 0, 9};

    EXPECT_ORDERED_EQ(d, e); //passes

    std::set<std::vector<int>> f = {{1, 2, 3}, {4, 5, 6}};
    std::set<std::vector<int>> g = {{1, 2, 3}, {4, 5, 6}};

    EXPECT_ORDERED_EQ(f, g); //passes

    std::unordered_set<int> h = {1, 2, 3, 4, 5, 6};
    std::unordered_set<int> i = {1, 2, 3, 4, 5, 6};

    EXPECT_ORDERED_EQ(h, i); //undefined behavior, but most likely to fail
}
```

### EXPECT_UNORDERED_EQ()
`EXPECT_UNORDERED_EQ(first, second)` takes in two arguments: two iterable containers. The two containers do not necessarily have to be the same type. This test can take in any kind of container, ordered or unordered, in fact, when this test is used on ordered containers, its behavior is the same as `EXPECT_ORDERED_EQ()`. This test passes iff both containers have the same elements (as defined by `==`) and the same count of each element, regardless of indexing, and fails otherwise. This test will also automatically fail when given two containers with different item counts.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <set>
#include <unordered_set>

D_TEST(expect_ordered_eq) {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {1, 2, 3, 4, 5};

    EXPECT_UNORDERED_EQ(a, b); //passes

    int c[] = {5, 4, 3, 2, 1};

    EXPECT_UNORDERED_EQ(a, c); // passes

    std::vector<int> d = {8, 6, 7, 5, 3, 0, 9};
    int e[] = {8, 6, 7, 5, 3, 0, 9};

    EXPECT_UNORDERED_EQ(d, e); //passes

    std::set<std::vector<int>> f = {{1, 2, 3}, {4, 5, 6}};
    std::set<std::vector<int>> g = {{1, 2, 3}, {4, 5, 6}};

    EXPECT_UNORDERED_EQ(f, g); //passes

    std::unordered_set<int> h = {1, 2, 3, 4, 5, 6};
    std::unordered_set<int> i = {1, 2, 3, 4, 5, 6};

    EXPECT_UNORDERED_EQ(h, i); //passes, unlike EXPECT_ORDERED_EQ()

    int j[] = {1, 1, 2, 3};
    int k[] = {1, 2, 3, 3};
    EXPECT_UNORDERED_EQ(j, k); //fails because there is a mismatch in counts on 1 and 3
}
```

### EXPECT_ORDERED_NE()
`EXPECT_ORDERED_NE(first, second)` takes in two parameters: two iterable containers that satisfy the `ranges` concept whose elements are capable of being compared by the `==` operator. It passes iff `first` and `second` have at least one element that do not pass a comparison by the `==` operator and fails otherwise. This function should only be called on containers that have some deterministic method of ordering its elements, ie, passing in `unordered` containers yields undefined behavior.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <set>
#include <unordered_set>

D_TEST(expect_ordered_ne) {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {1, 2, 3, 4, 5};

    EXPECT_ORDERED_NE(a, b); //fails

    int c[] = {5, 4, 3, 2, 1};

    EXPECT_ORDERED_NE(a, c); //passes

    std::vector<int> d = {8, 6, 7, 5, 3, 0, 9};
    int e[] = {8, 6, 7, 5, 3, 0, 9};

    EXPECT_ORDERED_NE(d, e); //fails

    std::set<std::vector<int>> f = {{1, 2, 3}, {4, 5, 6}};
    std::set<std::vector<int>> g = {{1, 2, 3}, {4, 5, 6}};

    EXPECT_ORDERED_NE(f, g); //fails

    std::unordered_set<int> h = {1, 2, 3, 4, 5, 6};
    std::unordered_set<int> i = {1, 2, 3, 4, 5, 6};

    EXPECT_ORDERED_NE(h, i); //undefined behavior, but will most likely fail

    int j[] = {1, 1, 2, 3};
    int k[] = {1, 2, 3, 3};
    EXPECT_ORDERED_NE(j, k); //passes because there is a mismatch in counts on 1 and 3
}
```

### EXPECT_UNORDERED_NE()
`EXPECT_UNORDERED_NE(first, second)` takes in two parameters: two iterable containers that satisfy the `ranges` concept whose elements are capable of being compared by the `==` operator. It passes iff `first` and `second` have at least one element that do not pass a comparison by the `==` operator and fails otherwise. Unlike `ASSERT_ORDERED_NE()`, this function can be used on any kind of container, eg. the ones that don't maintain any ordering.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <set>
#include <unordered_set>

D_TEST(expect_unordered_ne) {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {1, 2, 3, 4, 5};

    EXPECT_UNORDERED_NE(a, b); //fails

    int c[] = {5, 4, 3, 2, 1};

    EXPECT_UNORDERED_NE(a, c); //fails

    std::vector<int> d = {8, 6, 7, 5, 3, 0, 9};
    int e[] = {8, 6, 7, 5, 3, 0, 9};

    EXPECT_UNORDERED_NE(d, e); //fails

    std::set<std::vector<int>> f = {{1, 2, 3}, {4, 5, 6}};
    std::set<std::vector<int>> g = {{2, 2, 3}, {4, 5, 6}};

    EXPECT_UNORDERED_NE(f, g); //passes

    std::unordered_set<int> h = {1, 2, 3, 5, 5, 6};
    std::unordered_set<int> i = {1, 2, 3, 4, 5, 6};

    EXPECT_UNORDERED_NE(h, i); //passes

    int j[] = {1, 1, 2, 3};
    int k[] = {1, 2, 3, 3};
    EXPECT_UNORDERED_NE(j, k); //passes
}
```

### EXPECT_EMPTY()
`EXPECT_EMPTY(container)` takes in one parameter, a container with the `size()` method. It passes iff `container.size() == 0` and fails otherwise.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <set>

D_TEST(expect_empty) {
    std::vector<int> a = {1, 2, 3, 4, 5};
    EXPECT_EMPTY(a); //fails

    std::set<int> b = {};
    EXPECT_EMPTY(b); //passes
}
```

### EXPECT_NEMPTY()
`EXPECT_NEMPTY(container)` takes in one parameter. takes in one parameter, a container with the `size()` method. It passes iff `container.size() != 0` and fails otherwise.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <set>

D_TEST(expect_nempty) {
    std::vector<int> a = {1, 2, 3, 4, 5};
    EXPECT_NEMPTY(a); //passes

    std::set<int> b = {};
    EXPECT_NEMPTY(b); //fails
}
```

### EXPECT_SIZE()
`EXPECT_SIZE(container, size)` takes in two parameters, takes in one parameter, a container with the `size()` method and a `size_t`. It passes iff `container.size() == size` and fails otherwise. 

```
#include <testpp/testpp.hpp>
#include <vector>
#include <set>

D_TEST(expect_size) {
    std::vector<int> a = {1, 2, 3, 4, 5};
    EXPECT_SIZE(a, 5); //passes

    std::set<int> b = {};
    EXPECT_SIZE(b, 0); //passes

    EXPECT_SIZE(b, 5); //fails
}
```

### EXPECT_CONTAINS()
`EXPECT_CONTAINS(container, value)` takes in two parameters, a `ranges` container and a value to search for. It passes iff `container` contains `value` and fails otherwise. 

```
#include <testpp/testpp.hpp>
#include <vector>
#include <set>

D_TEST(expect_contains) {
    std::vector<int> a = {1, 2, 3, 4, 5};
    EXPECT_CONTAINS(a, 5); //passes

    std::set<int> b = {};
    EXPECT_CONTAINS(b, 11); //fails

    EXPECT_CONTAINS(a, -1); //fails
}
```

### EXPECT_DOES_NOT_CONTAIN()
`EXPECT_DOES_NOT_CONTAIN(container, value)` takes in two parameters, a `ranges` container and a value to search for. It passes iff `container` does not contain `value` and fails otherwise.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <set>

D_TEST(expect_does_not_contain) {
    std::vector<int> a = {1, 2, 3, 4, 5};
    EXPECT_DOES_NOT_CONTAIN(a, 5); //fails

    std::set<int> b = {};
    EXPECT_DOES_NOT_CONTAIN(b, 11); //passes

    EXPECT_DOES_NOT_CONTAIN(a, -1); //passes
}
```

## Meta Tests
Meta tests are used to see if a test will pass/fail. Ie, these are tests to ensure that tests are working. It is very important that you do not pass in random functions. These tests also have the capability of defining new tests, in a sense. For instance, there is no `STRING_DOES_NOT_CONTAIN()` test, however, you could combine `ASSERT_STRING_CONTAINS()` with `ASSERT_FAILS()` to create one that would have a similar functionality to what an `ASSERT_STRING_DOES_NOT_CONTAIN()` test would have.
There is an extra meta test `*_FAILS_WITH_MSG()`, however, since the error messaging could change, this test will remain undocumented and shouldn't really be used.

1. [Assert Passes](#assert_passes)
2. [Assert Fails](#assert_fails)
3. [Expect Passes](#expect_passes)
4. [Expect Fails](#expect_fails)

### ASSERT_PASSES()
`ASSERT_PASSES(test)` takes in one parameter, which is a test. It passes iff the passed in test passes, and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>

void gonnaBreakThings() { }

//this is a simple example, but it gets the point across
D_TEST(assert_passes) {
    ASSERT_PASSES(EXPECT_TRUE(true)); //passes
    ASSERT_PASSES(EXPECT_TRUE(false)); //fails
    ASSERT_PASSES(gonnaBreakThings()); //don't do this, but it would pass 

    //fails, but the nested ASSERT_TRUE failing DOES NOT terminate testing for the rest of the suite
    ASSERT_PASSES(ASSERT_TRUE(false)); 
}
```

### ASSERT_FAILS()
`EXPECT_FAILS(test)` takes in one parameter, which is a test. It passes iff the passed in test fails, and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>

void gonnaBreakThings() { }

//this is a simple example, but it gets the point across
D_TEST(assert_fails) {
    ASSERT_FAILS(EXPECT_TRUE(true)); //fails
    ASSERT_FAILS(EXPECT_TRUE(false)); //would pass
    ASSERT_FAILS(gonnaBreakThings()); //don't do this, but it would fail
    ASSERT_FAILS(ASSERT_TRUE(true)); //fails
}
```

### EXPECT_PASSES()
`EXPECT_PASSES(test)` takes in one parameter, which is a test. It passes iff the passed in test passes, and fails otherwise.

```
#include <testpp/testpp.hpp>

void gonnaBreakThings() { }

//this is a simple example, but it gets the point across
D_TEST(expect_passes) {
    EXPECT_PASSES(EXPECT_TRUE(true)); //passes
    EXPECT_PASSES(EXPECT_TRUE(false)); //fails
    EXPECT_PASSES(gonnaBreakThings()); //don't do this, but it would pass 

    //fails, but ASSERT_TRUE failing DOES NOT terminate testing for the rest of the suite
    EXPECT_PASSES(ASSERT_TRUE(false)); 
}
```

### EXPECT_FAILS()
`EXPECT_FAILS(test)` takes in one parameter, which is a test. It passes iff the passed in test fails, and fails otherwise.

```
#include <testpp/testpp.hpp>

void gonnaBreakThings() { }

//this is a simple example, but it gets the point across
D_TEST(expect_fails) {
    EXPECT_FAILS(EXPECT_TRUE(true)); //fails
    EXPECT_FAILS(EXPECT_TRUE(false)); //passes
    EXPECT_FAILS(gonnaBreakThings()); //don't do this, but it would fail
    EXPECT_FAILS(ASSERT_TRUE(true)); 
}
```

## Null Tests
Null tests are used to check if a value is equal to the `nullptr` or not. Since it checks solely for the `nullptr`, passing in the macro `NULL` is not a valid parameter type for any of the test. 

1. [Assert Null](#assert_null)
2. [Assert Not Null](#assert_not_null)
3. [Expect Null](#expect_null)
4. [Expect Not Null](#expect_not_null)

### ASSERT_NULL()
`ASSERT_NULL(val)` takes in a single parameter `val` and asserts that it's the nullptr. This test passes iff `val == nullptr` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>

D_TEST(assert_null) {
    ASSERT_NULL(nullptr) //passes
    ASSERT_NULL(NULL) //doesn't even compile
}
```

### ASSERT_NOT_NULL()
`ASSERT_NOT_NULL(val)` takes in a single parameter `val` and asserts that it's not the nullptr. This test passes iff `val != nullptr` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>

D_TEST(assert_null) {
    ASSERT_NOT_NULL("hello") //passes
    ASSERT_NOT_NULL(nullptr) //fails
    ASSERT_NOT_NULL(NULL) //doesn't even compile
}
```

### EXPECT_NULL()
`EXPECT_NULL(val)` takes in a single parameter `val` and checks that it's the nullptr. This test passes iff `val == nullptr` and fails otherwise.

```
#include <testpp/testpp.hpp>

D_TEST(assert_null) {
    void* ptr = nullptr;
    void*& ref = ptr;
    EXPECT_NULL(ref) //passes
    EXPECT_NULL(NULL) //doesn't even compile
}
```

### EXPECT_NOT_NULL()
`EXPECT_NOT_NULL(val)` takes in a single parameter `val` and checks that it's not the nullptr. This test passes iff `val != nullptr` and fails otherwise.

```
#include <testpp/testpp.hpp>

D_TEST(assert_null) {
    void* ptr = nullptr;
    void*& ref = ptr;
    EXPECT_NOT_NULL(ref) //fails
    EXPECT_NOT_NULL(NULL) //doesn't even compile
}
```

## Predicate Tests
Predicate tests are used to test containers and arrays to see if every element, some elements, or no elements satisfy a given condition.

1. [Assert All](#assert_all)
2. [Assert Some](#assert_some)
3. [Assert None](#assert_none)
4. [Expect All](#expect_all)
5. [Expect Some](#expect_some)
6. [Expect None](#expect_none)

### ASSERT_ALL()
`ASSERT_ALL(container, condition)` takes in two parameters: a container and an anonymous function that returns a boolean value. The container does not have to be an `stl` container, ie. arrays are fine as well. This test passes iff every element in `container` passes the `condition` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>
#include <vector>

D_TEST(assert_all) {
    std::vector<int> a = {1, 2, 2, 3, 4};

    ASSERT_ALL(a, [](int x) { return x > 0; }); //passes

    ASSERT_ALL(a, [](int x) { return x & 1; }); //fails since there are even elements
}
```

### ASSERT_SOME
`ASSERT_SOME(container, condition)` takes in two parameters: a container and an anonymous function that returns a boolean value. The container does not have to be an `stl` container, ie. arrays are fine as well. This test passes iff at least one element in `container` passes the `condition` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>
#include <vector>

D_TEST(assert_some) {
    std::vector<int> a = {1, 2, 2, 3, 4};

    ASSERT_SOME(a, [](int x) { return x > 0; }); //passes

    ASSERT_SOME(a, [](int x) { return x & 1; }); //passes since there is at least one odd element

    ASSERT_SOME(a, [](int x) {return x > 10; }) //fails because none of the elements are larger than 10
}
```

### ASSERT_NONE
`ASSERT_NONE(container, condition)` takes in two parameters: a container and an anonymous function that returns a boolean value. The container does not have to be an `stl` container, ie. arrays are fine as well. This test passes iff no element in `container` passes the `condition` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>
#include <vector>

D_TEST(assert_none) {
    std::vector<int> a = {1, 2, 2, 3, 4};

    ASSERT_NONE(a, [](int x) { return x > 0; }); //fails because every element satisfies this condition

    ASSERT_NONE(a, [](int x) { return x & 1; }); //passes since some elements satisfies this condition

    ASSERT_NONE(a, [](int x) {return x > 10; }) //passes because none of the elements are larger than 10
}
```

### EXPECT_ALL()
`EXPECT_ALL(container, condition)` takes in two parameters: a container and an anonymous function that returns a boolean value. The container does not have to be an `stl` container, ie. arrays are fine as well. This test passes iff every element in `container` passes the `condition` and fails otherwise. 

```
#include <testpp/testpp.hpp>
#include <vector>

D_TEST(expect_all) {
    std::vector<int> a = {1, 2, 2, 3, 4};

    EXPECT_ALL(a, [](int x) { return x > 0; }); //passes

    EXPECT_ALL(a, [](int x) { return x & 1; }); //fails since there are even elements
}
```

### EXPECT_SOME
`EXPECT_SOME(container, condition)` takes in two parameters: a container and an anonymous function that returns a boolean value. The container does not have to be an `stl` container, ie. arrays are fine as well. This test passes iff at least one element in `container` passes the `condition` and fails otherwise.
```
#include <testpp/testpp.hpp>
#include <vector>

D_TEST(expect_some) {
    std::vector<int> a = {1, 2, 2, 3, 4};

    EXPECT_SOME(a, [](int x) { return x > 0; }); //passes

    EXPECT_SOME(a, [](int x) { return x & 1; }); //passes since there is at least one odd element

    EXPECT_SOME(a, [](int x) {return x > 10; }) //fails because none of the elements are larger than 10
}
```

### EXPECT_NONE
`EXPECT_NONE(container, condition)` takes in two parameters: a container and an anonymous function that returns a boolean value. The container does not have to be an `stl` container, ie. arrays are fine as well. This test passes iff no element in `container` passes the `condition` and fails otherwise. 

```
#include <testpp/testpp.hpp>
#include <vector>

D_TEST(expect_none) {
    std::vector<int> a = {1, 2, 2, 3, 4};

    EXPECT_NONE(a, [](int x) { return x > 0; }); //fails because every element satisfies this condition

    EXPECT_NONE(a, [](int x) { return x & 1; }); //passes since some elements satisfies this condition

    EXPECT_NONE(a, [](int x) {return x > 10; }) //passes because none of the elements are larger than 10
}
```

## Set Tests
Set tests are used on containers that satisfy the `ranges` concept. They can be used on containers other than `set` and `unordered_set`. The name "set" just means that we perform set operations on containers as if they were mathematical sets.

1. [Assert Set Equals](#assert_set_eq)
2. [Assert Set Not Equals](#assert_set_ne)
3. [Assert Subset](#assert_subset)
4. [Assert Superset](#assert_superset)
5. [Assert Strict Subset](#assert_strict_subset)
6. [Expect Set Equals](#expect_set_eq)
7. [Expect Set Not Equals](#expect_set_ne)
8. [Expect Subset](#expect_subset)
9. [Expect Superset](#expect_superset)
10. [Expect Strict Subset](#expect_strict_subset)

### ASSERT_SET_EQ()
`ASSERT_SET_EQ(first, second)` takes in two parameters, two containers that satisfy the `ranges` concept. This test passes iff `first` and `second` contain the same elements, REGARDLESS of counts, and fails otherwise. Note that this indifference of counts is a big criterion that separates this test from `ASSERT_UNORDERED_EQ()`. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <unordered_set>

//this is a simple example, but it gets the point across
D_TEST(assert_set_eq) {
    std::vector<int> a = {1, 2, 2, 3, 4};
    std::vector<int> b = {1, 2, 3, 4};

    ASSERT_SET_EQ(a, b); //passes

    std::unordered_set<int> c = {1, 2, 3, 4};

    ASSERT_SET_EQ(a, c); //passes

    std::unordered_set<int> d = {1, 2, 3};
    ASSERT_SET_EQ(b, d); //fails
}
```

### ASSERT_SET_NE()
`ASSERT_SET_NE(first, second)` takes in two parameters, two containers that satisfy the `ranges` concept. This test passes iff `first` and `second` has at least one differing element, REGARDLESS of counts, and fails otherwise. Note that this indifference of counts is a big criterion that separates this test from `ASSERT_UNORDERED_NE()`. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <unordered_set>

//this is a simple example, but it gets the point across
D_TEST(assert_set_ne) {
    std::vector<int> a = {1, 2, 2, 3, 4};
    std::vector<int> b = {1, 2, 3, 4};

    ASSERT_SET_NE(a, b); //fails

    std::unordered_set<int> c = {1, 2, 3, 4};

    ASSERT_SET_NE(a, c); //fails

    std::unordered_set<int> d = {1, 2, 3};
    ASSERT_SET_NE(b, d); //passes
}
```

### ASSERT_SUBSET()
`ASSERT_SUBSET(first, second)` takes in two parameters, two containers that satisfy the `ranges` concept. This test passes iff every element in `first` appears in `second` REGARDLESS of counts, and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <unordered_set>

D_TEST(assert_subset) {
    std::vector<int> a = {1, 2, 2, 3, 4};
    std::vector<int> b = {1, 2, 3, 4};

    ASSERT_SUBSET(a, b); //passes

    std::unordered_set<int> c = {1, 2, 3, 4};

    ASSERT_SUBSET(a, c); //passes

    std::unordered_set<int> d = {1, 2, 3};
    ASSERT_SUBSET(b, d); //fails
}
```

### ASSERT_SUPERSET()
`ASSERT_SUPERSET(first, second)` takes in two parameters, two containers that satisfy the `ranges` concept. This test passes iff every element in `second` appears in `first` REGARDLESS of counts, and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <unordered_set>

D_TEST(assert_superset) {
    std::vector<int> a = {1, 2, 2, 3, 4};
    std::vector<int> b = {1, 2, 3, 4};

    ASSERT_SUPERSET(a, b); //passes

    std::unordered_set<int> c = {1, 2, 3, 4};

    ASSERT_SUPERSET(a, c); //passes

    std::unordered_set<int> d = {1, 2, 3};
    ASSERT_SUPERSET(b, d); //passes

    std::vector<int> e = {5};
    ASSERT_SUPER_SET(c, e); //fails
}
```

### ASSERT_STRICT_SUBSET()
`ASSERT_STRICT_SUBSET(first, second)` takes in two parameters, two containers that satisfy the `ranges` concept. This test passes iff every element in `first` appears in `second`, and there is at least one element in `second` that does not appear in `first`, REGARDLESS of counts, and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <unordered_set>

D_TEST(assert_strict_subset) {
    std::vector<int> a = {1, 2, 2, 3, 4};
    std::vector<int> b = {1, 2, 3, 4};

    ASSERT_STRICT_SUBSET(a, b); //fails
    ASSERT_STRICT_SUBSET(b, a); //fails

    std::unordered_set<int> c = {1, 2, 3, 4};

    ASSERT_STRICT_SUBSET(a, c); //fails

    std::unordered_set<int> d = {1, 2, 3};
    ASSERT_STRICT_SUBSET(b, d); //fails
    ASSERT_STRICT_SUBSET(d, b); //passes

    std::vector<int> e = {5};
    ASSERT_STRICT_SUBSET(c, e); //fails
}
```

### EXPECT_SET_EQ()
`EXPECT_SET_EQ(first, second)` takes in two parameters, two containers that satisfy the `ranges` concept. This test passes iff `first` and `second` contain the same elements, REGARDLESS of counts, and fails otherwise. Note that this indifference of counts is a big criterion that separates this test from `EXPECT_UNORDERED_EQ()`.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <unordered_set>

//this is a simple example, but it gets the point across
D_TEST(expect_set_eq) {
    std::vector<int> a = {1, 2, 2, 3, 4};
    std::vector<int> b = {1, 2, 3, 4};

    EXPECT_SET_EQ(a, b); //passes

    std::unordered_set<int> c = {1, 2, 3, 4};

    EXPECT_SET_EQ(a, c); //passes

    std::unordered_set<int> d = {1, 2, 3};
    EXPECT_SET_EQ(b, d); //fails
}
```

### EXPECT_SET_NE()
`EXPECT_SET_NE(first, second)` takes in two parameters, two containers that satisfy the `ranges` concept. This test passes iff `first` and `second` has at least one differing element, REGARDLESS of counts, and fails otherwise. Note that this indifference of counts is a big criterion that separates this test from `EXPECT_UNORDERED_NE()`.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <unordered_set>

//this is a simple example, but it gets the point across
D_TEST(expect_set_ne) {
    std::vector<int> a = {1, 2, 2, 3, 4};
    std::vector<int> b = {1, 2, 3, 4};

    EXPECT_SET_NE(a, b); //fails

    std::unordered_set<int> c = {1, 2, 3, 4};

    EXPECT_SET_NE(a, c); //fails

    std::unordered_set<int> d = {1, 2, 3};
    EXPECT_SET_NE(b, d); //passes
}
```

### EXPECT_SUBSET()
`EXPECT_SUBSET(first, second)` takes in two parameters, two containers that satisfy the `ranges` concept. This test passes iff every element in `first` appears in `second` REGARDLESS of counts, and fails otherwise.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <unordered_set>

D_TEST(expect_subset) {
    std::vector<int> a = {1, 2, 2, 3, 4};
    std::vector<int> b = {1, 2, 3, 4};

    EXPECT_SUBSET(a, b); //passes

    std::unordered_set<int> c = {1, 2, 3, 4};

    EXPECT_SUBSET(a, c); //passes

    std::unordered_set<int> d = {1, 2, 3};
    EXPECT_SUBSET(b, d); //fails
}
```

### EXPECT_SUPERSET()
`EXPECT_SUPERSET(first, second)` takes in two parameters, two containers that satisfy the `ranges` concept. This test passes iff every element in `second` appears in `first` REGARDLESS of counts, and fails otherwise. 

```
#include <testpp/testpp.hpp>
#include <vector>
#include <unordered_set>

D_TEST(expect_superset) {
    std::vector<int> a = {1, 2, 2, 3, 4};
    std::vector<int> b = {1, 2, 3, 4};

    EXPECT_SUPERSET(a, b); //passes

    std::unordered_set<int> c = {1, 2, 3, 4};

    EXPECT_SUPERSET(a, c); //passes

    std::unordered_set<int> d = {1, 2, 3};
    EXPECT_SUPERSET(b, d); //passes

    std::vector<int> e = {5};
    EXPECT_SUPER_SET(c, e); //fails
}
```

### EXPECT_STRICT_SUBSET()
`EXPECT_STRICT_SUBSET(first, second)` takes in two parameters, two containers that satisfy the `ranges` concept. This test passes iff every element in `first` appears in `second`, and there is at least one element in `second` that does not appear in `first`, REGARDLESS of counts, and fails otherwise.

```
#include <testpp/testpp.hpp>
#include <vector>
#include <unordered_set>

D_TEST(expect_strict_subset) {
    std::vector<int> a = {1, 2, 2, 3, 4};
    std::vector<int> b = {1, 2, 3, 4};

    EXPECT_STRICT_SUBSET(a, b); //fails
    EXPECT_STRICT_SUBSET(b, a); //fails

    std::unordered_set<int> c = {1, 2, 3, 4};

    EXPECT_STRICT_SUBSET(a, c); //fails

    std::unordered_set<int> d = {1, 2, 3};
    EXPECT_STRICT_SUBSET(b, d); //fails
    EXPECT_STRICT_SUBSET(d, b); //passes

    std::vector<int> e = {5};
    EXPECT_STRICT_SUBSET(c, e); //fails
}
```

## String Tests
Strings tests are used for checking the (in)equality of strings and whether or not they're empty. Null strings should be checked with using the [null tests](#null-tests). String tests use `std::string_view`, so as long as your string-type is compatible with string_view, these tests should work as you'd expect.


1. [Assert String Equals](#assert_str_eq)
2. [Assert String Not Equals](#assert_str_ne)
3. [Assert String Empty](#assert_str_emt)
4. [Assert String Not Empty](#assert_str_nemt)
5. [Assert String Contains](#assert_str_contains)
6. [Assert String Starts With](#assert_str_starts_with)
7. [Assert String Ends With](#assert_str_ends_with)
8. [Expect String Equals](#expect_str_eq)
9. [Expect String Not Equals](#expect_str_ne)
10. [Expect String Empty](#expect_str_emt)
11. [Expect String Not Empty](#expect_str_nemt)
12. [Expect String Contains](#expect_str_contains)
13. [Expect String Starts With](#expect_str_starts_with)
14. [Expect String Ends With](#expect_str_ends_with)

### ASSERT_STR_EQ()
`ASSERT_STR_EQ(a, b)` takes in two arguments, both must be convertible to `std::string_view`. Equality is defined on the `==` operator for `std::string_view`.

```
#include <testpp/testpp.hpp>
#include <string>

TEST(assert_str_eq, std_strings) {
    std::string a = "hello";
    std::string b = "hello";

    ASSERT_STR_EQ(a, b); //passes
    
    std::string c = "hello\0";
    
    ASSERT_STR_EQ(a, c); //passes
    ASSERT_STR_EQ(b, c); //passes

    std::string d = "goodbye";
    ASSERT_STR_EQ(c, d); //fails
}
```

```
#include <testpp/testpp.hpp>

TEST(assert_str_eq, char_ptr) {
    const char* a = "hello";
    const char* b = "hello";

    ASSERT_STR_EQ(a, b); //passes

    const char* c = "hello\0";

    ASSERT_STR_EQ(a, c); //passes
    ASSERT_STR_EQ(b, c); //passes

    const char* d = "goodbye";
    ASSERT_STR_EQ(c, d); //fails
}
```

```
#include <testpp/testpp.hpp>

TEST(assert_str_eq, char_arr) {
    char a[] = {'h', 'e', 'l', 'l', 'o'};
    char b[] = "hello"; //automatically has the null terminator character appended to it

    ASSERT_STR_EQ(a, b); //passes

    char c[] = "hello\0wazzup"; //definitely different looking from a[] and b[]
    ASSERT_STR_EQ(a, c); //passes because everything before c[]'s terminator character is the same as a[]'s contents

    char d[] = "hello there";
    ASSERT_STR_EQ(a, d); //fails because the length of d[] is different than the length of a[]
}
```

### ASSERT_STR_NE()
`ASSERT_STR_NE(a, b)` takes in two arguments, both must be convertible to `std::string_view`. Inequality is defined on the `!=` operator for `std::string_view`.

```
#include <testpp/testpp.hpp>
#include <string>

TEST(assert_str_ne, std_strings) {
    std::string a = "hello";
    std::string b = "hello!";

    ASSERT_STR_NE(a, b); //passes
    
    std::string c = "hi";
    
    ASSERT_STR_NE(a, c); //passes
    ASSERT_STR_NE(b, c); //passes

    std::string d = "hello\0";
    ASSERT_STR_NE(a, d); //fails
}
```

```
#include <testpp/testpp.hpp>

TEST(assert_str_ne, char_ptr) {
    const char* a = "hello";
    const char* b = "hello";

    ASSERT_STR_NE(a, b); //fails

    const char* c = "hello\0";

    ASSERT_STR_NE(a, c); //doesn't run, but would fail
    ASSERT_STR_NE(b, c); //doesn't run, but would fail

    const char* d = "goodbye";
    ASSERT_STR_NE(c, d); //doesn't run, but would pass
}
```

```
#include <testpp/testpp.hpp>

TEST(assert_str_ne, char_arr) {
    char a[] = {'h', 'e', 'l', 'l', 'o'};
    char b[] = "hello"; //automatically has the null terminator character appended to it

    ASSERT_STR_NE(a, b); //fails

    char c[] = "hello\0wazzup"; //definitely different looking from a[] and b[]
    ASSERT_STR_NE(a, c);    //doesn't run, but if it did, it fails because everything 
                            //before c[]'s terminator character is the same as a[]'s contents

    char d[] = "hello there";
    ASSERT_STR_NE(a, d);    //doesn't run, but if it did, it passes because the 
                            //length of d[] is different than the length of a[]
}
```

### ASSERT_STR_EMT()
`ASSERT_STR_EMT(a)` takes in one parameter, both must be convertible to `std::string_view`. Emptiness is defined on the `empty()` method.

```
#include <testpp/testpp.hpp>

TEST(assert_str_emt, std_string) {
    std::string a = "";
    ASSERT_STR_EMT(a); //passes

    std::string b = "hi";
    ASSERT_STR_EMT(b); //fails

    std::string c = nullptr;
    ASSERT_STR_EMT(c); //doesn't run but would have a segmentation fault. You have been warned.
}
```

```
#include <testpp/testpp.hpp>

TEST(assert_str_emt, char_ptr) {
    const char* a = "";
    ASSERT_STR_EMT(a); //passes

    const char* b = "hi";
    ASSERT_STR_EMT(b); //fails

    const char* c = nullptr;
    ASSERT_STR_EMT(c); //doesn't run, but would fail
}
```

```
#include <testpp/testpp.hpp>

TEST(assert_str_emt, char_arr) {
    char a[] = "";
    ASSERT_STR_EMT(a); //passes

    const char b[] = "hi";
    ASSERT_STR_EMT(b); //fails

    const char c[] = nullptr;
    ASSERT_STR_EMT(c); //doesn't run, but there would be a segmentation fault. You have been warned.
}
```

### ASSERT_STR_NEMT()
`ASSERT_STR_NEMT(a)` takes in one parameter, both must be convertible to `std::string_view`. Non-emptiness is defined on the `empty()` method.

```
#include <testpp/testpp.hpp>

TEST(assert_str_nemt, std_string) {
    std::string a = "";
    ASSERT_STR_NEMT(a); //fails

    std::string b = "hi";
    ASSERT_STR_NEMT(b); //doesn't run, but would pass

    std::string c = nullptr;
    ASSERT_STR_NEMT(c); //doesn't run, but would segmentation fault. You have been warned.
}
```

```
#include <testpp/testpp.hpp>

TEST(expect_str_nemt, char_ptr) {
    const char* a = "";
    ASSERT_STR_NEMT(a); //fails

    const char* b = "hi";
    ASSERT_STR_NEMT(b); //doesn't run, but would pass

    const char* c = nullptr;
    ASSERT_STR_NEMT(c); //doesn't run, but would fail
}
```

```
#include <testpp/testpp.hpp>

TEST(assert_str_nemt, char_arr) {
    char a[] = "";
    ASSERT_STR_NEMT(a); //fails

    const char b[] = "hi";
    ASSERT_STR_NEMT(b); //doesn't run, but would pass

    const char c[] = nullptr;
    ASSERT_STR_NEMT(c); //doesn't run, but would segmentation fault. You have been warned.
}
```

### ASSERT_STR_CONTAINS()
`ASSERT_STR_CONTAINS(string, substr)` takes in two arguments, both must be convertible to `std::string_view`. Emptiness is defined on the `empty()` method. String contains is determined by the `find()` method. This test passes iff `string_view.find(substr)` does not return `std::string_view::npos` and fails otherwise.

```
#include <testpp/testpp.hpp>
#include <string>

TEST(assert_str_contains, string) {
    std::string a = "hello";
    std::string b = "o";

    ASSERT_STR_CONTAINS(a, b); //passes
    ASSERT_STR_CONTAINS(b, a); //fails
    ASSERT_STR_CONTAINS(a, a); //would pass
}
```

```
#include <testpp/testpp.hpp>

TEST(assert_str_contains, char_ptr) {
    const char* a = "hello";
    const char* b = "o";

    ASSERT_STR_CONTAINS(a, b); //passes
    ASSERT_STR_CONTAINS(b, a); //fails
    ASSERT_STR_CONTAINS(a, a); //passes
    
    const char* c = nullptr;

    ASSERT_STR_CONTAINS(a, c); //fails
    ASSERT_STR_CONTAINS(c, a); //fails

    const char* d = nullptr;

    ASSERT_STR_CONTAINS(c, d); //passes
}
```

```
#include <testpp/testpp.hpp>

TEST(assert_str_contains, char_arr) {
    char a[] = "hello";
    char b[] = "o";

    ASSERT_STR_CONTAINS(a, b); //passes
    ASSERT_STR_CONTAINS(b, a); //fails
    ASSERT_STR_CONTAINS(a, a); //passes
}
```

### ASSERT_STR_STARTS_WITH()
`ASSERT_STR_STARTS_WITH(string, substr)` takes in two arguments, both must be convertible to `std::string_view`. Emptiness is defined on the `empty()` method. String starts with is determined by the `starts_with()` method. This test passes iff `string_view.starts_with(substr)` does not return `false` and fails otherwise.

```
#include <testpp/testpp.hpp>
#include <string>

TEST(assert_str_starts_with, string) {
    std::string a = "hello";
    std::string b = "he";

    ASSERT_STR_STARTS_WITH(a, b); //passes
    ASSERT_STR_STARTS_WITH(b, a); //fails
    ASSERT_STR_STARTS_WITH(a, a); //passes
}
```

```
#include <testpp/testpp.hpp>

TEST(assert_str_starts_with, char_ptr) {
    const char* a = "hello";
    const char* b = "he";

    ASSERT_STR_STARTS_WITH(a, b); //passes
    ASSERT_STR_STARTS_WITH(b, a); //fails
    ASSERT_STR_STARTS_WITH(a, a); //passes

    const char* c = nullptr;

    ASSERT_STR_STARTS_WITH(a, c); //fails
    ASSERT_STR_STARTS_WITH(c, a); //fails

    const char* d = nullptr;

    ASSERT_STR_STARTS_WITH(c, d); //passes
}
```

```
#include <testpp/testpp.hpp>

TEST(assert_str_starts_with, char_arr) {
    char a[] = "hello";
    char b[] = "he";

    ASSERT_STR_STARTS_WITH(a, b); //passes
    ASSERT_STR_STARTS_WITH(b, a); //fails
    ASSERT_STR_STARTS_WITH(a, a); //passes
}
```

### ASSERT_STR_ENDS_WITH()
`ASSERT_STR_ENDS_WITH(string, substr)` takes in two arguments, both must be convertible to `std::string_view`. Emptiness is defined on the `empty()` method. String starts with is determined by the `ends_with()` method. This test passes iff `string_view.ends_with(substr)` does not return `false` and fails otherwise.

```
#include <testpp/testpp.hpp>
#include <string>

TEST(assert_str_ends_with, string) {
    std::string a = "hello";
    std::string b = "lo";

    ASSERT_STR_ENDS_WITH(a, b); //passes
    ASSERT_STR_ENDS_WITH(b, a); //fails
    ASSERT_STR_ENDS_WITH(a, a); //passes
}
```

```
#include <testpp/testpp.hpp>

TEST(assert_str_ends_with, char_ptr) {
    const char* a = "hello";
    const char* b = "he";

    ASSERT_STR_ENDS_WITH(a, b); //passes
    ASSERT_STR_ENDS_WITH(b, a); //fails
    ASSERT_STR_ENDS_WITH(a, a); //passes

    const char* c = nullptr;

    ASSERT_STR_ENDS_WITH(a, c); //fails
    ASSERT_STR_ENDS_WITH(c, a); //fails

    const char* d = nullptr;

    ASSERT_STR_ENDS_WITH(c, d); //passes
}
```

```
#include <testpp/testpp.hpp>

TEST(assert_str_ends_with, char_arr) {
    char a[] = "hello";
    char b[] = "he";

    ASSERT_STR_ENDS_WITH(a, b); //passes
    ASSERT_STR_ENDS_WITH(b, a); //fails
    ASSERT_STR_ENDS_WITH(a, a); //passes
}
```

### EXPECT_STR_EQ()
`EXPECT_STR_EQ(a, b)` takes in two arguments, both must be convertible to `std::string_view`. Equality is defined on the `==` operator for `std::string_view`.

```
#include <testpp/testpp.hpp>
#include <string>

TEST(expect_str_eq, std_strings) {
    std::string a = "hello";
    std::string b = "hello";

    EXPECT_STR_EQ(a, b); //passes
    
    std::string c = "hello\0";
    
    EXPECT_STR_EQ(a, c); //passes
    EXPECT_STR_EQ(b, c); //passes

    std::string d = "goodbye";
    EXPECT_STR_EQ(c, d); //fails
}
```

```
#include <testpp/testpp.hpp>

TEST(expect_str_eq, char_ptr) {
    const char* a = "hello";
    const char* b = "hello";

    EXPECT_STR_EQ(a, b); //passes

    const char* c = "hello\0";

    EXPECT_STR_EQ(a, c); //passes
    EXPECT_STR_EQ(b, c); //passes

    const char* d = "goodbye";
    EXPECT_STR_EQ(c, d); //fails
}
```

```
#include <testpp/testpp.hpp>

TEST(expect_str_eq, char_arr) {
    char a[] = {'h', 'e', 'l', 'l', 'o'};
    char b[] = "hello"; //automatically has the null terminator character appended to it

    EXPECT_STR_EQ(a, b); //passes

    char c[] = "hello\0wazzup"; //definitely different looking from a[] and b[]
    EXPECT_STR_EQ(a, c); //passes because everything before c[]'s terminator character is the same as a[]'s contents

    char d[] = "hello there";
    EXPECT_STR_EQ(a, d); //fails because the length of d[] is different than the length of a[]
}
```

### EXPECT_STR_NE()
`EXPECT_STR_NE(a, b)` takes in two arguments, both must be convertible to `std::string_view`. Inequality is defined on the `!=` operator for `std::string_view`.

```
#include <testpp/testpp.hpp>
#include <string>

TEST(expect_str_ne, std_strings) {
    std::string a = "hello";
    std::string b = "hello!";

    EXPECT_STR_NE(a, b); //passes
    
    std::string c = "hi";
    
    EXPECT_STR_NE(a, c); //passes
    EXPECT_STR_NE(b, c); //passes

    std::string d = "hello\0";
    EXPECT_STR_NE(a, d); //fails
}
```

```
#include <testpp/testpp.hpp>

TEST(expect_str_ne, char_ptr) {
    const char* a = "hello";
    const char* b = "hello";

    EXPECT_STR_NE(a, b); //fails

    const char* c = "hello\0";

    EXPECT_STR_NE(a, c); //fails
    EXPECT_STR_NE(b, c); //fails

    const char* d = "goodbye";
    EXPECT_STR_NE(c, d); //passes
}
```

```
#include <testpp/testpp.hpp>

TEST(expect_str_ne, char_arr) {
    char a[] = {'h', 'e', 'l', 'l', 'o'};
    char b[] = "hello"; //automatically has the null terminator character appended to it

    EXPECT_STR_NE(a, b); //fails

    char c[] = "hello\0wazzup"; //definitely different looking from a[] and b[]
    EXPECT_STR_NE(a, c); //fails because everything before c[]'s terminator character is the same as a[]'s contents

    char d[] = "hello there";
    EXPECT_STR_NE(a, d); //passes because the length of d[] is different than the length of a[]
}
```

### EXPECT_STR_EMT()
`EXPECT_STR_EMT(a)` takes in one parameter, both must be convertible to `std::string_view`. Emptiness is defined on the `empty()` method.

```
#include <testpp/testpp.hpp>

TEST(expect_str_emt, std_string) {
    std::string a = "";
    EXPECT_STR_EMT(a); //passes

    std::string b = "hi";
    EXPECT_STR_EMT(b); //fails

    std::string c = nullptr;
    EXPECT_STR_EMT(c); //segmentation fault. You have been warned.
}
```

```
#include <testpp/testpp.hpp>

TEST(expect_str_emt, char_ptr) {
    const char* a = "";
    EXPECT_STR_EMT(a); //passes

    const char* b = "hi";
    EXPECT_STR_EMT(b); //fails

    const char* c = nullptr;
    EXPECT_STR_EMT(c); //fails
}
```

```
#include <testpp/testpp.hpp>

TEST(expect_str_emt, char_arr) {
    char a[] = "";
    EXPECT_STR_EMT(a); //passes

    const char b[] = "hi";
    EXPECT_STR_EMT(b); //fails

    const char c[] = nullptr;
    EXPECT_STR_EMT(c); //segmentation fault. You have been warned.
}
```

### EXPECT_STR_NEMT()
`EXPECT_STR_NEMT(a)` takes in one parameter, both must be convertible to `std::string_view`. Non-emptiness is defined on the `empty()` method.

```
#include <testpp/testpp.hpp>

TEST(expect_str_nemt, std_string) {
    std::string a = "";
    EXPECT_STR_NEMT(a); //fails

    std::string b = "hi";
    EXPECT_STR_NEMT(b); //passes

    std::string c = nullptr;
    EXPECT_STR_NEMT(c); //segmentation fault. You have been warned.
}
```

```
#include <testpp/testpp.hpp>

TEST(expect_str_nemt, char_ptr) {
    const char* a = "";
    EXPECT_STR_NEMT(a); //fails

    const char* b = "hi";
    EXPECT_STR_NEMT(b); //passes

    const char* c = nullptr;
    EXPECT_STR_NEMT(c); // fails
}
```

```
#include <testpp/testpp.hpp>

TEST(expect_str_nemt, char_arr) {
    char a[] = "";
    EXPECT_STR_NEMT(a); //fails

    const char b[] = "hi";
    EXPECT_STR_NEMT(b); //passes

    const char c[] = nullptr;
    EXPECT_STR_NEMT(c); //segmentation fault. You have been warned.
}
```

### EXPECT_STR_CONTAINS()
`EXPECT_STR_CONTAINS(string, substr)` takes in two arguments, both must be convertible to `std::string_view`. Emptiness is defined on the `empty()` method. String contains is determined by the `find()` method. This test passes iff `string_view.find(substr)` does not return `std::string_view::npos` and fails otherwise.

```
#include <testpp/testpp.hpp>
#include <string>

TEST(expect_str_contains, string) {
    std::string a = "hello";
    std::string b = "o";

    EXPECT_STR_CONTAINS(a, b); //passes
    EXPECT_STR_CONTAINS(b, a); //fails
    EXPECT_STR_CONTAINS(a, a); //passes
}
```

```
#include <testpp/testpp.hpp>

TEST(expect_str_contains, char_ptr) {
    const char* a = "hello";
    const char* b = "o";

    EXPECT_STR_CONTAINS(a, b); //passes
    EXPECT_STR_CONTAINS(b, a); //fails
    EXPECT_STR_CONTAINS(a, a); //passes
    
    const char* c = nullptr;

    EXPECT_STR_CONTAINS(a, c); //fails
    EXPECT_STR_CONTAINS(c, a); //fails

    const char* d = nullptr;

    EXPECT_STR_CONTAINS(c, d); //passes
}
```

```
#include <testpp/testpp.hpp>

TEST(expect_str_contains, char_arr) {
    char a[] = "hello";
    char b[] = "o";

    EXPECT_STR_CONTAINS(a, b); //passes
    EXPECT_STR_CONTAINS(b, a); //fails
    EXPECT_STR_CONTAINS(a, a); //passes
}
```

### EXPECT_STR_STARTS_WITH()
`EXPECT_STR_STARTS_WITH(string, substr)` takes in two arguments, both must be convertible to `std::string_view`. Emptiness is defined on the `empty()` method. String starts with is determined by the `starts_with()` method. This test passes iff `string_view.starts_with(substr)` does not return `false` and fails otherwise.

```
#include <testpp/testpp.hpp>
#include <string>

TEST(expect_str_starts_with, string) {
    std::string a = "hello";
    std::string b = "he";

    EXPECT_STR_STARTS_WITH(a, b); //passes
    EXPECT_STR_STARTS_WITH(b, a); //fails
    EXPECT_STR_STARTS_WITH(a, a); //passes
}
```

```
#include <testpp/testpp.hpp>

TEST(expect_str_starts_with, char_ptr) {
    const char* a = "hello";
    const char* b = "he";

    EXPECT_STR_STARTS_WITH(a, b); //passes
    EXPECT_STR_STARTS_WITH(b, a); //fails
    EXPECT_STR_STARTS_WITH(a, a); //passes

    const char* c = nullptr;

    EXPECT_STR_STARTS_WITH(a, c); //fails
    EXPECT_STR_STARTS_WITH(c, a); //fails

    const char* d = nullptr;

    EXPECT_STR_STARTS_WITH(c, d); //passes
}
```

```
#include <testpp/testpp.hpp>

TEST(expect_str_starts_with, char_arr) {
    char a[] = "hello";
    char b[] = "he";

    EXPECT_STR_STARTS_WITH(a, b); //passes
    EXPECT_STR_STARTS_WITH(b, a); //fails
    EXPECT_STR_STARTS_WITH(a, a); //passes
}
```

### EXPECT_STR_ENDS_WITH()
`EXPECT_STR_STARTS_WITH(string, substr)` takes in two arguments, both must be convertible to `std::string_view`. Emptiness is defined on the `empty()` method. String starts with is determined by the `ends_with()` method. This test passes iff `string_view.ends_with(substr)` does not return `false` and fails otherwise.

```
#include <testpp/testpp.hpp>
#include <string>

TEST(expect_str_ends_with, string) {
    std::string a = "hello";
    std::string b = "lo";

    EXPECT_STR_ENDS_WITH(a, b); //passes
    EXPECT_STR_ENDS_WITH(b, a); //fails
    EXPECT_STR_ENDS_WITH(a, a); //passes
}
```

```
#include <testpp/testpp.hpp>

TEST(expect_str_ends_with, char_ptr) {
    const char* a = "hello";
    const char* b = "he";

    EXPECT_STR_ENDS_WITH(a, b); //passes
    EXPECT_STR_ENDS_WITH(b, a); //fails
    EXPECT_STR_ENDS_WITH(a, a); //passes

    const char* c = nullptr;

    EXPECT_STR_ENDS_WITH(a, c); //fails
    EXPECT_STR_ENDS_WITH(c, a); //fails

    const char* d = nullptr;

    EXPECT_STR_ENDS_WITH(c, d); //passes
}
```

```
#include <testpp/testpp.hpp>

TEST(expect_str_ends_with, char_arr) {
    char a[] = "hello";
    char b[] = "he";

    EXPECT_STR_ENDS_WITH(a, b); //passes
    EXPECT_STR_ENDS_WITH(b, a); //fails
    EXPECT_STR_ENDS_WITH(a, a); //passes
}
```

## Throws Tests
Throws tests are used to check whether or not a function throws or does not throw an error. You are able to pass in anonymous functions, as well as functions that require parameters. Since functions can take parameters or none, you must pass in the function with `()` at the end of the function name.

1. [Assert Throws](#assert_throws)
2. [Assert Does Not Throw](#assert_does_not_throw)
3. [Assert Throws With Message](#assert_throws_msg)
4. [Expect Throws](#expect_throws)
5. [Expect Does Not Throw](#expect_does_not_throw)
6. [Expect Throws With Message](#expect_throws_msg)

### ASSERT_THROWS()
`ASSERT_THROWS(func, ex)` takes in up to two parameters: a function and optionally a type of exception that should be thrown. In the case that `ex` is not provided, it will pass iff `func` throws anything. In the case that `ex` is provided, it will pass iff `func` throws the same exception type as `ex`. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>

void dumbFunc() {
    throws 42;
}

void anotherFunc() { }

TEST(assert_throws, no_exception_type) {
    ASSERT_THROWS(dumbFunc); //passes

    ASSERT_THROWS(anotherFunc); //fails because it doesn't throw anything
}
```

```
#include <testpp/testpp.hpp>

void dumbFunc() {
    throw 42;
}

TEST(assert_throws, with_exception_type) {
    ASSERT_THROWS(dumbFunc, int); //passes
    
    ASSERT_THROWS(dumbFunc, std::invalid_argument); //fails because it doesn't throw the specified type
}
```

### ASSERT_DOES_NOT_THROW()
`ASSERT_DOES_NOT_THROW(func)` takes in one parameter, which is just a function. It passes iff `func` does not throw anything. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>

D_TEST(assert_does_not_throw) {
    ASSERT_DOES_NOT_THROW([&]() { }); //passes
    ASSERT_DOES_NOT_THROW([&]() { throw 42; }); //fails
}
```

### ASSERT_THROWS_MSG()
`ASSERT_THROWS_MSG(func, message)` takes in two parameters: a function and a message that should be thrown. It passes iff the function throws an error and the message of the thrown error is equal to the `message` parameter. Upon failure it will terminate testing for the test suite it was called in. Since C++ allows you to throw any type, this test will pass if you throw an `std::string` that is equal to the `message` parameter. Ie, you don't need to necessarily throw an `std::exception` with a `what()` that equals `message`.

```
#include <testpp/testpp.hpp>
#include <exceptional>
#include <string>

void dumbFunc() {
    throw 42;
}

void throwsException() {
    throw std::invalid_argument("This is a bad argument");
}

void throwString() {
    throw std::string("hi");
}

D_TEST(assert_throws_with_message) {
    ASSERT_THROWS_MSG(dumbFunc, "hi"); //fails
    ASSERT_THROWS_MSG(throwsException(), "This is a bad argument"); //passes
    ASSERT_THROWS_MSG(throwString, "hi"); //passes
}
```

### EXPECT_THROWS()
`EXPECT_THROWS(func, ex)` takes in up to two parameters: a function and optionally a type of exception that should be thrown. In the case that `ex` is not provided, it will pass iff `func` throws anything. In the case that `ex` is provided, it will pass iff `func` throws the same exception type as `ex`. 

```
#include <testpp/testpp.hpp>

void dumbFunc(int a, int b) {
    throw (a + b);
}

void anotherFunc() { }

TEST(expect_throws, no_exception_type) {
    EXPECT_THROWS(dumbFunc(40, 2)); //passes
    EXPECT_THROWS(anotherFunc()); //fails
}
```

```
#include <testpp/testpp.hpp>

void dumbFunc(int a, int b) {
    throw (a + b);
}

TEST(expect_throws, with_exception_type) {
    EXPECT_THROWS(dumbFunc(40, 2), float); //fails because it throws an int
    EXPECT_THROWS(dumbFunc(40, 2), int); //passes
}
```

### EXPECT_DOES_NOT_THROW()
`EXPECT_DOES_NOT_THROW(func)` takes in one parameter, which is just a function. It passes iff `func` does not throw anything. Upon failure it will terminate testing for the test suite it was called in.

```
#include <testpp/testpp.hpp>

void dumbFunc(int a, int b) {
    throw (a + b);
}

D_TEST(expect_does_not_throw) {
    EXPECT_DOES_NOT_THROW(dumbFunc(40, 2)); //fails
    EXPECT_DOES_NOT_THROW([&]() { }); //passes
}
```

### EXPECT_THROWS_MSG()
`EXPECT_THROWS_MSG(func, message)` takes in two parameters: a function and a message that should be thrown. It passes iff the function throws an error and the message of the thrown error is equal to the `message` parameter. Since C++ allows you to throw any type, this test will pass if you throw an `std::string` that is equal to the `message` parameter. Ie, you don't need to necessarily throw an `std::exception` with a `what()` that equals `message`.


```
#include <testpp/testpp.hpp>
#include <exceptional>
#include <string>

void dumbFunc() {
    throw 42;
}

void throwsException() {
    throw std::invalid_argument("This is a bad argument");
}

void throwString() {
    throw std::string("hi");
}

D_TEST(expect_throws_with_message) {
    EXPECT_THROWS_MSG(dumbFunc, "hi"); //fails
    EXPECT_THROWS_MSG(throwsException(), "This is a bad argument"); //passes
    EXPECT_THROWS_MSG(throwString, "hi"); //passes
}
```

## Isolation Tests
Isolation tests are tests that are to be run in isolation. As of now, only UNIX systems are supported for this type of testing (sorry Windows users, but I don't even have anything to compile or test it with. But since this IS open-source, I'll leave implementing Windows process isolation to the user). They are good for checking code beyond typical pass/fail behavior, namely how they run. It is also advised to run potentially dangerous code inside an isolation test. Because these tests run in a separate, they have a safeguard built in to be able to run for a maximum of 10 seconds (10000ms).

WARNING: These tests are VERY low level in execution, and their ability to perform depends on things such as compilation, content detection etc. These tests, ESPECIALLY the sanitizer tests should be operated with a grain of salt and accuracy/usefulness is not guaranteed. However, I am still pushing to main.

1. [Types of Execution Statuses](#types-of-execution-statuses)
2. [Types of Crash Types](#types-of-crash-types)
3. [Assert Death](#assert_death)
4. [Assert Segmentation Fault](#assert_segfault)
5. [Assert Abort](#assert_abort)
6. [Assert Fatal](#assert_fatal)
7. [Assert Nonfatal](#assert_nonfatal)
8. [Assert Success](#assert_success)
9. [Assert Failure](#assert_failure)
10. [Assert Nonzero Exit](#assert_nonzero_exit)
11. [Assert Exit Code](#assert_exitcode)
12. [Assert Completes](#assert_completes)
13. [Assert stdout Contains](#assert_stdout_contains)
14. [Assert stderr Contains](#assert_stderr_contains)
15. [Assert No stdout](#assert_no_stdout)
16. [Assert No stderr](#assert_no_stderr)
17. [Assert stdout Matches](#assert_stdout_matches)
18. [Assert stderr Matches](#assert_stderr_matches)
19. [Assert Address Sanitizer Failure](#assert_asan_failure)
20. [Assert No Address Sanitizer Failure](#assert_nasan_failure)
21. [Assert Undefined-Behavior Sanitizer Failure](#assert_ubsan_failure)
22. [Assert No Undefined-Behavior Sanitizer Failure](#assert_nubsan_failure)
23. [Assert Thread Sanitizer Failure](#assert_tsan_failure)
24. [Assert No Thread Sanitizer Failure](#assert_ntsan_failure)
25. [Assert Leak Sanitizer Failure](#assert_lsan_failure)
26. [Assert No Leak Sanitizer Failure](#assert_nlsan_failure)
27. [Assert Sanitizer Failure](#assert_san_failure)
28. [Assert No Sanitizer Failure](#assert_nsan_failure)
29. [Assert Timeout](#assert_timeout)
30. [Assert Completes Within](#assert_completes_within)
31. [Assert Execution Status](#assert_status)
32. [Assert Crash Type](#assert_crash_type)
33. [Assert Signal](#assert_signal)
34. [Assert Killed](#assert_killed)
35. [Expect Death](#expect_death)
36. [Expect Segmentation Fault](#expect_segfault)
37. [Expect Abort](#expect_abort)
38. [Expect Fatal](#expect_fatal)
39. [Expect Nonfatal](#expect_nonfatal)
40. [Expect Success](#expect_success)
41. [Expect Failure](#expect_failure)
42. [Expect Nonzero Exit](#expect_nonzero_exit)
43. [Expect Exit Code](#expect_exitcode)
44. [Expect Completes](#expect_completes)
45. [Expect stdout Contains](#expect_stdout_contains)
46. [Expect stderr Contains](#expect_stderr_contains)
47. [Expect No stdout](#expect_no_stdout)
48. [Expect No stderr](#expect_no_stderr)
49. [Expect stdout Matches](#expect_stdout_matches)
50. [Expect stderr Matches](#expect_stderr_matches)
51. [Expect Address Sanitizer Failure](#expect_asan_failure)
52. [Expect No Address Sanitizer Failure](#expect_nasan_failure)
53. [Expect Undefined-Behavior Sanitizer Failure](#expect_ubsan_failure)
54. [Expect No Undefined-Behavior Sanitizer Failure](#expect_nubsan_failure)
55. [Expect Thread Sanitizer Failure](#expect_tsan_failure)
56. [Expect No Thread Sanitizer Failure](#expect_ntsan_failure)
57. [Expect Leak Sanitizer Failure](#expect_lsan_failure)
58. [Expect No Leak Sanitizer Failure](#expect_nlsan_failure)
59. [Expect Sanitizer Failure](#expect_san_failure)
60. [Expect No Sanitizer Failure](#expect_nsan_failure)
61. [Expect Timeout](#expect_timeout)
62. [Expect Completes Within](#expect_completes_within)
63. [Expect Execution Status](#expect_status)
64. [Expect Crash Type](#expect_crash_type)
65. [Expect Signal](#expect_signal)
66. [Expect Killed](#expect_killed)

### Types of Execution Statuses

NOTRUN - The test wasn't run
COMPLETED - The test completed normally
CRASHED - The test crashed
TIMEDOUT - The test ran for too long
LAUNCHFAIL - fork() failed
COMFAIL - Reading from stdout/stderr/creating a pipe failed
FRAMEWORKERR - There was an internal framework error
SANFAIL - There was a sanitizer failure

### Types of Crash Types

NOCRASH - The test didn't crash
SEGFAULT - The test had a segmentation fault
ACCESSVIOLATION - The test had an access violation
ABORT - The test was aborted
ZERODIV - The test tried to divide by zero
ILLINSTR - The test tried to run an illegal instruction
BUSERR - There was a bus error
FLOATPOINT - There was a floating point exception
TRAP - There was a trap
KILLED - The test was killed
UNKNOWN - The test crashed for an unknown reason

### ASSERT_DEATH()
`ASSERT_DEATH(func)` takes in one parameter: a function. It passes if the subprocess exits with a status of `COMPLETED` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_SEGFAULT()
`ASSERT_SEGFAULT(func)` takes in one parameter: a function. It passes if the subprocess exits with a crash type of `SEGFAULT` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_ABORT()
`ASSERT_ABORT(func)` takes in one parameter: a function. It passes if the subprocess exits with a crash type of `ABORT` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_FATAL()
`ASSERT_FATAL(func)` takes in one parameter: a function. It passes if the subprocess exits with a status of `COMPLETED` and a crash type of `NONE` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_NONFATAL()
`ASSERT_NONFATAL(func)` takes in one parameter: a function. It passes if the subprocess exits with a status that isn't `COMPLETED` or a crash type that isn't none `NONE` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_SUCCESS()
`ASSERT_SUCCESS(func)` takes in one parameter: a function. It passes if the subprocess exits with exit code `EXIT_SUCCESS` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_FAILURE()
`ASSERT_FAILURE(func)` takes in one parameter: a function. It passes if the subprocess exits with exit code `EXIT_FAILURE` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_NONZERO_EXIT()
`ASSERT_NONZERO_EXIT(func)` takes in one parameter: a function. It passes if the subprocess exits with a nonzero exit code and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_EXITCODE()
`ASSERT_NONZERO_EXIT(func, code)` takes in two parameters: a function, and an integer exit code. It passes if the subprocess exits with an exit code equal to `code` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_COMPLETES()
`ASSERT_COMPLETES(func)` takes in one parameter: a function. It passes if the subprocess exits with a status of `COMPLETED` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_STDOUT_CONTAINS()
`ASSERT_STDOUT_CONTAINS(func, content)` takes in two parameters: a function, and a string of content. It passes if the subprocess's `stdout` output contains `content` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_STDERR_CONTAINS()
`ASSERT_STDERR_CONTAINS(func, content)` takes in two parameters: a function, and a string of content. It passes if the subprocess's `stderr` output contains `content` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_NO_STDOUT()
`ASSERT_NO_STDOUT(func)` takes in one parameter: a function. It passes if the subprocess's `stdout` output is empty and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_NO_STDERR()
`ASSERT_NO_STDERR(func)` takes in one parameter: a function. It passes if the subprocess's `stderr` output is empty and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_STDOUT_MATCHES()
`ASSERT_STDOUT_MATCHES(func, content)` takes in two parameters: a function, and a string of content. It passes if the subprocess's `stderr` output matches `content` exactly and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_STDERR_MATCHES()
`ASSERT_STDERR_CONTAINS(func, content)` takes in two parameters: a function, and a string of content. It passes if the subprocess's `stderr` output matches `content` exactly and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_ASAN_FAILURE()
`ASSERT_ASAN_FAILURE(func)` takes in one parameter: a function. It passes if the Address Sanitizer reports an error and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_NASAN_FAILURE()
`ASSERT_NASAN_FAILURE(func)` takes in one parameter: a function. It passes if the Address Sanitizer does not report an error and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_UBSAN_FAILURE()
`ASSERT_UBSAN_FAILURE(func)` takes in one parameter: a function. It passes if the Undefined-Behavior Sanitizer reports an error and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_NUBSAN_FAILURE()
`ASSERT_NUBSAN_FAILURE(func)` takes in one parameter: a function. It passes if the Undefined-Behavior Sanitizer does not report an error and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_TSAN_FAILURE()
`ASSERT_TSAN_FAILURE(func)` takes in one parameter: a function. It passes if the Thread Sanitizer reports an error and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_NTSAN_FAILURE()
`ASSERT_NTSAN_FAILURE(func)` takes in one parameter: a function. It passes if the Thread Sanitizer does not report an error and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_LSAN_FAILURE()
`ASSERT_LSAN_FAILURE(func)` takes in one parameter: a function. It passes if the Leak Sanitizer reports an error and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_NLSAN_FAILURE()
`ASSERT_NLSAN_FAILURE(func)` takes in one parameter: a function. It passes if the Leak Sanitizer does not report an error and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_SAN_FAILURE()
`ASSERT_SAN_FAILURE(func)` takes in one parameter: a function. It passes if the any Sanitizer reports an error and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_NSAN_FAILURE()
`ASSERT_NSAN_FAILURE(func)` takes in one parameter: a function. It passes if the no Sanitizer does not report an error and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_TIMEOUT()
`ASSERT_TIMEOUT(func, timeoutMs)` takes in two parameters: a function, and an amount of time in milliseconds. It passes if the subprocess takes longer to complete than `timeoutMs` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_COMPLETES_WITHIN()
`ASSERT_COMPLETES_WITHIN(func, timeoutMs)` takes in two parameters: a function, and an amount of time in milliseconds. It passes if the subprocess finishes in less time than `timeoutMs` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_STATUS()
`ASSERT_STATUS(func, status)` takes in two parameters: a function, and an [Execution Status](#types-of-execution-statuses). It passes if the subprocess finishes with an Execution Status that matches `status` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_CRASH_TYPE()
`ASSERT_CRASH_TYPE(func, type)` takes in two parameters: a function, and a [Crash Type](#types-of-crash-types). It passes if the subprocess finishes with a Crash Type that matches `type` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_SIGNAL()
`ASSERT_SIGNAL(func, signal)` takes in two parameters: a function, and an exit signal. It passes if the subprocess finishes with a NATIVE (for if Windows process isolation is ever added) execution signal that matches `signal` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### ASSERT_KILLED()
`ASSERT_KILLED(func)` takes in one parameter: a function. It passes if the subprocess finishes with Crash Type `KILLED` and fails otherwise. Upon failure it will terminate testing for the test suite it was called in.

### EXPECT_DEATH()
`EXPECT_DEATH(func)` takes in one parameter: a function. It passes if the subprocess exits with a status of `COMPLETED` and fails otherwise.

### EXPECT_SEGFAULT()
`EXPECT_SEGFAULT(func)` takes in one parameter: a function. It passes if the subprocess exits with a crash type of `SEGFAULT` and fails otherwise.

### EXPECT_ABORT()
`EXPECT_ABORT(func)` takes in one parameter: a function. It passes if the subprocess exits with a crash type of `ABORT` and fails otherwise.

### EXPECT_FATAL()
`EXPECT_FATAL(func)` takes in one parameter: a function. It passes if the subprocess exits with a status of `COMPLETED` and a crash type of `NONE` and fails otherwise.

### EXPECT_NONFATAL()
`EXPECT_NONFATAL(func)` takes in one parameter: a function. It passes if the subprocess exits with a status that isn't `COMPLETED` or a crash type that isn't none `NONE` and fails otherwise.

### EXPECT_SUCCESS()
`EXPECT_SUCCESS(func)` takes in one parameter: a function. It passes if the subprocess exits with exit code `EXIT_SUCCESS` and fails otherwise.

### EXPECT_FAILURE()
`EXPECT_FAILURE(func)` takes in one parameter: a function. It passes if the subprocess exits with exit code `EXIT_FAILURE` and fails otherwise.

### EXPECT_NONZERO_EXIT()
`EXPECT_NONZERO_EXIT(func)` takes in one parameter: a function. It passes if the subprocess exits with a nonzero exit code and fails otherwise.

### EXPECT_EXITCODE()
`EXPECT_NONZERO_EXIT(func, code)` takes in two parameters: a function, and an integer exit code. It passes if the subprocess exits with an exit code equal to `code` and fails otherwise.

### EXPECT_COMPLETES()
`EXPECT_COMPLETES(func)` takes in one parameter: a function. It passes if the subprocess exits with a status of `COMPLETED` and fails otherwise.

### EXPECT_STDOUT_CONTAINS()
`EXPECT_STDOUT_CONTAINS(func, content)` takes in two parameters: a function, and a string of content. It passes if the subprocess's `stdout` output contains `content` and fails otherwise.

### EXPECT_STDERR_CONTAINS()
`EXPECT_STDERR_CONTAINS(func, content)` takes in two parameters: a function, and a string of content. It passes if the subprocess's `stderr` output contains `content` and fails otherwise.

### EXPECT_NO_STDOUT()
`EXPECT_NO_STDOUT(func)` takes in one parameter: a function. It passes if the subprocess's `stdout` output is empty and fails otherwise.

### EXPECT_NO_STDERR()
`EXPECT_NO_STDERR(func)` takes in one parameter: a function. It passes if the subprocess's `stderr` output is empty and fails otherwise.

### EXPECT_STDOUT_MATCHES()
`EXPECT_STDOUT_MATCHES(func, content)` takes in two parameters: a function, and a string of content. It passes if the subprocess's `stderr` output matches `content` exactly and fails otherwise.

### EXPECT_STDERR_MATCHES()
`EXPECT_STDERR_CONTAINS(func, content)` takes in two parameters: a function, and a string of content. It passes if the subprocess's `stderr` output matches `content` exactly and fails otherwise.

### EXPECT_ASAN_FAILURE()
`EXPECT_ASAN_FAILURE(func)` takes in one parameter: a function. It passes if the Address Sanitizer reports an error and fails otherwise.

### EXPECT_NASAN_FAILURE()
`EXPECT_NASAN_FAILURE(func)` takes in one parameter: a function. It passes if the Address Sanitizer does not report an error and fails otherwise.

### EXPECT_UBSAN_FAILURE()
`EXPECT_UBSAN_FAILURE(func)` takes in one parameter: a function. It passes if the Undefined-Behavior Sanitizer reports an error and fails otherwise.

### EXPECT_NUBSAN_FAILURE()
`EXPECT_NUBSAN_FAILURE(func)` takes in one parameter: a function. It passes if the Undefined-Behavior Sanitizer does not report an error and fails otherwise.

### EXPECT_TSAN_FAILURE()
`EXPECT_TSAN_FAILURE(func)` takes in one parameter: a function. It passes if the Thread Sanitizer reports an error and fails otherwise.

### EXPECT_NTSAN_FAILURE()
`EXPECT_NTSAN_FAILURE(func)` takes in one parameter: a function. It passes if the Thread Sanitizer does not report an error and fails otherwise.

### EXPECT_LSAN_FAILURE()
`EXPECT_LSAN_FAILURE(func)` takes in one parameter: a function. It passes if the Leak Sanitizer reports an error and fails otherwise.

### EXPECT_NLSAN_FAILURE()
`EXPECT_NLSAN_FAILURE(func)` takes in one parameter: a function. It passes if the Leak Sanitizer does not report an error and fails otherwise.

### EXPECT_SAN_FAILURE()
`EXPECT_SAN_FAILURE(func)` takes in one parameter: a function. It passes if the any Sanitizer reports an error and fails otherwise.

### EXPECT_NSAN_FAILURE()
`EXPECT_NSAN_FAILURE(func)` takes in one parameter: a function. It passes if the no Sanitizer does not report an error and fails otherwise.

### EXPECT_TIMEOUT()
`EXPECT_TIMEOUT(func, timeoutMs)` takes in two parameters: a function, and an amount of time in milliseconds. It passes if the subprocess takes longer to complete than `timeoutMs` and fails otherwise.

### EXPECT_COMPLETES_WITHIN()
`EXPECT_COMPLETES_WITHIN(func, timeoutMs)` takes in two parameters: a function, and an amount of time in milliseconds. It passes if the subprocess finishes in less time than `timeoutMs` and fails otherwise.

### EXPECT_STATUS()
`EXPECT_STATUS(func, status)` takes in two parameters: a function, and an [Execution Status](#types-of-execution-statuses). It passes if the subprocess finishes with an Execution Status that matches `status` and fails otherwise.

### EXPECT_CRASH_TYPE()
`EXPECT_CRASH_TYPE(func, type)` takes in two parameters: a function, and a [Crash Type](#types-of-crash-types). It passes if the subprocess finishes with a Crash Type that matches `type` and fails otherwise.

### EXPECT_SIGNAL()
`EXPECT_SIGNAL(func, signal)` takes in two parameters: a function, and an exit signal. It passes if the subprocess finishes with a NATIVE (for if Windows process isolation is ever added) execution signal that matches `signal` and fails otherwise.

### EXPECT_KILLED()
`EXPECT_KILLED(func)` takes in one parameter: a function. It passes if the subprocess finishes with Crash Type `KILLED` and fails otherwise.
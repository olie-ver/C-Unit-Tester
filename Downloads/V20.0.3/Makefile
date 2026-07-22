CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -I./include

SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build
RUN_DIR = build/bin

LIB = $(BUILD_DIR)/libtester.a
TARGET = $(RUN_DIR)/runTests

SRC_FILES := $(shell find $(SRC_DIR) -name "*.cpp")
TEST_FILES := $(shell find $(TEST_DIR) -name "*.cpp")

# Object files
SRC_OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/obj/%.o,$(SRC_FILES))
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/tests_%.o,$(TEST_FILES))

clean:
	rm -rf $(BUILD_DIR)

run: 
	./$(TARGET) --v=default

test:
	./$(TARGET) --v=failOnly --skip=timeout

json: 
	./$(TARGET) --v=default --skip=timeout --json output.json

xml:
	./$(TARGET) --v=default --skip=timeout --xml output.xml

1: 
	./$(TARGET) --v=default --t=1

2:
	./$(TARGET) --v=default --t=2

3:
	./$(TARGET) --v=default --t=3

4:
	./$(TARGET) --v=default --t=4

5:
	./$(TARGET) --v=default --t=5

6:
	./$(TARGET) --v=default --t=6

7:
	./$(TARGET) --v=default --t=7

8:
	./$(TARGET) --v=default --t=8
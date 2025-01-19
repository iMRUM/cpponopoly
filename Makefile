CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include
TEST_FLAGS = -lgtest -lgtest_main -pthread

SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build
TEST_BUILD_DIR = $(BUILD_DIR)/tests

TEST_SRCS = $(wildcard $(TEST_DIR)/model/squares/*.cpp)
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(TEST_BUILD_DIR)/%.o)

.PHONY: all clean test

all: test

$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_OBJS)
	@mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(TEST_OBJS) -o $(TEST_BUILD_DIR)/run_tests $(TEST_FLAGS)
	./$(TEST_BUILD_DIR)/run_tests

clean:
	rm -rf $(BUILD_DIR)
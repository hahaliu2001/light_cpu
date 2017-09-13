# file      test.mk
# brief     

TARGET_EXEC := test.o

BUILD_DIR ?= ./build
TEST_DIRS  := ./test
UNITY_DIR  := ./test_vendor/unity
UNITY_FIXTURE_DIR  := ./test_vendor/unity_fixture

SRCS += $(shell find $(TEST_DIRS) -name *.cpp -or -name *.c -or -name *.s)
SRCS += $(shell find $(UNITY_DIR) -name *.cpp -or -name *.c -or -name *.s)
SRCS += $(shell find $(UNITY_FIXTURE_DIR) -name *.cpp -or -name *.c -or -name *.s)

INC_DIRS += $(shell find $(TEST_DIRS) -type d)
INC_DIRS += $(shell find $(UNITY_DIR) -type d)
INC_DIRS += $(shell find $(UNITY_FIXTURE_DIR) -type d)

SYMBOLS +=

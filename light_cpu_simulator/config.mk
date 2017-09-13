# file      config.mk
# brief     set 

TARGET_EXEC ?= cpu_core.out

BUILD_DIR ?= ./build
SRC_DIRS  := ./src

SRCS += $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
ifeq ($(TYPE), test)
	SRCS := $(filter-out $(SRC_DIRS)/main.c, $(SRCS))
endif

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS += $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

SYMBOLS +=
SYMS += $(patsubst %,-D%,$(SYMBOLS))

CFLAGS += $(INC) $(SYMS) -g -Wall -Werror -fmessage-length=0
CFLAGS += -Wno-format-extra-args -Wno-unused-result -Wformat=0

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)
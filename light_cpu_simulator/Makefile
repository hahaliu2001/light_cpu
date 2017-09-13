# Makefile-based project build system

include tools.mk

.PHONY: default

ifneq ($(TYPE), test)
default: clean all
else
default: clean test
include test.mk
endif

include config.mk

TARGETFILE = $(BUILD_DIR)/$(TARGET_EXEC)
.PHONY: all
all:: $(BUILD_DIR)/$(TARGET_EXEC)
	@echo "make all "
	$(BUILD_DIR)/$(TARGET_EXEC)

.PHONY: test
test:: $(BUILD_DIR)/$(TARGET_EXEC)
	@echo "run test"
	$(BUILD_DIR)/$(TARGET_EXEC)
	
.PHONY: clean
clean:
	$(RM) $(BUILD_DIR)


	

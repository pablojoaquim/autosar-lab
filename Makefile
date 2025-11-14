# ===============================
# Makefile for Windows + MinGW
# ===============================
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# ===============================
# Source directories
# EDIT ONLY HERE!!!!!!!!!!!
# ===============================
SRC_DIRS  = src\main \
			src\RTE \
			src\SWC \
			src\SWC\SpeedDisplay \
			src\SWC\SpeedSensor \
			src\BSW
TEST_DIR = test
MAIN = src/main/main.c

# ===============================
# Windows \ → /
# ===============================
SRC_DIRS := $(subst \,/,$(SRC_DIRS))

# ===============================
# Specific files to add
# ===============================
TEST_FILES = $(wildcard $(TEST_DIR)/test_*.c)

# ===============================
# Search for all the .c inside 
# the src directories
# ===============================
SRC_FILES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

# ===============================
# Automatic Includes
# ===============================
CFLAGS += $(foreach dir,$(SRC_DIRS), -I$(dir))

# ===============================
# Outputs
# ===============================
TARGET = main.exe
TEST_TARGET = tests.exe

# =================================
# Compiling the Main application
# =================================
all: $(TARGET)

$(TARGET): $(SRC_FILES)
	$(CC) $(CFLAGS) $(SRC_FILES) -o $(TARGET)
	@echo ==== Compilation completed: $(TARGET) ====

# =================================
# Compiling tests (without main.c)
# =================================
tests: $(filter-out $(MAIN),$(SRC_FILES)) $(TEST_FILES)
	$(CC) $(CFLAGS) $(filter-out $(MAIN),$(SRC_FILES)) $(TEST_FILES) -o $(TEST_TARGET)
	@echo ==== Compilation completed: $(TEST_TARGET) ====

# =================================
# Execute tests
# =================================
run-tests: tests
	@echo ==== Executing tests ====
	@./$(TEST_TARGET)

# =================================
# Execute main application
# =================================
run: $(TARGET)
	@echo ==== Executing Application ====
	@./$(TARGET)

# =================================
# Clean everything
# =================================
clean:
	@echo ==== Cleaning binnaries ====
	@if exist "$(TARGET)" ( del /Q "$(TARGET)" )
	@if exist "$(subst /,\\,$(TEST_TARGET))" ( del /Q "$(subst /,\\,$(TEST_TARGET))" )

# ============================================
# AUTOSAR Lab Makefile
# Extends existing katas-training Makefile
# ============================================

# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -std=c11 -g
LDFLAGS := -lrt -lpthread

# Directories
BUILD_DIR := build
AUTOSAR_BUILD_DIR := $(BUILD_DIR)/autosar
COVERAGE_DIR := $(BUILD_DIR)/coverage

# AUTOSAR source directories
AUTOSAR_BSW_DIR := src/autosar/bsw
AUTOSAR_RTE_DIR := src/autosar/rte
AUTOSAR_SWC_DIR := src/autosar/swc

# AUTOSAR include paths
AUTOSAR_INCLUDES := -Isrc/autosar/bsw/os \
                    -Isrc/autosar/bsw/com \
                    -Isrc/autosar/rte \
                    -Isrc/autosar/swc/template \
                    -Isrc/autosar/swc/kata_001

# AUTOSAR source files
AUTOSAR_BSW_SRCS := $(wildcard $(AUTOSAR_BSW_DIR)/os/*.c) \
                    $(wildcard $(AUTOSAR_BSW_DIR)/com/*.c)

AUTOSAR_RTE_SRCS := $(wildcard $(AUTOSAR_RTE_DIR)/*.c)

AUTOSAR_SWC_SRCS := $(wildcard $(AUTOSAR_SWC_DIR)/template/*.c) \
                    $(wildcard $(AUTOSAR_SWC_DIR)/kata_001/*.c)

AUTOSAR_MAIN_SRC := src/main.c

AUTOSAR_ALL_SRCS := $(AUTOSAR_BSW_SRCS) \
                    $(AUTOSAR_RTE_SRCS) \
                    $(AUTOSAR_SWC_SRCS) \
                    $(AUTOSAR_MAIN_SRC)

# Object files
AUTOSAR_OBJS := $(AUTOSAR_ALL_SRCS:%.c=$(AUTOSAR_BUILD_DIR)/%.o)

# Executable
AUTOSAR_EXE := $(AUTOSAR_BUILD_DIR)/autosar_lab

# ============================================
# Main targets
# ============================================

.PHONY: all clean help
.PHONY: autosar autosar-run autosar-clean autosar-rebuild
.PHONY: autosar-tests autosar-coverage autosar-debug

# Default target
all: help

# ============================================
# AUTOSAR Lab targets
# ============================================

autosar: $(AUTOSAR_EXE)
	@echo "✓ AUTOSAR Lab built successfully!"

$(AUTOSAR_EXE): $(AUTOSAR_OBJS)
	@echo "Linking AUTOSAR Lab..."
	@mkdir -p $(dir $@)
	$(CC) $(AUTOSAR_OBJS) $(LDFLAGS) -o $@

# Compile C source files
$(AUTOSAR_BUILD_DIR)/%.o: %.c
	@echo "Compiling $<..."
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(AUTOSAR_INCLUDES) -c $< -o $@

autosar-run: autosar
	@echo ""
	@echo "Running AUTOSAR Lab..."
	@echo "======================================"
	@$(AUTOSAR_EXE)

autosar-clean:
	@echo "Cleaning AUTOSAR build artifacts..."
	@rm -rf $(AUTOSAR_BUILD_DIR)
	@echo "✓ Clean complete"

autosar-rebuild: autosar-clean autosar

# ============================================
# Testing targets
# ============================================

autosar-tests:
	@echo "Running AUTOSAR unit tests..."
	@echo "Note: Add your unit tests in test/autosar/"
	@echo "TODO: Integrate with your test framework"

# ============================================
# Code coverage
# ============================================

COVERAGE_CFLAGS := $(CFLAGS) --coverage
COVERAGE_LDFLAGS := $(LDFLAGS) --coverage

autosar-coverage: CFLAGS := $(COVERAGE_CFLAGS)
autosar-coverage: LDFLAGS := $(COVERAGE_LDFLAGS)
autosar-coverage: autosar-clean autosar
	@echo ""
	@echo "Running with coverage..."
	@timeout 2s $(AUTOSAR_EXE) || true
	@echo ""
	@echo "Generating coverage report..."
	@mkdir -p $(COVERAGE_DIR)
	@gcovr -r . --html --html-details -o $(COVERAGE_DIR)/coverage.html \
		--exclude 'test/*' --exclude 'build/*'
	@echo "✓ Coverage report generated: $(COVERAGE_DIR)/coverage.html"

# ============================================
# Debug targets
# ============================================

autosar-debug: CFLAGS += -O0 -DDEBUG
autosar-debug: autosar-rebuild
	@echo "Debug build complete. Run with: gdb $(AUTOSAR_EXE)"

# ============================================
# Development helpers
# ============================================

# Create new kata from template
new-kata:
	@read -p "Enter kata number (e.g., 002): " num; \
	kata_dir="src/autosar/swc/kata_$$num"; \
	if [ -d "$$kata_dir" ]; then \
		echo "Error: Kata $$num already exists!"; \
		exit 1; \
	fi; \
	echo "Creating new kata: $$num"; \
	cp -r src/autosar/swc/template $$kata_dir; \
	cd $$kata_dir && \
	mv Swc_Template.h Swc_Kata$$num.h && \
	mv Swc_Template.c Swc_Kata$$num.c && \
	sed -i "s/Template/Kata$$num/g" *.h *.c && \
	sed -i "s/TEMPLATE/KATA$$num/g" *.h *.c; \
	echo "✓ Kata $$num created in $$kata_dir"; \
	echo "  Next steps:"; \
	echo "  1. Edit Swc_Kata$$num.c with your kata solution"; \
	echo "  2. Add to Makefile AUTOSAR_SWC_SRCS"; \
	echo "  3. Register in main.c"

# List all katas
list-katas:
	@echo "Available katas:"
	@ls -1d src/autosar/swc/kata_* 2>/dev/null | sed 's|src/autosar/swc/||' || echo "  No katas created yet"
	@echo ""
	@echo "Template available at: src/autosar/swc/template"

# ============================================
# Help
# ============================================

help:
	@echo "AUTOSAR Lab - Kata Training System"
	@echo ""
	@echo "Available targets:"
	@echo "  make autosar          - Build AUTOSAR lab"
	@echo "  make autosar-run      - Build and run AUTOSAR lab"
	@echo "  make autosar-clean    - Clean build artifacts"
	@echo "  make autosar-rebuild  - Clean and rebuild"
	@echo "  make autosar-tests    - Run unit tests"
	@echo "  make autosar-coverage - Generate coverage report"
	@echo "  make autosar-debug    - Build with debug symbols"
	@echo ""
	@echo "Development helpers:"
	@echo "  make new-kata         - Create new kata from template"
	@echo "  make list-katas       - List all created katas"
	@echo ""
	@echo "Example workflow:"
	@echo "  1. make new-kata      (create kata_002)"
	@echo "  2. Edit kata_002/Swc_Kata002.c"
	@echo "  3. make autosar-run   (build and test)"
	@echo "  4. make autosar-coverage (check coverage)"

# ============================================
# Dependency generation
# ============================================

-include $(AUTOSAR_OBJS:.o=.d)

$(AUTOSAR_BUILD_DIR)/%.d: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(AUTOSAR_INCLUDES) -MM -MT $(@:.d=.o) $< -MF $@
# PATHS - to search for the headers and source files
HEADERS_1 = ../../../
HEADERS_2 = 
HEADERS_3 = 

SOURCE_1 = ../../../
SOURCE_2 = 
SOURCE_3 = 

INCLUDES = $(HEADERS_1) $(HEADERS_2) $(HEADERS_3)
SOURCE = $(SOURCE_1) $(SOURCE_2) $(SOURCE_3)

vpath %.h $(INCLUDES)
vpath %.c $(SOURCE)

# COMPILER - with flags and libraries to link
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror $(foreach dir, $(INCLUDES), -I$(dir))
LDLIBS = -lbcunit

# EXECUTABLE - the final binary file
BUILD_DIR = ./build
BIN = test_selection_sort
TARGET = $(BUILD_DIR)/$(BIN)

# FILES
PWD_HEADERS := $(wildcard *.h)
PWD_SOURCES := $(wildcard *.c)
TOOLS_HEADERS := tools/printing.h tools/comparison.h tools/general.h
TOOLS_SOURCES := tools/printing.c tools/comparison.c tools/general.c
TEST_HEADERS := tests/shared_test.h tests/comparison_sort_tests.h
TEST_SOURCES := tests/shared_test.c tests/comparison_sort_tests.c
SORT_HEADERS := algorithms/selection_sort.h
SORT_SOURCES := algorithms/selection_sort.c
DS_HEADERS :=
DS_SOURCES :=
HEADERS = $(PWD_HEADERS) $(TOOLS_HEADERS) $(TEST_HEADERS) $(SORT_HEADERS) $(DS_HEADERS)
SOURCES = $(PWD_SOURCES) $(TOOLS_SOURCES) $(TEST_SOURCES) $(SORT_SOURCES) $(DS_SOURCES)
OBJECTS := $(SOURCES:%.c=$(BUILD_DIR)/%.o)
DEPENDS = $(OBJECTS:%.o=%.d)

# TARGETS
.PHONY: all clean rebuild test

all: $(TARGET)

$(TARGET): $(OBJECTS) $(HEADERS) Makefile
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDLIBS) -o $(TARGET)

-include $(DEPENDS)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	$(RM) $(TARGET) $(OBJECTS)

rebuild: clean $(TARGET)

test:
	@echo "EXECUTABLES = ${TARGET}"
	@echo "OBJECTS = ${OBJECTS}"

# directory for source files
SRC_DIR = src
OUT_DIR = out

# compiler and flags
CC = gcc
CFLAGS = -Wall -std=c99

# font and object files
SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(OUT_DIR)/%.o, $(SOURCES))
HEADERS := $(wildcard $(SRC_DIR)/*.h)

# executable name
EXECUTABLE = $(OUT_DIR)/main

# zip file name
ZIP_FILE = project.zip

# file list to zip (including .h files from SRC_DIR now)
ZIP_FILES := $(SOURCES) $(HEADERS) Makefile

# compile rules
$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# links
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

# create output directory
$(shell mkdir -p $(OUT_DIR))

# temporary files cleaner
clean:
	rm -rf $(OUT_DIR) $(EXECUTABLE) $(ZIP_FILE)

# execute program
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# zip creation
zip:
	zip -r $(ZIP_FILE) $(ZIP_FILES)

# compile
all: $(EXECUTABLE)

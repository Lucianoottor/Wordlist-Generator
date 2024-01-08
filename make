# Makefile for wlsgen

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
DEB_DIR = debian

# Name of the binary
TARGET = wlsgen

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Debian package files
DEB_CONTROL = $(DEB_DIR)/control
DEB_COMPAT = $(DEB_DIR)/compat
DEB_RULES = $(DEB_DIR)/rules
DEB_CHANGELOG = $(DEB_DIR)/changelog
DEB_INSTALL = $(DEB_DIR)/install

# Default target
all: $(TARGET)

# Build the binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $^

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean up
clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/$(TARGET)

# Debian package target
deb: clean $(DEB_CONTROL) $(DEB_COMPAT) $(DEB_RULES) $(DEB_CHANGELOG) $(DEB_INSTALL)
	dpkg-buildpackage -us -uc

# Install locally (for testing)
install: all
	cp $(BUILD_DIR)/$(TARGET) /usr/local/bin/$(TARGET)

.PHONY: clean deb install

# Variables for directories and files
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
ASSETS_DIR = assets
INSTALL_DIR = /opt/fnaf3
APP_NAME = fnaf3.exe

# Source files
SRC_FILES = main.cpp graphics.cpp game.cpp objects.cpp audio.cpp
OBJ_FILES = $(SRC_FILES:%.cpp=$(BUILD_DIR)/%.o)

# Compiler and linker
CXX = g++
CXXFLAGS = -c
LDFLAGS = -lSDL2_mixer -lSDL2_image -lSDL2

all: compile link

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

# Link object files
link: $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) -o $(BIN_DIR)/$(APP_NAME) $(OBJ_FILES) $(LDFLAGS)

# Run the application
run: all
	$(BIN_DIR)/$(APP_NAME)

# Clean build and binary directories
clean:
	rm -f $(BUILD_DIR)/* $(BIN_DIR)/*

# Install the application
install:
	sudo mkdir -p $(INSTALL_DIR)/bin
	sudo mkdir -p $(INSTALL_DIR)/assets
	sudo cp $(BIN_DIR)/$(APP_NAME) $(INSTALL_DIR)/bin/
	sudo cp -r $(ASSETS_DIR)/* $(INSTALL_DIR)/assets/
	sudo cp icon.png $(INSTALL_DIR)/
	sudo cp fnaf3.desktop /usr/share/applications/

# Uninstall the application
uninstall:
	sudo rm -rf $(INSTALL_DIR)
	sudo rm /usr/share/applications/fnaf3.desktop

.PHONY: all compile link run clean install uninstall

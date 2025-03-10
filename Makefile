# Variables for directories and files
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
ASSETS_DIR = assets
INSTALL_DIR = /opt/fnaf3
APP_NAME = fnaf3

# Source files
SRC_FILES = main.cpp graphics.cpp game.cpp objects.cpp audio.cpp
OBJ_FILES = $(SRC_FILES:%.cpp=$(BUILD_DIR)/%.o)

# Platform-specific commands and settings
ifeq ($(OS),Windows_NT)
    MKDIR_P = if not exist $(subst /,\,$(1)) mkdir $(subst /,\,$(1))
    RM = del /Q
    CP = xcopy /s /i
    BIN_EXTENSION = .exe
    SDL_FLAGS = -static-libgcc -static-libstdc++ -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
else
    MKDIR_P = mkdir -p $(1)
    RM = rm -f
    CP = cp -r
    BIN_EXTENSION =
    SDL_FLAGS = -lSDL2_mixer -lSDL2_image -lSDL2
endif

# Compiler and linker
CXX = g++
CXXFLAGS = -c
LDFLAGS = $(SDL_FLAGS)

all: compile link copy_assets

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(call MKDIR_P,$(BUILD_DIR))
	$(CXX) $(CXXFLAGS) -o $@ $<

# Link object files
link: $(OBJ_FILES)
	@$(call MKDIR_P,$(BIN_DIR))
	$(CXX) -o $(BIN_DIR)/$(APP_NAME)$(BIN_EXTENSION) $(OBJ_FILES) $(LDFLAGS)

# Copy assets to bin directory
copy_assets:
	@$(call MKDIR_P,$(BIN_DIR)/assets)
	$(CP) $(ASSETS_DIR)/* $(BIN_DIR)/assets/

# Run the application
run: all
	$(BIN_DIR)/$(APP_NAME)$(BIN_EXTENSION)

# Clean build and binary directories
clean:
	$(RM) $(BUILD_DIR)/* $(BIN_DIR)/*

# Install the application
install:
	$(call MKDIR_P,$(INSTALL_DIR)/bin)
	$(call MKDIR_P,$(INSTALL_DIR)/assets)
	$(CP) $(BIN_DIR)/$(APP_NAME)$(BIN_EXTENSION) $(INSTALL_DIR)/bin/
	$(CP) $(ASSETS_DIR)/* $(INSTALL_DIR)/assets/
	$(CP) icon.png $(INSTALL_DIR)/
	$(CP) fnaf3.desktop /usr/share/applications/

# Uninstall the application
uninstall:
	$(RM) /usr/share/applications/fnaf3.desktop
	$(RM) $(INSTALL_DIR)/bin/$(APP_NAME)$(BIN_EXTENSION)
	$(RM) $(INSTALL_DIR)/icon.png
	$(RM) /$(INSTALL_DIR)/assets/*

.PHONY: all compile link run clean install uninstall copy_assets


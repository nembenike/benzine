CC = gcc
CFLAGS = -Wall -Wextra $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lm

# Directory structure
ENGINE_DIR = src/benzine
GAME_DIR = src/game
BIN_DIR = bin
OBJ_DIR = bin/obj

# Make sure the directories exist
$(shell mkdir -p $(BIN_DIR))
$(shell mkdir -p $(OBJ_DIR))

# Source and object files
ENGINE_SOURCES = $(wildcard $(ENGINE_DIR)/*.c)
GAME_SOURCES = $(wildcard $(GAME_DIR)/*.c)
ALL_SOURCES = $(ENGINE_SOURCES) $(GAME_SOURCES)

ENGINE_OBJECTS = $(ENGINE_SOURCES:$(ENGINE_DIR)/%.c=$(OBJ_DIR)/%.o)
GAME_OBJECTS = $(GAME_SOURCES:$(GAME_DIR)/%.c=$(OBJ_DIR)/game_%.o)
ALL_OBJECTS = $(ENGINE_OBJECTS) $(GAME_OBJECTS)

EXECUTABLE = $(BIN_DIR)/game

# Include directories
INCLUDES = -I$(ENGINE_DIR) -I$(GAME_DIR)

# Main target
all: $(EXECUTABLE)

# Linking
$(EXECUTABLE): $(ALL_OBJECTS)
	@echo "Linking..."
	@$(CC) $(ALL_OBJECTS) -o $@ $(LDFLAGS)
	@echo "Build complete: $(EXECUTABLE)"

# Compilation rules
$(OBJ_DIR)/%.o: $(ENGINE_DIR)/%.c
	@echo "Compiling engine: $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/game_%.o: $(GAME_DIR)/%.c
	@echo "Compiling game: $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean build files
clean:
	@echo "Cleaning..."
	@rm -rf $(OBJ_DIR) $(EXECUTABLE)
	@echo "Clean complete"

# Rebuild everything
rebuild: clean all

# Debug target
debug: CFLAGS += -g -DDEBUG
debug: all

# Release target
release: CFLAGS += -O2
release: all

# Print variables for debugging
print-%:
	@echo $* = $($*)

# List all source files
list-sources:
	@echo "Engine sources:"
	@echo $(ENGINE_SOURCES)
	@echo "Game sources:"
	@echo $(GAME_SOURCES)

# Make these commands always execute
.PHONY: all clean rebuild debug release list-sources

# Dependencies
-include $(ALL_OBJECTS:.o=.d)

# Generate dependency files
$(OBJ_DIR)/%.d: $(ENGINE_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -MM -MF $@ -MT "$(OBJ_DIR)/$*.o $@" $<

$(OBJ_DIR)/game_%.d: $(GAME_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -MM -MF $@ -MT "$(OBJ_DIR)/game_$*.o $@" $<
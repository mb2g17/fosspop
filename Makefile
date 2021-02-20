CC					 := em++
SDL2_FLAGS			 := -s USE_SDL=2
SDL2_IMAGE_FLAGS	 := -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]'
PRELOAD_ASSETS_FLAGS := --use-preload-plugins --preload-file assets

INCLUDE_DIR := include
SRC_DIR 	:= src

BUILD_DIR 	:= build
OUT_DIR 	:= $(BUILD_DIR)/out
DIST_DIR 	:= $(BUILD_DIR)/dist

OBJECTS := main.o game.o obj.o

all: clean dist

clean:
	rm -rf $(BUILD_DIR)

build: *.o

dist: $(OBJECTS)
	mkdir -p $(DIST_DIR)
	cp public/* $(DIST_DIR)
	$(CC) $(SDL2_FLAGS) $(SDL2_IMAGE_FLAGS) $(PRELOAD_ASSETS_FLAGS) \
		-o $(DIST_DIR)/index.js \
		$(OUT_DIR)/*.o

define build_lib
	mkdir -p $(OUT_DIR)
	$(CC) $(SDL2_FLAGS) $(SDL2_IMAGE_FLAGS) \
		-I$(INCLUDE_DIR) \
		-c -o $(OUT_DIR)/$(2) \
		$(1)
endef

obj.o: $(SRC_DIR)/game/obj.cpp
	$(call build_lib,$<,$@)

game.o: $(SRC_DIR)/game/game.cpp
	$(call build_lib,$<,$@)

main.o: $(SRC_DIR)/main.cpp
	$(call build_lib,$<,$@)

run:
	cd $(DIST_DIR) && http-server

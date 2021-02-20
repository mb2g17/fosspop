CC			:= emcc
SDL2_FLAGS	:= -s USE_SDL=2
SDL2_IMAGE_FLAGS	:= -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]'
PRELOAD_ASSETS_FLAGS := --use-preload-plugins --preload-file assets

INCLUDE_DIR := include
LIB_DIR 	:= lib
SRC_DIR 	:= src

BUILD_DIR 	:= build
OUT_DIR 	:= $(BUILD_DIR)/out
DIST_DIR 	:= $(BUILD_DIR)/dist

clean:
	rm -rf $(BUILD_DIR)

build: main.o game.o

dist: main.o game.o
	mkdir -p $(DIST_DIR)
	cp public/* $(DIST_DIR)
	$(CC) $(SDL2_FLAGS) $(SDL2_IMAGE_FLAGS) $(PRELOAD_ASSETS_FLAGS) \
		-o $(DIST_DIR)/index.js \
		$(OUT_DIR)/main.o $(OUT_DIR)/game.o

define build_lib
	mkdir -p $(OUT_DIR)
	$(CC) $(SDL2_FLAGS) $(SDL2_IMAGE_FLAGS) -I$(INCLUDE_DIR) -c -o $(OUT_DIR)/$(2) $(1)
endef

game.o: $(LIB_DIR)/game/game.cpp
	$(call build_lib,$(LIB_DIR)/game/game.cpp,game.o)

main.o: $(SRC_DIR)/main.cpp
	$(call build_lib,$(SRC_DIR)/main.cpp,main.o)

run:
	cd $(DIST_DIR) && http-server

CC := emcc
CC_FLAGS := -s USE_SDL=2 \
		-s USE_SDL_IMAGE=2 \
		-s SDL2_IMAGE_FORMATS='["png"]' \
		-o build/index.js \
		--use-preload-plugins \
		--preload-file assets

BUILD_DIR := build

clean:
	@echo Cleaning...
	if [ -d $(BUILD_DIR) ]; then rm -r build; fi

build:
	@echo Building...
	if [ ! -d $(BUILD_DIR) ]; then mkdir build; fi
	cp public/* $(BUILD_DIR)
	$(CC) src/main.cpp $(CC_FLAGS)

run:
	@echo Running...
	cd build && http-server

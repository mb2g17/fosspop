CC="emcc"
BUILD_DIR="./build"

clean:
	@echo Cleaning...
	if [ -d $(BUILD_DIR) ]; then rm -r build; fi

build:
	@echo Building...
	mkdir build
	emcc src/main.cpp \
		-s USE_SDL=2 \
		-s USE_SDL_IMAGE=2 \
		-s SDL2_IMAGE_FORMATS='["png"]' \
		-o build/index.html \
		--use-preload-plugins \
		--preload-file assets

run:
	@echo Running...
	cd build && http-server

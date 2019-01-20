# Change these for your platforms
CC=g++
MACOS_SDL_DIR=/Library/Frameworks
WINDOWS_SDL_DIR=/C/MinGW/SDL2.0.8
WINDOWS_SDL_DLL=$(WINDOWS_SDL_DIR)/bin/SDL2.dll


help:
	@cat build_subsystem/help.txt

bin: 
	mkdir bin

	# Windows only
	cp $(WINDOWS_SDL_DLL) bin/SDL2.dll



build: bin
	# MAC OS
	$(CC) src/Main.cpp -o bin/Main.o -F$(MACOS_SDL_DIR) -g -framework SDL2 -framework OpenGL -L /usr/local/lib/ -l GLEW -framework Cocoa -I $(MACOS_SDL_DIR)/SDL2.framework/Headers  -Wno-write-strings

	# Windows
	#$(CC) -o bin/Main.o src/Main.cpp -I$(WINDOWS_SDL_DIR)/include/SDL2 -L$(WINDOWS_SDL_DIR)/lib -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lglew32

run: build
	./bin/Main.o

clean:
	rm -rf bin
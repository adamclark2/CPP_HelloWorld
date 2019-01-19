help:
	@cat build_subsystem/help.txt

include build_subsystem/*.makefile

build: bin
	$(CC) src/Main.cpp -o bin/Main.o

run: build
	./bin/Main.o
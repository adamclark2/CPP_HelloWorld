# CPP_HelloWorld
Hello World c++ and SDL

# SDL Config
`SDL 2.0.8`

# Glew Config

    - Windows
        - Download `glew` https://sourceforge.net/projects/glew/
        - Put the headers in your mingw headers dir
        - Put the libs in your mingw libs dir
        - Put the binaries in your mingw libs dir

    - Mac
        - OK

# Makefile Config
    - Modify the makefile's `build: bin` target such that you are using `Mac` or `Windows` to compile
    - Modify te makefile's platform vars at the top if need be
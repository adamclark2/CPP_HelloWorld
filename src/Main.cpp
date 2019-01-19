
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "SDL.h"

#include "HelloClass.cpp"
#include "PlatformDetection.cpp"
#include "Render.cpp"

int main(int argc, char* argv[]){
    printf("Hello World\n");
    HelloClass* hi = new HelloClass();
        hi->printHi();
    delete hi;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        // Unrecoverable error, exit here.
        printf("SDL_Init failed: %s\n", SDL_GetError());
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    atexit(SDL_Quit);

    printf("\n\n");
    PlatformDetection* pd = new PlatformDetection();
    pd->printPlatform();
    delete pd;

    Render* r = new Render();
    r->doRender();
    delete r;
}
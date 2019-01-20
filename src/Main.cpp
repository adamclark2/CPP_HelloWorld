
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "SDL.h"
#include "GL/glew.h"

#include "PlatformDetection.cpp"
#include "Render.cpp"
#include "ErrorCheck.cpp"

SDL_Window* win = NULL;
SDL_GLContext glcontext = NULL;

void doInit(){
 if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        // Unrecoverable error, exit here.
        printf("SDL_Init failed: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    atexit(SDL_Quit);

    win = SDL_CreateWindow("Hello C++",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,250,100, SDL_WINDOW_OPENGL);
    if(win == NULL){
        printf("Window isn't created\n");
        exit(1);
    }

    glcontext = SDL_GL_CreateContext(win);
    glewInit();
    glViewport(0,0,250,100);
    checkGLError(__LINE__, __FILE__);
}

int main(int argc, char **argv){
    printf("Running Application\n--------------------------------\n");
    fflush(stdout);
    doInit();    

    PlatformDetection* pd = new PlatformDetection();
    pd->printPlatform();
    pd->showPlatform();
    delete pd;

    glGetError();
    checkGLError(__LINE__, __FILE__);
    Render* r = new Render();
    SDL_Event event;
    while (1) {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            break;
        }
        r->doRender();
        SDL_GL_SwapWindow(win);  
    }
    

    // Cleanup
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(win);
    delete r;

    exit(0);
}
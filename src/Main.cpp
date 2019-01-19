
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "SDL.h"
#include "gl/glew.h";

#include "PlatformDetection.cpp"
#include "Render.cpp"

SDL_Window* win = NULL;
SDL_GLContext glcontext = NULL;

void doInit(){
 if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        // Unrecoverable error, exit here.
        printf("SDL_Init failed: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Anti-Alias
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    atexit(SDL_Quit);

    win = SDL_CreateWindow("Hello C++",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,250,100, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
    if(win == NULL){
        printf("Window isn't created\n");
        exit(1);
    }

    glcontext = SDL_GL_CreateContext(win);
    glewInit();
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
}

int main(int argc, char **argv){
    printf("Running Application\n--------------------------------\n");
    fflush(stdout);
    doInit();    

    PlatformDetection* pd = new PlatformDetection();
    pd->printPlatform();
    pd->showPlatform();
    delete pd;

    SDL_ShowWindow(win);
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
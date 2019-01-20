
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
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, SDL_TRUE);

    atexit(SDL_Quit);

    win = SDL_CreateWindow("Hello C++",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,400, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if(win == NULL){
        printf("Window isn't created\n");
        exit(1);
    }

    glcontext = SDL_GL_CreateContext(win);
    glewInit();
    glViewport(0,0,800,400);
    checkGLError(__LINE__, __FILE__);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback((GLDEBUGPROC) &glDebugCallback, 0);
}

void cleanup(){
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(win);
}

int main(int argc, char **argv){
    printf("Running Application\n--------------------------------\n");
    fflush(stdout);
    doInit();
    printf("AFTER INIT*****\n\n");    

    FILE* f = fopen("src/frag.glsl", "r");
    if(f == NULL){
        printf("Shaders can't be found. Exiting!\n");
        cleanup();
        exit(1);
    }
    fclose(f);

    PlatformDetection* pd = new PlatformDetection();
    pd->printPlatform();
    pd->showPlatform();
    delete pd;

    glGetError();
    checkGLError(__LINE__, __FILE__);
    Render* r = new Render();
    SDL_Event event;
    float size[] = {800,400};
    while (1) {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            break;
        }else if(event.type == SDL_WINDOWEVENT){
            if(event.window.event == SDL_WINDOWEVENT_RESIZED){
                printf("Window %d resized to %dx%d",event.window.windowID, event.window.data1,event.window.data2);
                glViewport(0,0,event.window.data1,event.window.data2);
                size[0] = 0.0f + event.window.data1;
                size[1] = 0.0f + event.window.data2;
            }
        }else if(event.type == SDL_KEYDOWN){
            printf(  "KEY DOWN! %s\n", SDL_GetKeyName(event.key.keysym.sym) );
        }


        r->doRender(size);
        SDL_GL_SwapWindow(win);  
    }
    

    // Cleanup
    delete r;
    cleanup();

    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>

#include "SDL.h"
#include "GL/glew.h"

class PlatformDetection{
    public:
        PlatformDetection(){

        }

        void printPlatform(){
            char* info = getPlatform(true);
            printf("%s", info);
            free(info);
        }

        char* getPlatform(bool showExtensions){
            char* ret = (char*) malloc(sizeof(char) * 10000);

            char* extensions = "**Not Shown**";
            if(glGetString(GL_EXTENSIONS) == NULL){
                extensions = "(NULL)";
            } else if(showExtensions){
                extensions = (char*) glGetString(GL_EXTENSIONS);
            }


            snprintf(ret, 10000,
            "    Platform Information:\n---------------------------------------------------\n"
            "    Platform         : %s\n"
            "    RAM              : %d MB\n"
            "    Logical CPU cores: %d\n"
            "\n"
            "    Open GL Version   : %s\n"
            "    Open GL Vendor    : %s\n"
            "    Open GL Renderer  : %s\n"
            "    Open GL SL        : %s\n"
            "    Open GL extensions: %s\n"
            "\n---------------------------------------------------\n"

            ,SDL_GetPlatform(), SDL_GetSystemRAM(),SDL_GetCPUCount(),

            glGetString(GL_VERSION),glGetString(GL_VENDOR),glGetString(GL_RENDERER),glGetString(GL_SHADING_LANGUAGE_VERSION), extensions
            );

            return ret;
        }

        void showPlatform(){
            char* title = "Platform Information";
            char* info = getPlatform(false);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, info, NULL);
            free(info);
        }


};
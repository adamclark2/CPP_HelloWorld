#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>

#include "SDL.h"
#include "GL/glew.h"

struct glErrNumbers {
    GLint gl_number;
    char prefix[32];
    char postfix[64];
};

#define error_numbs_length 3
struct glErrNumbers error_numbs[] = {
    {GL_MAX_UNIFORM_LOCATIONS, "GL_MAX_UNIFORM_LOCATIONS", ""},
    {GL_MAX_UNIFORM_BLOCK_SIZE, "GL_MAX_UNIFORM_BLOCK_SIZE", ""},
    {GL_MAX_UNIFORM_BUFFER_BINDINGS, "GL_MAX_UNIFORM_BUFFER_BINDINGS", ""}
};

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

            char nums[1000];
            nums[0] = '\0';
            for(int i = 0; i < error_numbs_length;i++){
                char old[1000];
                old[999] = '\0';
                for(int i = 0;i < 1000;i++){
                    old[i] = nums[i];
                }

                GLint gl_ret = 0;
                glGetIntegerv(error_numbs[i].gl_number, &gl_ret);
                snprintf(nums, 1000, "%s%32s: %d %64s\n", old, error_numbs[i].prefix, gl_ret, error_numbs[i].postfix);
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
            "%s---------------------------------------------------\n"

            ,SDL_GetPlatform(), SDL_GetSystemRAM(),SDL_GetCPUCount(),

            glGetString(GL_VERSION),glGetString(GL_VENDOR),glGetString(GL_RENDERER),glGetString(GL_SHADING_LANGUAGE_VERSION), extensions,
            nums
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
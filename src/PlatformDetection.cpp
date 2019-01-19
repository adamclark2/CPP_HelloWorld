#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "SDL.h"

class PlatformDetection{
    public:
        PlatformDetection(){

        }

        void printPlatform(){
            printf("Platform         : %s\n", SDL_GetPlatform());
            printf("RAM              : %d MB\n", SDL_GetSystemRAM());
            printf("Logical CPU cores: %d\n", SDL_GetCPUCount());
        }


};
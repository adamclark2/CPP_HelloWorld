#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "gl/glew.h"

void checkGLError(int line, char* file){
    /*
    GLenum err = glGetError();
    GLenum orig = err;

    char* errText = "";
    while(err != GL_NO_ERROR){
        errText = "";
        if(err == GL_INVALID_OPERATION){
            errText = "GL_INVALID_OPERATION";
        }else if(err == GL_INVALID_VALUE){
            errText = "GL_INVALID_VALUE";
        }

        printf("\nGL ERROR [%d] at line [%i] file [%s] {{%s}}\n", err, line, file, errText);
        err = glGetError();
    }
    if(orig != GL_NO_ERROR){
        //exit(1);
    }else{
        //printf("NO ERROR-----\n");
    }*/

    // Replaced by OpenGL's error stuff
}

void dumpShaderInfo(GLuint shader, char* shaderName){
    int comp = 0; 
    glGetShaderiv(shader, GL_COMPILE_STATUS, &comp);

    char buf[10000];
    glGetShaderInfoLog(shader, 10000,NULL, (GLchar*) &buf);
    printf("Shader Log %s [Comp: %d, id: %d, isShader: %d]:\n------------------------\n%s\n", shaderName,comp,(int) shader,(int) glIsShader(shader), buf);
}

void dumpProgramInfo(GLuint prog, char* progName){
    char* status;
    int link = 0;
    int val = 0;
    glGetProgramiv(prog, GL_LINK_STATUS, &link);
    glGetProgramiv(prog, GL_VALIDATE_STATUS, &val);

    char buf[10000];
    glGetProgramInfoLog(prog, 10000,NULL, (GLchar*) &buf);
    printf("Program Log %s [Link: %d, Val: %d, id: %d, isProg: %d]:\n------------------------\n%s\n", progName,link,val,(int) prog,(int) glIsProgram(prog), buf);
}

void printLog(int line, char* file,char* err){
    printf("\nGENERIC ERROR at line [%i] file [%s] {{%s}}\n", line, file, err);
}

void GLAPIENTRY glDebugCallback(unsigned source,unsigned type, unsigned id,unsigned severity, int length,const char* message, const void* userParam){
    printf("[Src: %d][Type: %d][id: %d][severity: %d][len: %d][msg: %s]\n", (int) source, (int) type, (int) id, (int) severity, (int) length, (char*) message);
}
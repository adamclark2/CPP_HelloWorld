#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "gl/glew.h"

void checkGLError(int line, char* file){
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
        exit(1);
    }else{
        //printf("NO ERROR-----\n");
    }
}

void dumpShaderInfo(GLuint shader, char* shaderName){
    char buf[10000];
    glGetShaderInfoLog(shader, 10000,NULL, (GLchar*) &buf);
    printf("Shader Log %s:\n------------------------\n%s\n", shaderName, buf);
}

void dumpProgramInfo(GLuint prog, char* progName){
    char buf[10000];
    glGetProgramInfoLog(prog, 10000,NULL, (GLchar*) &buf);
    printf("Program Log %s:\n------------------------\n%s\n", progName, buf);
}

void printLog(int line, char* file,char* err){
    printf("\nGENERIC ERROR at line [%i] file [%s] {{%s}}\n", line, file, err);
}
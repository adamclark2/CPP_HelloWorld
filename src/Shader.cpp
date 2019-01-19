#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "SDL.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

using namespace::std;

class Shader{
    public:
        Shader(){
            this->glCheckError();
                char* vert = this->fileToString("src/vert.glsl");
                char* frag = this->fileToString("src/frag.glsl");

                GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
                GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

                glShaderSource(vertShader, 1, (const GLchar**) &vert, NULL);
                glCompileShader(vertShader);
            this->glCheckError();
                this->program = glCreateProgram();
                glAttachShader(this->program,vertShader);
                glLinkProgram(this->program);
                glAttachShader(this->program,fragShader);
                glLinkProgram(this->program);
            this->glCheckError();
                glDeleteShader(vertShader);
                glDeleteShader(fragShader);
                free(frag);
                free(vert);
            this->glCheckError();
            
            fflush(stdout);
        }

        ~Shader(){
            glDeleteProgram(this->program);
        }

        void use(){
            glUseProgram(this->program);
        }

        void glCheckError(){
            GLenum err = glGetError();
            GLenum orig = err;
            while(err != GL_NO_ERROR){
                char* errStr = (char*) gluErrorString(err);
                printf("-----\nVertex shader error %d\n%s\n------\n", err, errStr);
                err = glGetError();
            }
            if(orig != GL_NO_ERROR){
                exit(1);
            }else{
                printf("NO ERROR-----\n");
            }
        }

        GLint program;

        private:
            char* fileToString(char* file){
                int i = 0;
                ifstream infile;
                infile.open (file, ifstream::in);
                while (infile.good()){
                    i++;
                    infile.get();
                }
                infile.close();


                char* vert = (char*) malloc(sizeof(char) * (i + 1));
                vert[i] = '\0';
                i=0;
                infile.open (file, ifstream::in);
                while (infile.good()){
                    vert[i++] = infile.get();
                }
                infile.close();

                return vert;
            }

        
};
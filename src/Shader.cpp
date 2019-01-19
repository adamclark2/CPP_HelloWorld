#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "SDL.h"
#include "SDL_opengl.h"
#include "GL/glew.h"

#include "ErrorCheck.cpp"

using namespace::std;

class Shader{
    public:
        Shader(){
            checkGLError(__LINE__, __FILE__);
                char* vert = this->fileToString("src/vert.glsl");
                char* frag = this->fileToString("src/frag.glsl");

                GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
                glShaderSource(vertShader, 1, (const GLchar**) &vert, NULL);
                glCompileShader(vertShader);
                dumpShaderInfo(vertShader, "vert");

                GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
                glShaderSource(fragShader, 1, (const GLchar**) &frag, NULL);
                glCompileShader(fragShader);
                dumpShaderInfo(fragShader, "frag");

            checkGLError(__LINE__, __FILE__);
                this->program = glCreateProgram();
                glAttachShader(this->program,vertShader);
                glAttachShader(this->program,fragShader);
                glLinkProgram(this->program);
            checkGLError(__LINE__, __FILE__);
                glDeleteShader(vertShader);
                glDeleteShader(fragShader);
                free(frag);
                free(vert);
            checkGLError(__LINE__, __FILE__);

            glValidateProgram(this->program);
            dumpProgramInfo(this->program, "Prog1");
        }

        ~Shader(){
            glDeleteProgram(this->program);
        }

        void use(){
            glUseProgram(this->program);
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
                vert[i - 1] = '\0';

                return vert;
            }

        
};
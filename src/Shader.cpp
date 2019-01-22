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
                GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
                this->program = glCreateProgram();

                glShaderSource(vertShader, 1, (const GLchar**) &vert, NULL);
                glCompileShader(vertShader);
                dumpShaderInfo(vertShader, "vert");

                
                glShaderSource(fragShader, 1, (const GLchar**) &frag, NULL);
                glCompileShader(fragShader);
                dumpShaderInfo(fragShader, "frag");

            checkGLError(__LINE__, __FILE__);
                
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
            dumpProgramInfo(this->program, "Prog1 Shader.cpp");
        }

        ~Shader(){
            glDeleteProgram(this->program);
        }

        void use(){
            glUseProgram(this->program);
        }

        void setColor(float r, float g, float b, float a){
            glUniform4f(glGetUniformLocation(this->program, "vColor"), r,g,b,a);
            checkGLError(__LINE__, __FILE__);
        }

        void setRotation(float mat4Rot[]){
            GLuint vRot = glGetUniformLocation(this->program, "vRot");
            glUniformMatrix4fv(vRot, 1, GL_TRUE, mat4Rot);
            checkGLError(__LINE__, __FILE__);
        }

        void setScaleAndTranslation(float scale, float xTrans, float yTrans, float zTrans){
            float mat[] = {
                scale,0.0f,0.0f,xTrans,
                0.0f,scale,0.0f,yTrans,
                0.0f,0.0f,scale,zTrans,
                0.0f,0.0f,0.0f,1.0f
            };
            GLuint vTransform = glGetUniformLocation(this->program, "vTransform");
            glUniformMatrix4fv(vTransform, 1, GL_TRUE, mat);
            checkGLError(__LINE__, __FILE__);
        }

        void setWindowSize(float width, float height){
            float vWinTransformFV[] = {width, height, 1};
            GLuint vWinSize = glGetUniformLocation(this->program, "vWinSize");
            glUniform3fv(vWinSize, 1, vWinTransformFV);
            checkGLError(__LINE__, __FILE__);
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
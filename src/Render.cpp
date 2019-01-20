#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#include "SDL.h"
#include "GL/glew.h"
#include "ErrorCheck.cpp"

#include "Shader.cpp"

#define PI 3.14159265

class Render{
    public:
        Render(){
            xTranslate = 0.0f;
            checkGLError(__LINE__, __FILE__);
            s = new Shader();
            float pts[] = {
                -1.0f, -1.0f, 0.0f,
                1.0f, -1.0f, 0.0f,
                0.0f,  1.0f, 0.0f
            };

            float pts2[] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f,  0.5f, 0.0f
            };

            glGenVertexArrays(1,vao);
            glGenBuffers(2, buf);

            glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, pts, GL_DYNAMIC_DRAW);
            checkGLError(__LINE__, __FILE__);
            
            glBindBuffer(GL_ARRAY_BUFFER, buf[1]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, pts2, GL_DYNAMIC_DRAW);
            checkGLError(__LINE__, __FILE__);            
        }

        ~Render(){
            glDeleteBuffers(1, buf);
            glDeleteVertexArrays(1, vao);
            delete s;
        }

        /* 
            Render stuff

            Render loop is in main()
        */
        void doRender(){
            checkGLError(__LINE__, __FILE__);
            // Blink background
            if(SDL_GetTicks() % 2000 > 1000){
                glClearColor(1,1,1,1);
                glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
            }else{
                glClearColor(1,0,0,1);   
                glBindBuffer(GL_ARRAY_BUFFER, buf[1]);
            }
            glClear(GL_COLOR_BUFFER_BIT);
            checkGLError(__LINE__, __FILE__);

            checkGLError(__LINE__, __FILE__);

            checkGLError(__LINE__, __FILE__);
            glUseProgram(s->program);
            checkGLError(__LINE__, __FILE__);

            xTranslate += 0.01f;   
            xTranslate = xTranslate > 1 ? 0.0f : xTranslate;
            float scale = 1.0f;       
            float mat[] = {
                scale,0.0f,0.0f,xTranslate,
                0.0f,scale,0.0f,0.0f,
                0.0f,0.0f,scale,0.0f,
                0.0f,0.0f,0.0f,1.0f
            };
            GLuint vTransform = glGetUniformLocation(s->program, "vTransform");
            glUniformMatrix4fv(vTransform, 1, GL_TRUE, mat);
            checkGLError(__LINE__, __FILE__);

            glUniform4f(glGetUniformLocation(s->program, "vColor"), 0.5f, 0.5f, 0.5f, 1.0f);
            checkGLError(__LINE__, __FILE__);
            
            glBindVertexArray(vao[0]);
            GLuint vPos = glGetAttribLocation(s->program, "vPos");
            glEnableVertexAttribArray(vPos);
            glVertexAttribPointer(vPos, 3, GL_FLOAT, GL_FALSE, 0, 0);
            checkGLError(__LINE__, __FILE__);

            glDrawArrays(GL_TRIANGLES, 0, 9);

            glFlush();
            checkGLError(__LINE__, __FILE__);
        }

    private:
        GLuint buf[2];
        GLuint vao[1];
        Shader* s;
        float xTranslate;
        
};


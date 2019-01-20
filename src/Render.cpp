#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "SDL.h"
#include "GL/glew.h"
#include "ErrorCheck.cpp"

#include "Shader.cpp"

class Render{
    public:
        Render(){
            checkGLError(__LINE__, __FILE__);
            s = new Shader();
            float pts[] = {
                -1.0f, -1.0f, 0.0f,
                1.0f, -1.0f, 0.0f,
                0.0f,  1.0f, 0.0f
            };

            glGenVertexArrays(1,vao);
            glBindVertexArray(vao[0]);

            glGenBuffers(1, buf);
            glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, pts, GL_DYNAMIC_DRAW);
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
            }else{
                glClearColor(1,0,0,1);   
            }
            glClear(GL_COLOR_BUFFER_BIT);
            checkGLError(__LINE__, __FILE__);

            checkGLError(__LINE__, __FILE__);

            checkGLError(__LINE__, __FILE__);
            glUseProgram(s->program);
            checkGLError(__LINE__, __FILE__);

            glUniform4f(glGetUniformLocation(s->program, "vColor"), 0.5f, 0.5f, 0.5f, 1.0f);
            GLuint vPos = glGetAttribLocation(s->program, "vPos");
            glBindVertexArray(vao[0]);

            glEnableVertexAttribArray(vPos);
            glVertexAttribPointer(vPos, 3, GL_FLOAT, GL_FALSE, 0, 0);
            
            glDrawArrays(GL_TRIANGLES, 0, 9);
            glFlush();
            checkGLError(__LINE__, __FILE__);
        }

    private:
        GLuint buf[1];
        GLuint vao[1];
        Shader* s;
        
};


#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "SDL.h"
#include "GL/glew.h"

#include "Shader.cpp"

void checkGLError(){
    GLenum err = glGetError();
    GLenum orig = err;
    while(err != GL_NO_ERROR){
        //char* errStr = (char*) gluErrorString(err);
        printf("-----\nVertex shader error %d\n%s\n------\n", err, '-');
        err = glGetError();
    }
    if(orig != GL_NO_ERROR){
        exit(1);
    }else{
        //printf("NO ERROR-----\n");
    }
}

class Render{
    public:
        Render(){
            s = new Shader();
            float pts[] = {
                -1.0f, -1.0f, 0.0f,
                1.0f, -1.0f, 0.0f,
                0.0f,  1.0f, 0.0f
            };


            glGenBuffers(1, buf);
            glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, pts, GL_DYNAMIC_DRAW);
            checkGLError();
        }

        ~Render(){
            glDeleteBuffers(1, buf);
            delete s;
        }

        /* 
            Render stuff

            Render loop is in main()
        */
        void doRender(){
            // Blink background
            if(SDL_GetTicks() % 2000 > 1000){
                glClearColor(1,1,1,1);
            }else{
                glClearColor(1,0,0,1);   
            }
            glClear(GL_COLOR_BUFFER_BIT);
            
            glUseProgram(s->program);
            checkGLError();

            glUniform4f(glGetUniformLocation(s->program, "vColor"), 0.5f, 0.5f, 0.5f, 1.0f);

            GLuint vPos = glGetAttribLocation(s->program, "vPos");
            glEnableVertexAttribArray(vPos);
            glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
            glVertexAttribPointer(vPos, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glDrawArrays(GL_TRIANGLES, 0, 9);
            glFlush();
            checkGLError();
        }

    private:
        GLuint buf[1];
        Shader* s;
        
};


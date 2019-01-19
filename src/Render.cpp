#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "SDL.h"
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>

#include "Shader.cpp"

class Render{
    public:
        Render(){

        }

        void doRender(){
            this->win = NULL;
            int flags = SDL_WINDOW_OPENGL;
            this->win = SDL_CreateWindow("Hello C++",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,250,100,flags);
            if(this->win == NULL){
                printf("Window isn't created\n");
                exit(1);
            }


            SDL_ShowWindow(this->win);
            SDL_GLContext glcontext = SDL_GL_CreateContext(this->win);

            printf("\n\n");
            printf("Open GL Version   : %s\n", glGetString(GL_VERSION));
            printf("Open GL Vendor    : %s\n", glGetString(GL_VENDOR));
            printf("Open GL Renderer  : %s\n", glGetString(GL_RENDERER));
            printf("Open GL SL        : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
            printf("Open GL extensions: %s\n", glGetString(GL_EXTENSIONS));

            glGetError();
            Shader* s = new Shader();
            //s->use();

            float points[] = {
            0.0f,  0.5f,  0.0f,
            0.5f, -0.5f,  0.0f,
            -0.5f, -0.5f,  0.0f
            };

            GLuint vbo = 0;
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

            GLuint vao = 0;
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
                

            // Render loop
            SDL_Event event;
            while (1) {
                SDL_PollEvent(&event);
                if (event.type == SDL_QUIT) {
                    break;
                }

                // Blink background
                if(SDL_GetTicks() % 2000 > 1000){
                    glClearColor(1,1,1,1);
                }else{
                    glClearColor(1,0,0,1);   
                }
                glClear(GL_COLOR_BUFFER_BIT);
            

               s->use();

               
               glBindVertexArray(vao);
               glDrawArrays(GL_TRIANGLES, 0, 3);
               SDL_GL_SwapWindow(this->win);  
            }

            // Cleanup
            delete s;
            SDL_GL_DeleteContext(glcontext); 
            SDL_DestroyWindow(this->win);
        }

    private:
        SDL_Window* win;
};
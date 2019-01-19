#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "SDL.h"

class Point {
    public:
        Point(){
            points = (double[]) malloc(sizeof(double * 2));
            points[0] = 0;
            points[1] = 0;

            glGenBuffers(1, &this->vbo);
            glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(this->points), this->points, GL_STATIC_DRAW);
        }

        Point(double x, double y){
            points = (double[]) malloc(sizeof(double * 2));
            points[0] = x;
            points[1] = y;
        }

        double[] points;

        drawPoint(){

        }

        ~Point(){
            free(points);
        }

    private:
        GLuint vbo;
};
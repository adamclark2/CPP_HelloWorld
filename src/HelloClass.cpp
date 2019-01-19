#include <stdio.h>
#include <stdlib.h>

/*
    A simple class that prints 'Hello World'
*/
class HelloClass{
    public:
        int* x;

        HelloClass(){
            this->x = (int*) malloc(sizeof(int));
            *x = 2;
        }

        ~HelloClass(){
            printf("\nAdios!\n");
            free(x);
        }

        void printHi(){
            printf("Hello!!!!!!!!!\n\nWoo! %d\n", *this->x);
        }
};
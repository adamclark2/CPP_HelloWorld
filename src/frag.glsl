#version 330

uniform vec4 vColor;

out vec4 frag_colour;
void main(void){
    frag_colour = vColor;
}
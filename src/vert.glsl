#version 330

in vec3 vPos;

uniform vec3 vWinSize;
uniform mat4 vRot;
uniform mat4 vTransform;

void main(void){
    gl_Position = (vRot * vTransform) * vec4((vPos / vWinSize), 1.0) ;
}
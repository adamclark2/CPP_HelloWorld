#version 330

in vec3 vPos;

void main(void){
    gl_Position = vec4(vPos, 1.0);
}
#version 330

in vec3 vPos;
uniform mat4 vTransform;

void main(void){
    gl_Position = vTransform * vec4(vPos, 1.0);
}
#version 150 core

in vec2 position;

int main(){
    gl_Position = vec4(position, 0.0, 1.0);
    //same as   = vec4(position.x, position.y, 0.0, 1.0);
}
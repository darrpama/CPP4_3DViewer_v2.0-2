#version 120
attribute vec3 aPos;
varying vec3 FragPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main() {
   FragPos = vec3(model * vec4(aPos, 1.0));
   gl_Position = projection * view * vec4(FragPos, 1.0);
}
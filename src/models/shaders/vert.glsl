#extension GL_EXT_gpu_shader4 : require
attribute vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {

    gl_Position = projection * view * vec4(aPos, 1.0);
}
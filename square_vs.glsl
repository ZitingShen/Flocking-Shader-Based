#version 150

in vec4 vPos;
uniform mat4 proj;
uniform mat4 modelview;

void main() {
    gl_Position = proj*modelview*vPos;
}

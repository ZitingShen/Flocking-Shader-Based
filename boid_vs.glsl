#version 150

in vec4 vPos;
in vec4 vColor;
out vec4 color;
uniform mat4 modelview;

void main() {
    gl_Position = modelview*vPos;
    color = vColor;
}

#version 150

in vec4 vPos;
in vec3 vColor;
out vec4 color;
uniform mat4 proj;
uniform mat4 modelview;

void main() {
    gl_Position = proj*modelview*vPos;
    color = vec4(vColor, 1);
}

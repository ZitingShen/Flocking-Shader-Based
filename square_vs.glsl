#version 150

in vec4 vPos;
uniform mat4 modelview[16];

void main() {
    gl_Position = modelview[gl_InstanceID]*vPos;
}

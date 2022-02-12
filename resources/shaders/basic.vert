#version 460 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aColor;

uniform mat4 uModel;

out vec2 uv;
out vec3 color;

void main() {
    uv = aUV;
    color = aColor;
    gl_Position = uModel * vec4(aPosition, 1.0f);
}

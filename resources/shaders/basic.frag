#version 460

out vec4 FragColor;

//in vec3 vertexColor;

//uniform vec3 tint;

void main() {
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
//    FragColor = vec4(tint, 1.0);
//    FragColor = vec4(mix(vertexColor, tint, 0.5), 1.0);
}

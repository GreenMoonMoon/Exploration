#version 460

out vec4 FragColor;

in vec4 gl_FragCoord;

in vec2 uv;
in vec3 color;


//uniform vec3 tint;
uniform vec2 resolution;
uniform sampler2D tex1;

void main() {
//    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
//    FragColor = vec4(tint, 1.0);
//    FragColor = vec4(vertexColor, 1.0);
//    FragColor = vec4(mix(vertexColor, tint, 0.5), 1.0);
    FragColor = texture(tex1, uv) * vec4(color, 1.0);
}

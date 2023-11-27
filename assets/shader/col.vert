#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 vertex_color_in;

out vec4 vertex_color_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(pos, 1.0);
	vertex_color_out = vec4(vertex_color_in, 1.0);
}


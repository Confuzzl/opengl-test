#version 460 core
in vec4 vertex_color_out;

out vec4 color;

void main() {
	if (vertex_color_out.a == 0)
		discard;
	color = vertex_color_out;
}
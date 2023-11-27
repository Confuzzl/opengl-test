#version 460 core
in vec2 vertex_uv_out;

out vec4 color;

uniform sampler2D sampler;

void main() {
	vec4 col = texture(sampler, vertex_uv_out);
	if (col.a == 0)
		discard;
	color = col;
}
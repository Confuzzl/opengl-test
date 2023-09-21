#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 vertex_color_in;
layout (location = 2) in vec2 vertex_uv_in;

out vec4 vertex_color_out;
out vec2 vertex_uv_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

const uniform int TEXEL_RANGE = 1 << 15;

vec2 normalizeUV() {
	vec2 copy = vertex_uv_in;
	copy /= vec2(TEXEL_RANGE, TEXEL_RANGE);
	return copy;
}

void main() {
	gl_Position = projection * view * model * vec4(pos, 1f);
	vertex_color_out = vec4(vertex_color_in, 1f);
	vertex_uv_out = normalizeUV();
}


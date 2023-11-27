#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 2) in vec2 vertex_uv_in;

out vec2 vertex_uv_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

const int TEXEL_RANGE = 1 << 15;

vec2 normalizeUV() {
	vec2 copy = vertex_uv_in;
	copy /= vec2(TEXEL_RANGE, TEXEL_RANGE);
	return copy;
}

void main() {
	gl_Position = projection * view * model * vec4(pos, 1.0);
	vertex_uv_out = normalizeUV();
}


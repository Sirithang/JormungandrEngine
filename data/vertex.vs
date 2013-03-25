#version 330

in vec3 in_position;
in vec2 in_uv;

out vec2 out_uv;

uniform mat4 mvp;

void main()
{
	out_uv = in_uv;
	gl_Position = mvp * vec4(in_position, 1.0);
}
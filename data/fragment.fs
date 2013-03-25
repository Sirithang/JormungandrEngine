#version 330

in vec2 out_uv;

out vec4 out_Color;

uniform sampler2D _sampler0;
 
void main(void)
{
	vec4 col = texture2D(_sampler0, out_uv);
    out_Color = col;
}
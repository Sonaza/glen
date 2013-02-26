#version 150

out vec4 finalColor;

in vec2 v_texcoord;
in vec4 v_normal;
in vec4 v_fragposition;

uniform sampler2D u_diffuse;

void main()
{
	finalColor = texture(u_diffuse, v_texcoord);
}
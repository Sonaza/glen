#version 150

out vec4 finalColor;

in vec2 v_texcoord;

uniform vec4 u_spriteColor;
uniform sampler2D u_texture;

void main()
{
	finalColor = u_spriteColor * texture2D(u_texture, v_texcoord);
}
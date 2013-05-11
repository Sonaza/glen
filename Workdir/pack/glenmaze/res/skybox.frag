#version 150

out vec4 finalColor;

in vec3 v_texcoord;

uniform struct Textures
{
	samplerCube diffuse;
} u_texture;

uniform vec4 u_color;

void main()
{
	vec4 diffuse = texture(u_texture.diffuse, v_texcoord);
	
	finalColor = u_color * diffuse;
}
#version 150

out vec4 finalColor;

in vec2 v_texcoord;
in vec4 v_normal;
in vec4 v_fragposition;

uniform sampler2D u_diffuse;
uniform sampler2D u_specular;



void main()
{
	vec4 diffuse = texture(u_diffuse, v_texcoord);
	vec4 decal = texture(u_specular, v_texcoord);
	
	finalColor = vec4(
		diffuse.rgb + decal.rgb * decal.a, diffuse.a
	);
	
	/*finalColor = vec4(
		diffuse.rgb * (1.f - decal.a) + decal.rgb * decal.a, diffuse.a
	);*/

	//finalColor = mix(diffuse, decal, decal.a);
}
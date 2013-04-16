#version 150

precision highp float;

out vec4 finalColor;

in vec2 v_texcoord;
in vec4 v_normal;

uniform sampler2D u_diffuse;

void main()
{
	vec4 diffuse = texture(u_diffuse, v_texcoord);
		
	finalColor = diffuse;
	
	/*finalColor = vec4(
		diffuse.rgb * (vec3(1.0) - decal.rgb), diffuse.a * decal.a
	);*/

	//finalColor = mix(diffuse, decal, decal.a);
}
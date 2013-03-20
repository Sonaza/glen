#version 150

precision highp float;

out vec4 finalColor;

in vec2 v_texcoord;
in vec4 v_normal;
in vec4 v_fragposition;
/*
in vec2 v_diffusecoord;
in vec2 v_specularcoord;*/

uniform mat4 u_diffusemat;
uniform mat4 u_specularmat;

uniform sampler2D u_diffuse;
uniform sampler2D u_specular;

void main()
{
	vec2 v_diffusecoord = (u_diffusemat * vec4(v_texcoord, 0.f, 1.f)).xy;
	vec2 v_specularcoord = (u_specularmat * vec4(v_texcoord, 0.f, 1.f)).xy;
	
	vec4 diffuse = texture(u_diffuse, v_diffusecoord);
	vec4 decal = texture(u_specular, v_specularcoord);
	
	finalColor = vec4(
		diffuse.rgb + decal.rgb * decal.a, diffuse.a * decal.a
	);
	
	if(!gl_FrontFacing)
		finalColor *= vec4(vec3(0.2), 0.8);
	
	if(finalColor.a <= 0.1) discard;
	
	/*finalColor = vec4(
		diffuse.rgb * (vec3(1.0) - decal.rgb), diffuse.a * decal.a
	);*/

	//finalColor = mix(diffuse, decal, decal.a);
}
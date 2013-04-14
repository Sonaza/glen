#version 150

precision highp float;

out vec4 finalColor;

in vec2 v_texcoord;
in vec4 v_normal;
in vec4 v_fragposition;
in vec4 v_fragcolor;

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
		
	finalColor = v_fragcolor * diffuse;
	
	/*finalColor = vec4(
		diffuse.rgb * (vec3(1.0) - decal.rgb), diffuse.a * decal.a
	);*/

	//finalColor = mix(diffuse, decal, decal.a);
}
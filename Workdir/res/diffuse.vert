#version 150

precision highp float;

in vec3 a_position;
in vec3 a_texcoord;
in vec3 a_normal;

out vec2 v_texcoord;
out vec4 v_normal;
out vec4 v_fragposition;
out vec4 v_fragcolor;

/*
out vec2 v_diffusecoord;
out vec2 v_specularcoord;

uniform mat4 u_diffusemat;
uniform mat4 u_specularmat;*/

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

uniform float u_time;

void main()
{
	//vec4 normal = u_model * vec4(a_normal, 1.0);
	
	v_fragcolor = vec4(1.f);//vec4(a_normal.xyz * 0.5f + vec3(0.5f), 1.f);
	
	v_texcoord	= vec2(a_texcoord.x, 1.0 - a_texcoord.y);
	
	v_normal	= vec4(a_normal, 1.0);
	
	v_fragposition = u_view * u_model * vec4(a_position, 1.0);
	gl_Position = u_proj * u_view * u_model * vec4(a_position, 1.0);
}

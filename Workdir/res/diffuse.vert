#version 150

in vec3 a_position;
in vec3 a_texcoord;
in vec3 a_normal;

out vec2 v_texcoord;
out vec4 v_normal;
out vec4 v_fragposition;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

void main()
{
	v_texcoord	= texcoord.xy;
	v_normal	= vec4(normal, 1.0);
	
	v_fragposition = view * model * vec4(pos, 1.0);
	gl_Position = proj * view * model * vec4(pos, 1.0);
}

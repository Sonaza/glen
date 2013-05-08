#version 150

in vec3 a_position;
in vec3 a_texcoord;
in vec3 a_normal;

out vec2 v_texcoord;
out vec4 v_normal;

uniform struct Matrices {
	mat4 model;
	mat4 view;
	mat4 proj;
} u_matrix;

void main()
{
	v_texcoord	= vec2(a_texcoord.x, 1.0 - a_texcoord.y);
	v_normal	= vec4(a_normal, 1.0);
	
	gl_Position = u_matrix.proj * u_matrix.view * u_matrix.model * vec4(a_position, 1.0);
}

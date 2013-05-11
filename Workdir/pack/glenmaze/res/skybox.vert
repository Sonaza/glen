#version 150

in vec3 a_position;
in vec3 a_texcoord;

out vec3 v_texcoord;

uniform struct Matrices {
	mat4 model;
	mat4 view;
	mat4 proj;
} u_matrix;

void main()
{
	v_texcoord 	= normalize(a_position);
	
	gl_Position = u_matrix.proj * u_matrix.view * u_matrix.model * vec4(a_position, 1.0);
}

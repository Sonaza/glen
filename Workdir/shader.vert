#version 150

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

in vec4 vertexColor;

in vec3 position;
in vec3 normal;
in vec2 texcoord;

out vec4 FragColor;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
	TexCoord = texcoord;
	FragColor = vec4(1.0);//vec4(position.x+0.1, position.y+0.1, position.z+0.1, 1.0);
	Normal = normal;
	
	gl_Position = proj * view * model * vec4(position, 1.0);
}
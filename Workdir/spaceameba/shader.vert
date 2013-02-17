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

uniform float time;

void main()
{
	TexCoord = texcoord;
	Normal = normal;
	
	vec3 pos = position.xyz
					+ normal.xyz * (cos(time * 3.5f + position.y * 20.f) * 0.5f + 1.f)
					* (sin(time + position.y * 10.f) * 0.5f + 1.0f) * 0.1f
					+ normal.xyz * (cos(time * 3.5f + position.x * 20.f) * 0.5f + 1.f)
					* (sin(time + position.x * 10.f) * 0.5f + 1.0f) * 0.1f;
	
	FragColor = vec4(pos.xyz / 2.0 + vec3(0.5), 1.0) * 1.f;
	
	gl_Position = proj * view * model * vec4(pos, 1.0);
}

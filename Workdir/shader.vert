#version 150

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

in vec4 vertexColor;

in vec3 position;
in vec3 normal;
in vec3 texcoord;

out vec4 FragColor;
out vec3 Normal;
out vec2 TexCoord;

out vec3 FragPosition;

uniform float time;

void main()
{
	TexCoord = texcoord.xy;
	
	vec3 pos = position.xyz
					//+ normalize(position.xyz) * (cos(time * 2.f + position.y * 500.f) * 0.5f + 0.5f) * 0.5f
					//+ normal.xyz * (cos(time * 3.5f + position.y * position.y * 500.f) * 0.5f + 1.5f)
					//* (sin(time + position.y * position.y * 20.f) * 0.5f + 0.5f) * 0.02f
					+ normal.xyz * (sin(time * 4.f + position.y * position.y * position.z * 200.f)*0.5f+0.75f) * 0.03f
					* (cos(time * 2.f * position.y * position.z / 150.f)*0.5f+0.5f)
					//* (cos(time * 2.f + position.y * position.z * 20.f)*0.5f+0.5f)
					//* (cos(time / 1.2f)*1.5f-0.5f);
					//+ normal.xyz * (sin(time * 4.f + position.y * 20.f)*0.5f+0.6f) * 0.1f
					//* (cos(time * 2.f + position.x * position.x * 50.f)*0.5f+0.5f)
	;
	
	Normal = normalize(view * model * vec4(normal, 0.0)).xyz;
	
	FragColor = vec4(pos.xyz / 2.0 + vec3(0.5), 1.0) * 2.2f;
	FragPosition = (view * model * vec4(pos, 1.0)).xyz;
	
	gl_Position = proj * view * model * vec4(pos, 1.0);
}

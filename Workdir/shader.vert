#version 150

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

in vec4 vertexColor;

in vec3 position;
in vec3 normal;
in vec3 texcoord;

out vec4 vertFragColor;
out vec4 vertNormal;
out vec2 vertTexCoord;
out vec3 vertFragPosition;

uniform float time;

void main()
{
	/*vec3 pos = position.xyz
					+ normal.xyz * 0.1f
					* (sin(time * 4.f + position.x * position.y * position.z * 400.f) * 0.5f + 0.75f)
					* (sin(time * 2.f + position.x * position.z * 150.f) * 0.5f - 0.5f)
					//* (cos(time * 2.f * position.y * position.z / 50.f) * 0.5f + 0.5f)
					//* (cos(time * 2.f + position.x * position.y * 250.f) * 0.5f + 0.5f)
					//* (cos(time / 1.2f)*1.5f-0.5f);
					//+ normal.xyz * (sin(time * 4.f + position.y * 20.f)*0.5f+0.6f) * 0.1f
					//* (cos(time * 2.f + position.x * position.x * 50.f)*0.5f+0.5f)
	;*/
	
	vec3 pos = position.xyz
					+ normal.xyz * 0.1f
					* (sin(time * 4.f + position.x * position.y * position.z * 200.f) * 0.5f + 0.75f)
					* (sin(time * 2.f + position.x * position.z * 50.f) * 0.5f - 0.5f);
	
	vertTexCoord = texcoord.xy;
	vertNormal = vec4(normal, 1.0);
	
	vertFragColor = vec4(pos.xyz / 2.0 + vec3(0.5), 1.0) * 1.8f;
	vertFragPosition = (view * model * vec4(pos, 1.0)).xyz;
	
	gl_Position = vec4(pos, 1.0);
}

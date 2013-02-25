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
	
	/*mat4 twist = mat4(
					cos(angle), -sin(angle), 0.0, 0.0,
					sin(angle), cos(angle), 0.0, 0.0,
					0.0, 0.0, 1.0, 0.0,
					0.0, 0.0, 0.0, 1.0
				);*/
	
	vec3 pos = position.xyz
					+ normal.xyz * 0.05f
					* (sin(time * 4.f + position.x * position.y * 50.f) * 0.5f + 0.5f)
					* (sin(time * 2.f + position.x * position.y * position.z * 90.f) * 0.5f - 0.5f)
					+ vec3(
						sin(time + position.y * 15.f) * 0.06f * (cos(time / 2.f) * 0.5f + 0.5f),
						cos(time + position.x * 4.f) * 0.05f,
						sin(time * 2 + position.x * 10.f) * 0.05f
					)
	;
	
	vertTexCoord = texcoord.xy;
	vertNormal = vec4(normal, 1.0);
	
	vertFragColor = vec4(1.0);//vec4(pos.xyz / 2.0 + vec3(0.5), 1.0) * 2.f;
	vertFragPosition = (view * model * vec4(pos, 1.0)).xyz;
	
	gl_Position = vec4(pos, 1.0);
}

#version 150

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

in vec4 vertFragColor[];
in vec2 vertTexCoord[];
in vec4 vertNormal[];
in vec3 vertFragPosition[];

out vec4 FragColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform float time;

void main()
{
	mat4 modelview = view * model;
	mat4 mvp = proj * modelview;
	
	vec4 tempnormal;
	
	for(int i=0; i < 3; i++)
	{
		switch(i)
		{
			case 0:
				tempnormal = vec4(normalize(cross(gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz, gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz)), 1.0);
			break;
			case 1:
				tempnormal = vec4(normalize(cross(gl_in[2].gl_Position.xyz - gl_in[1].gl_Position.xyz, gl_in[0].gl_Position.xyz - gl_in[1].gl_Position.xyz)), 1.0);
			break;
			case 2:
				tempnormal = vec4(normalize(cross(gl_in[0].gl_Position.xyz - gl_in[2].gl_Position.xyz, gl_in[1].gl_Position.xyz - gl_in[2].gl_Position.xyz)), 1.0);
			break;
		}
		
		FragColor = vec4(normalize(tempnormal).xyz / -2.f + vec3(0.5), 1.0) * 1.5f;//vertFragColor[i];
		TexCoord = vertTexCoord[i];
		
		Normal = normalize(modelview * tempnormal).xyz;
		//Normal = normalize(modelview * vertNormal[i]).xyz;
		
		FragPosition = vertFragPosition[i];
		
		vec3 N = tempnormal.xyz;//vertNormal[i].xyz;
		
		vec4 temppos = gl_in[i].gl_Position;
		vec3 pos = gl_in[i].gl_Position.xyz
						+ N * (sin(time / 1.5f + temppos.x * temppos.y * temppos.z * 10.f) * 0.5f + 0.5f) * 0.1f
						+ N * cos(time + temppos.y * 15.f) * 0.01f
		;
		
		gl_Position = mvp * vec4(pos, 1.0);
		
		EmitVertex();
	}
	
	EndPrimitive();
}

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
		
		FragColor = vertFragColor[i];
		TexCoord = vertTexCoord[i];
		
		Normal = normalize(modelview * tempnormal).xyz;
		//Normal = normalize(modelview * vertNormal[i]).xyz;
		
		FragPosition = vertFragPosition[i];
		
		gl_Position = mvp * gl_in[i].gl_Position;
		
		EmitVertex();
	}
	
	EndPrimitive();
}

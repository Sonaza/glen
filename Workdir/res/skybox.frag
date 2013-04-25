#version 150

precision highp float;

out vec4 finalColor;

in vec2 v_texcoord;
in vec4 v_normal;

uniform float u_time;

uniform sampler2D u_diffuse;

void main()
{
	vec4 diffuse = texture(u_diffuse, v_texcoord);
	
	//float daycycle = cos(u_time / 2.f) * 0.4f + 0.6f;
	
	finalColor = vec4(diffuse.rgb, 1.f);
}
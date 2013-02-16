#version 150

out vec4 finalColor;

in vec4 FragColor;
in vec2 TexCoord;
in vec3 Normal;

uniform sampler2D tex;

void main()
{
	vec2 uv = TexCoord;
	
	float d = 1.0 - (gl_FragCoord.z / gl_FragCoord.w / 5.0);
	d = clamp(d, 0.0, 1.0);
	
	vec4 fog = vec4(d, d, d, 1.0);
	vec4 c = texture(tex, uv) * FragColor * fog;
	
	finalColor = vec4(c.rgb, c.a);
}
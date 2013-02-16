#version 150

out vec4 finalColor;

in vec4 FragColor;
in vec2 TexCoord;
in vec3 Normal;

uniform sampler2D tex;

void main()
{
	vec2 uv = TexCoord;
	vec4 c = texture(tex, uv) * FragColor;
	
	if(c.a <= 0.99) discard;
	
	finalColor = vec4(c.rgb, c.a);
}
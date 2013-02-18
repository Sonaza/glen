#version 150

out vec4 finalColor;

in vec4 FragColor;
in vec2 TexCoord;
in vec3 Normal;

uniform float time;

uniform sampler2D tex;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 758.5453);
}

void main()
{
	vec2 uv = TexCoord;
	
	float d = (gl_FragCoord.z / gl_FragCoord.w) - 1.2f;
	//d = clamp(d, 0.0, 1.0);
	
	float intensity = (exp(d/2.5f)-1.f)/2.5;
	intensity = clamp(intensity, 0.f, 1.f);
	
	vec4 fogColor = vec4(1.0);
	
	//texture(tex, uv) * 
	vec4 c = FragColor * (1.f-intensity) + fogColor * intensity;
	c.r = clamp(c.r, 0.0, 1.0);
	c.g = clamp(c.g, 0.0, 1.0);
	c.b = clamp(c.b, 0.0, 1.0);
	
	finalColor = FragColor;//vec4(c.rgb, 1.f);
	
	vec2 pos = TexCoord * vec2(1.0, tan(time/0.5f)*0.5f+1.1f);
	vec2 uPos = pos;
	uPos.y -= 0.5;
	
	vec3 color = vec3(0.0);
	float vertColor = 0.0;
	const float k = 9.;
	for( float i = 1.0; i < k; ++i )
	{
		float t = time * (1.0);
	
		uPos.y += sin( uPos.x*exp(i) - t) * 0.015;
		float fTemp = abs(1.0/(50.0*k) / uPos.y);
		vertColor += fTemp;
		color += vec3( fTemp*(i*0.03), fTemp*i/k, pow(fTemp,0.93)*1.2 );
	}
	
	float ca = color.r * 0.3 + color.g * 0.3 + color.b * 0.3;
	finalColor += vec4(ca, ca, ca, 1.0);
	
	float ft = fract(time);
	vec3 temp = vec3( rand( pos +  7.+ ft ), 
				  rand( pos +  9.+ ft ),
				  rand( pos + 11.+ ft ) ) / 32.0;
	ca = temp.r * 0.3 + temp.g * 0.3 + temp.b * 0.3;
	
	finalColor.rgb += vec3(ca);
	
	finalColor = finalColor * (1.f-intensity) + fogColor * intensity;
}
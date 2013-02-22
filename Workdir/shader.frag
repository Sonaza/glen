#version 150

uniform mat4 model;
uniform mat4 view;

out vec4 finalColor;

in vec4 FragColor;
in vec2 TexCoord;
in vec3 Normal;

in vec3 FragPosition;

uniform float time;

uniform sampler2D tex;

const vec4 lightPos = vec4(1.0, 0.0, -1.5, 1.0);
const vec4 ambientColor = vec4(95, 35, 17, 255) / 255.f;
const vec4 diffuseColor = vec4(250, 215, 220, 255) / 255.f;
const vec4 specularColor = vec4(255, 255, 255, 255) / 255.f;

void main()
{
	vec3 lightDir = normalize(
		lightPos.xyz + vec3(0.0, 0.0, -2.f + cos(time / 2.f) * 0.8f)
		- FragPosition);
	
	float lightIntensity = 1.f;// (1.f - min(1.f, distance(FragPosition, lightPos.xyz) / 1.8f));
	
	vec4 diffuseFactor = (dot(Normal, lightDir) * diffuseColor);
	vec4 ambientFactor = (dot(Normal, lightDir) * ambientColor);
	vec4 ambdiffFactor = diffuseFactor * lightIntensity + ambientColor; // + ambientFactor * (1.f-lightIntensity)
	
	vec3 reflection = reflect(lightDir.xyz, Normal);
	vec3 eyes = normalize(FragPosition);
	
	float shininess = 60.f;
	vec4 specularFactor = max(pow(-dot(reflection, eyes), shininess), 0.0) * specularColor * lightIntensity;
	
	float d = (gl_FragCoord.z / gl_FragCoord.w) - 1.2f;
	//d = clamp(d, 0.0, 1.0);
	
	float intensity = 0.f;//(exp(d/(cos(time/2.f) * 0.5f + 1.f))-1.f)/5.0;
	//if(intensity >= 1) discard;
	
	intensity = clamp(intensity, 0.f, 1.f);
	
	vec4 fogColor = ambientColor;
	
	vec4 lighting = ambdiffFactor + specularFactor;
	
	vec2 bpos = vec2(cos(time * 3.f - TexCoord.x * TexCoord.y * 80.f) * 0.25f + 0.5f, sin(time * 3.f + TexCoord.x * TexCoord.y * 80.f) * 0.25f + 0.5f);
	float bcol = 0.3f / ((bpos.x - TexCoord.x) * (bpos.x - TexCoord.x) + (bpos.y - TexCoord.y) * (bpos.y - TexCoord.y));
	vec4 FragColor = vec4(vec3(bcol + 0.65f) * ambientColor.xyz * 1.5f, 1.0);
	
	//vec4 FragColor = texture(tex, TexCoord) * FragColor;
	vec4 c = FragColor * lighting * (1.f-intensity) + fogColor * intensity;
	
	finalColor = vec4(c.rgb, 1.f);
}
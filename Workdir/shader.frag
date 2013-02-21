#version 150

out vec4 finalColor;

in vec4 FragColor;
in vec2 TexCoord;
in vec3 Normal;

in vec3 FragPosition;

uniform float time;

uniform sampler2D tex;

const vec3 lightPos = vec3(2.0, 2.0, 1.0);
const vec4 ambientColor = vec4(94, 65, 152, 255) / 255.f;
const vec4 diffuseColor = vec4(250, 215, 220, 255) / 255.f;
const vec4 specularColor = vec4(255, 255, 255, 255) / 255.f;

void main()
{
	vec3 lightDir = normalize(lightPos - FragPosition);
	
	float lightIntensity = 1.f;//(1.f - min(1.f, distance(FragPosition, lightPos.xyz) / 5.f));
	vec4 diffuseFactor = (dot(Normal, lightDir) * diffuseColor);
	vec4 ambdiffFactor = diffuseFactor * lightIntensity + ambientColor;
	
	vec3 reflection = reflect(lightDir.xyz, Normal);
	vec3 eyes = normalize(FragPosition);
	
	float shininess = 10.f;
	vec4 specularFactor = max(pow(-dot(reflection, eyes), shininess), 0.0) * specularColor * lightIntensity;
	
	float d = (gl_FragCoord.z / gl_FragCoord.w) - 1.2f;
	//d = clamp(d, 0.0, 1.0);
	
	float intensity = (exp(d/(cos(time/2.f) * 0.5f + 1.f))-1.f)/5.0;
	//if(intensity >= 1) discard;
	
	intensity = clamp(intensity, 0.f, 1.f);
	
	vec4 fogColor = ambientColor;
	
	vec4 lighting = ambdiffFactor + specularFactor;
	//vec4 FragColor = texture(tex, TexCoord) * FragColor;
	vec4 c = FragColor * lighting * (1.f-intensity) + fogColor * intensity;
	c.r = clamp(c.r, 0.0, 1.0);
	c.g = clamp(c.g, 0.0, 1.0);
	c.b = clamp(c.b, 0.0, 1.0);
	
	finalColor = vec4(c.rgb, 1.f);
}
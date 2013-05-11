#version 150

precision highp float;

out vec4 finalColor;

in vec2 v_texcoord;
in vec4 v_normal;
in vec4 v_fragposition;
in vec4 v_fragcolor;

uniform struct TexTransforms
{
	mat4 diffuse;
	mat4 normal;
	mat4 specular;
} u_texmatrix;

uniform struct Textures
{
	sampler2D diffuse;
	sampler2D normal;
	sampler2D specular;
} u_texture;

uniform struct Matrices {
	mat4 model;
	mat4 view;
	mat4 proj;
} u_matrix;

float warp_diffuse(float d)
{
	return d;// * 0.5 + 0.5;
	//return smoothstep(0.35, 0.37, d) * 0.4 + smoothstep(0.70, 0.72, d) * 0.6;
}

vec4 getDiffuseFrag()
{
	#ifdef TEXTURE_DIFFUSE
		vec2 diffuse_uv = (u_texmatrix.diffuse * vec4(v_texcoord, 0.f, 1.f)).xy;
		return texture(u_texture.diffuse, diffuse_uv);
	#else
		return vec4(1.0);
	#endif
}

//vec4 fogColor = vec4(114.f / 255.f, 168.f / 255.f, 198.f / 255.f, 1.f);

uniform float u_time;

uniform vec4 u_color;

void main()
{
	vec4 diffuseFrag = getDiffuseFrag();
	finalColor = diffuseFrag;
	
	//vec2 normalmap_uv = (u_texmatrix.normal * vec4(v_texcoord, 0.f, 1.f)).xy;
	//vec4 normalmapFrag = texture(u_texture.normal, normalMap_uv);
	
	float zdistance = (gl_FragCoord.z / gl_FragCoord.w);
	float fogIntensity = exp((zdistance - 20.f) / 7000.f) - 1.f;
	
	fogIntensity = clamp(fogIntensity, 0.f, 1.f);
	
	//float daycycle = cos(u_time / 2.f) * 0.5f + 0.5f;
	//float daycm = daycycle * 0.8f + 0.2f;
	
	vec4 fogColor = vec4(114.f / 255.f, 168.f / 255.f, 198.f / 255.f, 1.f);
	//fogColor = vec4(fogColor.rgb * daycm, 1.f);
	
	//////////////
	
	vec3 lightPos = vec3(2.f, 4.f, 2.f);////vec3(cos(m_time / 2.f) * 1800.f, cos(m_time / 2.f) * 1500.f, sin(-m_time / 2.f) * 2500.f);
	vec3 lightDir = lightPos;
	//v_fragposition.xyz;
	
	//float D = length(lightDir);
		
	vec3 L = normalize(lightDir);
	vec3 N = normalize(v_normal.xyz);
	
	vec4 diffuseColor = vec4(0.7, 0.7, 0.7, 0.0);
	vec4 ambientColor = vec4(0.45, 0.45, 0.45, 1.0);
	vec4 specularColor = vec4(5.6, 0.6, 0.45, 1.0);
	
	//vec3 falloff = vec3(1.f, 2.f, 1.f);
	//float attenuation = 1.f / (falloff.x + (falloff.y * D) + (falloff.z * D * D));
	
	float NdotL = max(warp_diffuse(dot(N, L)), 0.f);
	
	vec4 diffuseFactor = NdotL * diffuseColor;
	diffuseFactor = clamp(diffuseFactor, 0.f, 1.f);
	
	vec4 lightFactor = diffuseFactor + ambientColor;
	
	#ifdef SPECULAR
	
	float shininess = 50.f;
	
	vec4 fragpos = u_matrix.view * v_fragposition;
	vec3 eye = normalize(fragpos.xyz);
	
	vec3 reflection = reflect(L, N);
	
	vec4 specularFactor = max(pow(-dot(reflection, eye), shininess), 0.f) * specularColor;
	
	lightFactor = lightFactor + specularFactor;
	
	#endif
	
	finalColor = finalColor * lightFactor;
	
	finalColor = finalColor * (1.f - fogIntensity) + fogColor * fogIntensity;
	
	//float dca = daycycle * 0.3f + 0.7f;
	//float dcb = clamp(daycycle + 0.8f, 0.f, 1.f);
	
	//vec3 sykle = vec3(dca, dca, dcb);
	
	finalColor = u_color * vec4(finalColor.rgb, diffuseFrag.a);
	finalColor = clamp(finalColor, 0.f, 1.f);
	
	//vec3 c = v_fragposition.xyz / 1500.f / 2.f + vec3(0.5f);
	
	//finalColor = vec4(c, 1.f);
	
	//finalColor = vec4(vec3(zdistance / 3000.f), diffuseFrag.a);
}
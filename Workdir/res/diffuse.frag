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

uniform mat4 u_model;
uniform mat4 u_view;

float warp_diffuse(float d)
{
	return d * 0.5 + 0.5;
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

vec4 fogColor = vec4(114.f / 255.f, 168.f / 255.f, 198.f / 255.f, 1.f);

void main()
{
	vec4 diffuseFrag = getDiffuseFrag();
	
	//vec2 normalmap_uv = (u_texmatrix.normal * vec4(v_texcoord, 0.f, 1.f)).xy;
	//vec4 normalmapFrag = texture(u_texture.normal, normalMap_uv);
	
	float zdistance = (gl_FragCoord.z / gl_FragCoord.w);
	float fogIntensity = exp(zdistance / 1800.f) - 1.f;
	
	fogIntensity = clamp(fogIntensity, 0.f, 1.f);
	
	//////////////
	
	vec3 lightPos = vec3(-10.f, 20.f, -50.f);
	
	vec3 L = normalize(lightPos - v_fragposition.xyz);
	vec3 N = normalize(v_normal.xyz);
	
	vec4 diffuseColor = vec4(0.7, 0.55, 0.3, 0.0);
	vec4 ambientColor = vec4(0.3, 0.35, 0.4, 1.0);
	vec4 specularColor = vec4(0.6, 0.6, 0.45, 1.0);
	
	vec4 diffuseFactor = max(warp_diffuse(dot(N, L)), 0.f) * diffuseColor;
	vec4 lightFactor = diffuseFactor + ambientColor;
	
	vec4 mvFragPos = u_view * v_fragposition;
	
	vec3 eye = normalize(mvFragPos.xyz);
	vec3 reflection = reflect(L, N);
	
	float shininess = 50000.f;
	
	vec4 specularFactor = max(pow(-dot(reflection, eye), shininess), 0.f) * specularColor;
	
	//////////////	
	
	finalColor = (v_fragcolor * diffuseFrag * lightFactor + specularFactor) * (1.f - fogIntensity) + fogColor * fogIntensity;
	
	/*finalColor = vec4(
		diffuse.rgb * (vec3(1.0) - decal.rgb), diffuse.a * decal.a
	);*/

	//finalColor = mix(diffuse, decal, decal.a);
}
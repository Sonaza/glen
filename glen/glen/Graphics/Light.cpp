#include <glen/Graphics/Light.hpp>
#include <glen/Graphics/Material.hpp>

namespace glen
{
namespace
{
	std::vector<Light*>	_lights;
}

/////////////////////////////////////////////////
Light::Light(void) :
	m_type(Directional),
	m_color(255, 255, 255, 255)
{
}
	
/////////////////////////////////////////////////
Light::Light(LightType type) :
	m_type(type),
	m_color(255, 255, 255, 255)
{
}

/////////////////////////////////////////////////
Light::~Light(void)
{
}

/////////////////////////////////////////////////
Light* Light::create(LightType type)
{
	Light* result = new(std::nothrow) Light(type);

	if(result)
	{
		_lights.push_back(result);
	}

	return result;
}

/////////////////////////////////////////////////
void Light::setUniforms(Material* material)
{
	//material->m_program->
}

/////////////////////////////////////////////////
void Light::setColor(const Color& color)
{
	m_color = color;
}

/////////////////////////////////////////////////
void Light::setIntensity(float intensity)
{
	m_intensity = intensity;
}

}
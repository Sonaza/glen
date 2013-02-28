#ifndef GLEN_LIGHT_HPP
#define GLEN_LIGHT_HPP

#include <glen/System/Transformable.hpp>
#include <glen/Graphics/Color.hpp>

#include <vector>

namespace glen
{

	class Material;

	class Light : public Transformable
	{
	public:
		enum LightType
		{
			Directional
		};

		Light(void);
		Light(LightType type);
		~Light(void);

		static Light* create(LightType type);
		static void setUniforms(Material* material);

		void setColor(const Color& color);
		void setIntensity(float intensity);

	private:

		LightType	m_type;

		Color		m_color;
		float		m_intensity;

	};

}

#endif

#include <glen/Graphics/Texture/TextureTransform.hpp>

namespace glen
{

////////////////////////////////////////////////////////////////
TextureTransform::TextureTransform(void)
{
}

////////////////////////////////////////////////////////////////
TextureTransform::~TextureTransform(void)
{
}

//////////////////////////////////////////////////
mat4 TextureTransform::getMatrix()
{
	if(m_updateMatrix)
	{
		m_matrix = mat4();
		m_matrix.translate(vec3f(0.5f, 0.5f, 0.f))
				.translate(m_position)
				.rotate(m_rotation.x, vec3f(1.f, 0.f, 0.f))
				.rotate(m_rotation.y, vec3f(0.f, 1.f, 0.f))
				.rotate(m_rotation.z, vec3f(0.f, 0.f, 1.f))
				.scale(m_scale)
				.translate(-vec3f(0.5f, 0.5f, 0.f))
				.translate(m_pivot);

		m_updateMatrix = false;
	}

	return m_matrix;
}

}

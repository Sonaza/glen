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
		m_matrix = mat4::identity;
		m_matrix.translate(vec3f(0.5f, 0.5f, 0.f))
				.translate(m_position)
				.rotate(m_rotation.x, vec3f(1.f, 0.f, 0.f))
				.rotate(m_rotation.y, vec3f(0.f, 1.f, 0.f))
				.rotate(m_rotation.z, vec3f(0.f, 0.f, 1.f))
				.scale(m_scale)
				.translate(-vec3f(0.5f, 0.5f, 0.f))
				.translate(m_pivot);
		/*
		m_matrix = glm::translate(m_matrix, glm::vec3(0.5f, 0.5f, 0.f));

		m_matrix = glm::translate(m_matrix, glm::vec3(m_position.x, m_position.y, m_position.z));

		m_matrix = glm::rotate(m_matrix, m_rotation.x, glm::vec3(1.f, 0.f, 0.f));
		m_matrix = glm::rotate(m_matrix, m_rotation.y, glm::vec3(0.f, 1.f, 0.f));
		m_matrix = glm::rotate(m_matrix, m_rotation.z, glm::vec3(0.f, 0.f, 1.f));

		m_matrix = glm::scale(m_matrix, glm::vec3(m_scale.x, m_scale.y, m_scale.z));

		m_matrix = glm::translate(m_matrix, glm::vec3(-0.5f, -0.5f, 0.f));

		m_matrix = glm::translate(m_matrix, glm::vec3(m_pivot.x, m_pivot.y, m_pivot.z));
		*/
		m_updateMatrix = false;
	}

	return m_matrix;
}

}

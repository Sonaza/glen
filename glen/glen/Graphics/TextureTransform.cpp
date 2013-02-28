#include <glen/Graphics/TextureTransform.hpp>

#include <glm/gtc/matrix_transform.hpp>

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
glm::mat4 TextureTransform::getMatrix()
{
	if(m_updateMatrix)
	{
		m_matrix = glm::mat4(1.f);

		m_matrix = glm::translate(m_matrix, glm::vec3(m_position.x, m_position.y, m_position.z));

		m_matrix = glm::rotate(m_matrix, m_rotation.x, glm::vec3(1.f, 0.f, 0.f));
		m_matrix = glm::rotate(m_matrix, m_rotation.y, glm::vec3(0.f, 1.f, 0.f));
		m_matrix = glm::rotate(m_matrix, m_rotation.z, glm::vec3(0.f, 0.f, 1.f));

		m_matrix = glm::translate(m_matrix, glm::vec3(m_pivot.x, m_pivot.y, m_pivot.z));
		
		m_matrix = glm::inverse(glm::scale(m_matrix, glm::vec3(m_scale.x, m_scale.y, m_scale.z)));

		m_updateMatrix = false;
	}

	return m_matrix;
}

}

#ifndef GLEN_MODEL_HPP
#define GLEN_MODEL_HPP

#include <glen/opengl.hpp>
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <cassert>

namespace glen
{

	class Material;
	class MeshData;

	class Model
	{
	public:
		Model(void);
		~Model(void);

		void setMaterial(Material* material);

		bool loadFromFile(const std::string& path);

		void render(glm::mat4 &transform);
		
	protected:

		Material*	m_material;

		MeshData*	m_meshdata;

		GLuint		m_vbo;
		GLuint		m_vao;

	};

}

#endif
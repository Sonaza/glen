#ifndef GLEN_MODEL_HPP
#define GLEN_MODEL_HPP

#include <glen/opengl.hpp>
#include <glen/System/Types.hpp>

#include <vector>
#include <string>
#include <cassert>

namespace glen
{

	class Material;
	class MeshData;

	class Model
	{
		friend class Renderer;

	public:
		Model(void);
		~Model(void);

		bool loadFromFile(const std::string& path);

		void setMaterial(Material* material);

		void render(mat4 &transform);
		
	protected:

		Material*	m_material;
		MeshData*	m_meshdata;

		GLuint		m_vbo;
		GLuint		m_vao;

	};

}

#endif
#ifndef GLEN_MODEL_HPP
#define GLEN_MODEL_HPP

#include <glen/Graphics/MeshLoader.hpp>
#include <glen/ogl.h>

#include <glen/Graphics/Material.hpp>

#include <glen/System/Transformable.hpp>

#include <vector>
#include <string>
#include <cassert>

namespace glen
{

	class Model : public Transformable
	{
	public:
		Model(void);
		~Model(void);

		void setMaterial(Material* material);

		bool loadFromFile(const std::string& path);

		void render();
		

	protected:

		Material*	m_material;

		MeshData*	m_meshdata;

		GLuint		m_vbo;
		GLuint		m_vao;

	};

}

#endif
#include <glen/Graphics/Model.hpp>
#include <glen/Graphics/Material.hpp>
#include <glen/Graphics/MeshLoader.hpp>

#include <glen/Graphics/Texture/Texture2D.hpp>

#include <glen/Graphics/ShaderProgram.hpp>
#include <glen/Graphics/Shader.hpp>

#include <glen/Graphics/Camera.hpp>

namespace glen
{
//////////////////////////////////////////////////
Model::Model(void) :
	m_vbo(0),
	m_vao(0),
	m_meshdata(NULL),
	m_material(NULL)
{
}

//////////////////////////////////////////////////
Model::~Model(void)
{
	if(m_vao != 0) glDeleteVertexArrays(1, &m_vao);
	if(m_vbo != 0) glDeleteBuffers(1, &m_vbo);
}

//////////////////////////////////////////////////
void Model::setMaterial(Material* material)
{
	m_material = material;
	assert(m_material != NULL && "Material can't be null");

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	m_material->_linkVertexAttrib();

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//////////////////////////////////////////////////
bool Model::loadFromFile(const std::string& path)
{
	m_meshdata = new(std::nothrow) MeshData();
	assert(m_meshdata != NULL && "Memory allocation for mesh data failed");

	// Check if memory allocation was successful
	if(!m_meshdata) return false;

	// Attempt to load the mesh file
	if(!MeshLoader::loadMesh(path, m_meshdata))
	{
		delete m_meshdata;
		m_meshdata = NULL;

		return false;
	}
	
	// Generate VAO and VBO
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_meshdata->data.size(), &m_meshdata->data[0], GL_STATIC_DRAW);
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}

//////////////////////////////////////////////////
void Model::render(glm::mat4 &transform)
{
	glBindVertexArray(m_vao);
	m_material->bind();

	//m_material->m_program->setUniform("u_time", GetTickCount() / 1000.f);

	Material::Matrices mat;
	mat.projection	= Camera::activeCamera()->getProjectionMatrix();
	mat.view		= Camera::activeCamera()->getMatrix();
	mat.model		= transform;

	m_material->setMatrices(mat);

	// Render model on screen
	glCheck(glDrawArrays(GL_TRIANGLES, 0, m_meshdata->drawCount));
	
	glBindVertexArray(0);
	m_material->unbind();
}

}
#include <glen/Graphics/Model.hpp>
#include <glen/Graphics/Camera.hpp>

#include <glen/Graphics/Texture.hpp>

#include <glen/Graphics/ShaderProgram.hpp>
#include <glen/Graphics/Shader.hpp>

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
void Model::setMaterial(Material& material)
{
	m_material = &material;
	assert(m_material != NULL && "Material can't be null");

	//m_material->bind();

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	m_material->_linkVertexAttrib();

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//m_material->unbind();
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

	// Create shaders
	/*Shader* vertexShader = new(std::nothrow) Shader();
	vertexShader->loadFromFile("shader.vert", Shader::Vertex);

	Shader* geometryShader = new(std::nothrow) Shader();
	geometryShader->loadFromFile("shader.geom", Shader::Geometry);

	Shader* fragmentShader = new(std::nothrow) Shader();
	fragmentShader->loadFromFile("shader.frag", Shader::Fragment);

	m_shaders.push_back(vertexShader);
	m_shaders.push_back(geometryShader);
	m_shaders.push_back(fragmentShader);

	// Link shader program
	m_program = new(std::nothrow) ShaderProgram();
	if(!m_program->compile(m_shaders))
	{
		return false;
	}

	// Link the vertex data with the shaders
	glEnableVertexAttribArray(m_program->attrib("position"));
	glCheck(glVertexAttribPointer(
			m_program->attrib("position"), 3, GL_FLOAT, GL_FALSE,
			sizeof(GLfloat) * 9, 0
		));

	glEnableVertexAttribArray(m_program->attrib("texcoord"));
	glCheck(glVertexAttribPointer(
			m_program->attrib("texcoord"), 3, GL_FLOAT, GL_FALSE,
			sizeof(GLfloat) * 9, (void*)(sizeof(GLfloat) * 3)
		));

	glEnableVertexAttribArray(m_program->attrib("normal"));
	glCheck(glVertexAttribPointer(
			m_program->attrib("normal"), 3, GL_FLOAT, GL_FALSE,
			sizeof(GLfloat) * 9, (void*)(sizeof(GLfloat) * 6)
		));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/

	return true;
}

//////////////////////////////////////////////////
void Model::render()
{
	glBindVertexArray(m_vao);
	//glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	// Set model material in use
	m_material->bind();

	m_material->m_program->setUniform("u_model", getMatrix());
	
	Camera* camera = Camera::activeCamera();

	m_material->m_program->setUniform("u_view", camera->getMatrix());
	m_material->m_program->setUniform("u_proj", camera->getProjectionMatrix());

	// Bind material textures
	m_material->_bindTextures();

	// Render model on screen
	glCheck(glDrawArrays(GL_TRIANGLES, 0, m_meshdata->drawCount));
	
	glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	m_material->unbind();
}

}
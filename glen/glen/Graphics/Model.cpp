#include <glen/Graphics/Model.hpp>
#include <glen/Graphics/Camera.hpp>
#include <glen/Graphics/Texture.hpp>

namespace glen
{
//////////////////////////////////////////////////
Model::Model(void) :
	m_program(NULL),
	m_vbo(0),
	m_vao(0),
	m_meshdata(NULL),
	m_texture(NULL)
{
}

//////////////////////////////////////////////////
Model::~Model(void)
{
	if(m_vao != 0) glDeleteVertexArrays(1, &m_vao);
	if(m_vbo != 0) glDeleteBuffers(1, &m_vbo);

	if(m_program != NULL)
	{
		delete m_program; m_program = NULL;
	}

	for(ShaderList::iterator it = m_shaders.begin();
		it != m_shaders.end(); ++it)
	{
		delete *it;
	}

	m_shaders.clear();
}

//////////////////////////////////////////////////
void Model::setTexture(Texture& texture)
{
	m_texture = &texture;
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
		return false;
	}
	
	// Generate VAO and VBO
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_meshdata->data.size(), &m_meshdata->data[0], GL_STATIC_DRAW);

	// Create shaders
	Shader* vertexShader = new(std::nothrow) Shader();
	vertexShader->loadFromFile("shader.vert", Shader::Vertex);

	Shader* fragmentShader = new(std::nothrow) Shader();
	fragmentShader->loadFromFile("shader.frag", Shader::Fragment);

	m_shaders.push_back(vertexShader);
	m_shaders.push_back(fragmentShader);

	// Link shader program
	m_program = new(std::nothrow) ShaderProgram();
	if(!m_program->compile(m_shaders))
	{
		return false;
	}

	// Link the vertex data with the shaders
	glEnableVertexAttribArray(m_program->attrib("position"));
	glCheck(
		glVertexAttribPointer(
			m_program->attrib("position"), 3, GL_FLOAT, GL_FALSE,
			sizeof(GLfloat) * 8, 0
		));

	glEnableVertexAttribArray(m_program->attrib("texcoord"));
	glCheck(
		glVertexAttribPointer(
			m_program->attrib("texcoord"), 2, GL_FLOAT, GL_FALSE,
			sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 3)
		));

	glEnableVertexAttribArray(m_program->attrib("normal"));
	glCheck(
		glVertexAttribPointer(
			m_program->attrib("normal"), 3, GL_FLOAT, GL_FALSE,
			sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 5)
		));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}

//////////////////////////////////////////////////
void Model::render()
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	m_program->use();

	m_program->setUniform("model", getMatrix());
	
	Camera* camera = Camera::activeCamera();

	m_program->setUniform("view", camera->getMatrix());
	m_program->setUniform("proj", camera->getProjectionMatrix());

	if(m_texture)
		m_texture->bind();

	glCheck(glDrawArrays(GL_TRIANGLES, 0, m_meshdata->drawCount));

	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_program->unUse();
}

}
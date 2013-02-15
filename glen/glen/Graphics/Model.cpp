#include <glen/Graphics/Model.hpp>

namespace glen
{
//////////////////////////////////////////////////
Model::Model(void) :
	m_program(NULL),
	m_vbo(0),
	m_vao(0),
	m_meshdata(NULL)
{
}

//////////////////////////////////////////////////
Model::~Model(void)
{
}

//////////////////////////////////////////////////
bool Model::loadFromFile(const std::string& path)
{
	m_meshdata = new(std::nothrow) MeshData();
	assert(m_meshdata != NULL && "Memory allocation for meshdata failed");

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_meshdata->drawCount, &m_meshdata->data[0], GL_STATIC_DRAW);

	// Create shaders
	Shader* vertexShader = new(std::nothrow) Shader();
	vertexShader->loadFromFile("shader.vert", Shader::Vertex);

	Shader* fragmentShader = new(std::nothrow) Shader();
	fragmentShader->loadFromFile("shader.frag", Shader::Fragment);

	m_shaders.push_back(vertexShader);
	m_shaders.push_back(fragmentShader);

	// Link shader program
	m_program = new(std::nothrow) ShaderProgram();
	m_program->compile(m_shaders);

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, 0);

	GLint normalAttrib = glGetAttribLocation(shaderProgram, "normal");
	glEnableVertexAttribArray(normalAttrib);
	glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 3));

	GLint texcoordAttrib = glGetAttribLocation(shaderProgram, "texCoord");
	glEnableVertexAttribArray(texcoordAttrib);
	glVertexAttribPointer(texcoordAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 6));
}

}
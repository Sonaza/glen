#include <glen/Graphics/Sprite.hpp>
#include <glen/Graphics/Texture/Texture2D.hpp>

#include <glen/Graphics/Shader.hpp>
#include <glen/Graphics/ShaderProgram.hpp>

#define ATTRIB_POINTER(NAME, SIZE, STRIDE, OFFSET) \
	do { glEnableVertexAttribArray(m_program->attrib(NAME)); \
		glCheck(glVertexAttribPointer( \
		m_program->attrib(NAME), SIZE, GL_FLOAT, GL_FALSE, \
		sizeof(GLfloat) * STRIDE, (void*)(sizeof(GLfloat) * OFFSET) \
	)); } while(0) \

using namespace glen;

ShaderProgramPtr Sprite::m_program = NULL;

////////////////////////////////////////////////////
Sprite::Sprite() :
	m_texture(NULL)
{
	// Load the static shader program if it has not been loaded yet
	if(!m_program)
	{
		_loadshaders("res/sprite.vert", "res/sprite.frag");
	}
}

////////////////////////////////////////////////////
Sprite::~Sprite()
{
	
}

////////////////////////////////////////////////////
void Sprite::setTexture2D(Texture2D* texture)
{
	assert(texture != NULL && "Texture must be set");
	
	m_texture = texture;

	Vector2f size = static_cast<Vector2f>(m_texture->getSize());

	m_data.clear();

	GLfloat vertexdata[] = {
		0.f,	0.f,	0.f, 0.f, 1.f, 0.f,	// Top left
		0.f,	size.y,	0.f, 0.f, 0.f, 0.f,	// Bottom left
		size.x,	0.f,	0.f, 1.f, 1.f, 0.f,	// Top right
		size.x,	0.f,	0.f, 1.f, 1.f, 0.f,	// Top right
		0.f,	size.y,	0.f, 0.f, 0.f, 0.f,	// Bottom left
		size.x, size.y, 0.f, 1.f, 0.f, 0.f	// Bottom right
	};

	_generateObjects();

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexdata), &vertexdata, GL_STATIC_DRAW);

	ATTRIB_POINTER("a_position", 3, 6, 0);
	ATTRIB_POINTER("a_texcoord", 3, 6, 3);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

////////////////////////////////////////////////////
void Sprite::render(glm::mat4 &transform)
{

}

////////////////////////////////////////////////////
void Sprite::_generateObjects()
{
	// Generate VAO and VBO
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

////////////////////////////////////////////////////
bool Sprite::_loadshaders(const std::string& vertex, const std::string& fragment)
{
	// Create shaders
	Shader* vertexShader = new(std::nothrow) Shader();
	vertexShader->loadFromFile(vertex, Shader::Vertex);

	//Shader* geometryShader = new(std::nothrow) Shader();
	//geometryShader->loadFromFile(geometry, Shader::Geometry);

	Shader* fragmentShader = new(std::nothrow) Shader();
	fragmentShader->loadFromFile(fragment, Shader::Fragment);

	m_shaders.push_back(vertexShader);
	//m_shaders.push_back(geometryShader);
	m_shaders.push_back(fragmentShader);

	// Attempt to allocate and link shader program
	m_program.reset(new(std::nothrow) ShaderProgram);
	if(!m_program->compile(m_shaders))
	{
		m_shaders.clear();

		delete vertexShader;
		delete fragmentShader;

		m_program.release();

		return false;
	}

	m_program->use();

	// Set texturing uniforms
	m_program->setUniform("u_texture", 0);

	m_program->unUse();

	return true;
}
#include <glen/Graphics/Material.hpp>

#define ATTRIB_POINTER(NAME, SIZE, STRIDE, OFFSET) \
	glEnableVertexAttribArray(m_program->attrib(NAME)); \
	glCheck(glVertexAttribPointer( \
		m_program->attrib(NAME), SIZE, GL_FLOAT, GL_FALSE, \
		sizeof(GLfloat) * STRIDE, (void*)(sizeof(GLfloat) * OFFSET) \
	)) \

namespace glen
{

///////////////////////////////////////////////////
Material::Material(void) :
	m_program(NULL)
{
}

///////////////////////////////////////////////////
Material::~Material(void)
{
	if(m_program != NULL)
	{
		delete m_program;
		m_program = NULL;
	}

	for(ShaderList::iterator it = m_shaders.begin();
		it != m_shaders.end(); ++it)
	{
		delete *it;
	}

	m_shaders.clear();
}

///////////////////////////////////////////////////
void Material::bind() const
{
	m_program->use();

}

///////////////////////////////////////////////////
void Material::setTexture(TextureType type, const Texture& texture)
{
	m_textures.insert(std::make_pair(type, &texture));
}

///////////////////////////////////////////////////
bool Material::_loadshaders(const std::string& vertex, const std::string& fragment)
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
	m_program = new(std::nothrow) ShaderProgram();
	if(!m_program->compile(m_shaders))
	{
		m_shaders.clear();

		delete vertexShader;
		delete fragmentShader;

		return false;
	}
}

///////////////////////////////////////////////////
void Material::_linkVertexAttrib()
{
	ATTRIB_POINTER("a_position", 3, 9, 0);
	ATTRIB_POINTER("a_texcoord", 3, 9, 3);
	ATTRIB_POINTER("a_normal", 3, 9, 6);
}

}
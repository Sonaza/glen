#include <glen/Graphics/Material.hpp>
#include <glen/Graphics/Texture.hpp>

#define ATTRIB_POINTER(NAME, SIZE, STRIDE, OFFSET) \
	do { glEnableVertexAttribArray(m_program->attrib(NAME)); \
	glCheck(glVertexAttribPointer( \
		m_program->attrib(NAME), SIZE, GL_FLOAT, GL_FALSE, \
		sizeof(GLfloat) * STRIDE, (void*)(sizeof(GLfloat) * OFFSET) \
	)); } while(0) \

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
	assert(m_program != NULL && "Program must be initialised");
	m_program->use();
}

///////////////////////////////////////////////////
void Material::unbind() const
{
	assert(m_program != NULL && "Program must be initialised");
	m_program->unUse();
}

///////////////////////////////////////////////////
void Material::setTexture(TextureType type, Texture& texture)
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

		delete m_program;
		m_program = NULL;

		return false;
	}

	m_program->use();

	// Set texturing uniforms
	m_program->setUniform("u_diffuse", Diffuse);
	m_program->setUniform("u_normal", Normal);
	m_program->setUniform("u_specular", Specular);

	m_program->unUse();

	return true;
}

///////////////////////////////////////////////////
void Material::_linkVertexAttrib()
{
	ATTRIB_POINTER("a_position", 3, 9, 0);
	ATTRIB_POINTER("a_texcoord", 3, 9, 3);
	ATTRIB_POINTER("a_normal", 3, 9, 6);
}

///////////////////////////////////////////////////
void Material::_bindTextures()
{
	for(std::map<TextureType, Texture*>::iterator it = m_textures.begin();
		it != m_textures.end(); ++it)
	{
		glActiveTexture(GL_TEXTURE0 + it->first);
		it->second->bind();
	}
}

}
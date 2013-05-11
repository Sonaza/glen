#include <glen/Graphics/ShaderManager.hpp>
#include <glen/System/ErrorStream.hpp>

using namespace glen;

namespace
{
	ShaderAssetList m_shaders;
}

////////////////////////////////////////////////////
void ShaderManager::unload()
{
	/*for(ShaderAssetList::iterator it = m_shaders.begin(); it != m_shaders.end(); ++it)
	{
		delete *it;
	}

	m_shaders.clear();*/
}

////////////////////////////////////////////////////
ShaderAsset* ShaderManager::loadShader(const std::string &vertex, const std::string &fragment, ShaderDefines defines)
{
	ShaderAsset* asset = new ShaderAsset;
	
	asset->defines = defines;

	// Load Vertex Shader
	asset->vertex = new(std::nothrow) Shader(defines);
	asset->vertex->loadFromFile(vertex, Shader::Vertex);

	// Load Fragment Shader
	asset->fragment = new(std::nothrow) Shader(defines);
	asset->fragment->loadFromFile(fragment, Shader::Fragment);

	std::vector<Shader*> shaders;
	shaders.push_back(asset->vertex);
	shaders.push_back(asset->fragment);

	// Attempt to allocate and link shader program
	asset->program = new(std::nothrow) ShaderProgram();
	assert(asset->program != NULL && "Allocation failed");

	if(asset->program && !asset->program->compile(shaders))
	{
		err << "Shader compilation failed. See console for more information" << ErrorStream::error;

		// Shader compilation failed
		delete asset;

		return NULL;
	}

	m_shaders.push_back(asset);

	return asset;
}
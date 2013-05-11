#include <glen/Graphics/MaterialFactory.hpp>
#include <glen/Graphics/Material.hpp>

#include <glen/System/AssetManager.hpp>
#include <glen/System/Assets/Texture2DAsset.hpp>

#include <glen/System/ErrorStream.hpp>

using namespace glen;

//////////////////////////////////////////////////////
MaterialFactory::MaterialFactory(void)
{
}

//////////////////////////////////////////////////////
MaterialFactory::~MaterialFactory(void)
{

}

//////////////////////////////////////////////////////
Material* MaterialFactory::plain()
{
	Material* result = new Material();

	result->_loadshaders("res/diffuse.vert", "res/diffuse.frag");

	return result;
}

//////////////////////////////////////////////////////
Material* MaterialFactory::diffuse(const std::string &diffuse)
{
	Material* result = NULL;
	Texture2D* texDiffuse = _getTexture2D(diffuse);

	// Failure in asset loading
	if(texDiffuse)
	{
		result = new Material();

		ShaderDefines def;
		def.push_back("TEXTURE_DIFFUSE");

		if(!result->_loadshaders("res/diffuse.vert", "res/diffuse.frag", def))
		{
			err << "Error loading/compiling diffuse shaders" << ErrorStream::error;

			delete result;
			return NULL;
		}

		result->setTexture(Texture::Diffuse, texDiffuse);
	}

	return result;
}

//////////////////////////////////////////////////////
Material* MaterialFactory::specular(const std::string &diffuse)
{
	Material* result = NULL;
	Texture2D* texDiffuse = _getTexture2D(diffuse);

	// Failure in asset loading
	if(texDiffuse)
	{
		result = new Material();

		ShaderDefines def;
		def.push_back("TEXTURE_DIFFUSE");
		def.push_back("SPECULAR");

		if(!result->_loadshaders("res/diffuse.vert", "res/diffuse.frag", def))
		{
			err << "Error loading/compiling diffuse shaders" << ErrorStream::error;

			delete result;
			return NULL;
		}

		result->setTexture(Texture::Diffuse, texDiffuse);
	}

	return result;
}

//////////////////////////////////////////////////////
Material* MaterialFactory::skybox(const std::string &cubemap)
{
	Material* result = NULL;
	TextureCubemap* texCubemap = AssetManager::getTextureCubemap(cubemap);

	if(texCubemap)
	{
		result = new Material();
		result->_loadshaders("res/skybox.vert", "res/skybox.frag");
		
		result->setTexture(Texture::Diffuse, texCubemap);
	}
	else
	{
		err << "Unable to retrieve Cubemap '" << cubemap << "'." << ErrorStream::error;
	}

	return result;
}

/*
//////////////////////////////////////////////////////
Material* MaterialFactory::bumped_diffuse(const std::string &diffuse, const std::string &normal)
{
	Material* result = new Material();

	result->_loadshaders("res/diffuse.vert", "res/diffuse.frag");

	Texture2D* texDiffuse = _getTexture2D(diffuse);
	Texture2D* texNormal = _getTexture2D(normal);

	// Failure in asset loading
	if(!texDiffuse || !texNormal)
	{
		delete result;
		return NULL;
	}

	result->setTexture<Texture2D::Diffuse>(*texDiffuse);
	result->setTexture<Texture::Normal>(*texNormal);

	return result;
}*/

//////////////////////////////////////////////////////
Texture2D* MaterialFactory::_getTexture2D(const std::string &id)
{
	Texture2D* result = NULL;
	Texture2DAsset* asset = AssetManager::getTexture2D(id);

	// Failure in asset loading
	if(!asset)
	{
		err << "Unable to retrieve Texture '" << id << "'." << ErrorStream::error;
	}
	else
	{
		result = asset->getAsset();
	}

	return result;
}

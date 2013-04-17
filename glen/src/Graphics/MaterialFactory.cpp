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
Material* MaterialFactory::diffuse(const std::string &diffuse)
{
	Material* result = new(std::nothrow) Material();

	if(result)
	{
		ShaderDefines def;
		def.push_back("TEXTURE_DIFFUSE");

		result->_loadshaders("res/diffuse.vert", "res/diffuse.frag", def);

		Texture2D* texDiffuse = _getTexture(diffuse);

		// Failure in asset loading
		if(!texDiffuse)
		{
			delete result;
			return NULL;
		}

		result->setTexture<Texture2D::Diffuse>(*texDiffuse);
	}

	return result;
}

//////////////////////////////////////////////////////
Material* MaterialFactory::skyplane(const std::string &skyplane)
{
	Material* result = new(std::nothrow) Material();

	if(result)
	{
		result->_loadshaders("res/skybox.vert", "res/skybox.frag");

		Texture2D* texDiffuse = _getTexture(skyplane);

		// Failure in asset loading
		if(!texDiffuse)
		{
			delete result;
			return NULL;
		}

		result->setTexture<Texture2D::Diffuse>(*texDiffuse);
	}

	return result;
}

//////////////////////////////////////////////////////
Material* MaterialFactory::bumped_diffuse(const std::string &diffuse, const std::string &normal)
{
	Material* result = new(std::nothrow) Material();

	if(result)
	{
		result->_loadshaders("res/diffuse.vert", "res/diffuse.frag");

		Texture2D* texDiffuse = _getTexture(diffuse);
		Texture2D* texNormal = _getTexture(normal);

		// Failure in asset loading
		if(!texDiffuse || !texNormal)
		{
			delete result;
			return NULL;
		}

		result->setTexture<Texture2D::Diffuse>(*texDiffuse);
		result->setTexture<Texture2D::Normal>(*texNormal);
	}

	return result;
}

//////////////////////////////////////////////////////
Texture2D* MaterialFactory::_getTexture(const std::string &id)
{
	Texture2D* result = NULL;

	Texture2DAsset* asset = AssetManager::getTexture2D(id);
	assert(asset != NULL && "Texture asset not found");

	// Failure in asset loading
	if(!asset)
	{
		err << "Unable to retrieve Texture2D '" << id << "'." << ErrorStream::error;
	}
	else
	{
		result = asset->getAsset();
	}

	return result;
}

#include <glen/System/AssetManager.hpp>

#include <glen/System/Assets/Texture2DAsset.hpp>
#include <glen/Graphics/Texture/TextureCubemap.hpp>
#include <glen/System/Assets/ModelAsset.hpp>

#include <glen/Graphics/Texture/Texture.hpp>

#include <glen/Graphics/Material.hpp>
#include <glen/Graphics/MaterialFactory.hpp>

#include <glen/Graphics/MeshLoader.hpp>

using namespace glen;

namespace
{
	struct Textures
	{
		Texture2DAssetList	texture2d;
		TextureCubemapList	texturecubemaps;
	} m_textures;
	
	MeshDataList		m_meshdata;
	ModelAssetList		m_models;
	MaterialList		m_materials;
}

////////////////////////////////////////////////////
void AssetManager::unload()
{
	for(Texture2DAssetList::iterator it = m_textures.texture2d.begin(); it != m_textures.texture2d.end(); ++it)
	{
		delete it->second;
	}

	m_textures.texture2d.clear();

	///////////////////////////

	for(TextureCubemapList::iterator it = m_textures.texturecubemaps.begin(); it != m_textures.texturecubemaps.end(); ++it)
	{
		delete it->second;
	}

	m_textures.texturecubemaps.clear();

	///////////////////////////

	for(MeshDataList::iterator it = m_meshdata.begin(); it != m_meshdata.end(); ++it)
	{
		delete it->second;
	}

	m_meshdata.clear();

	///////////////////////////

	for(ModelAssetList::iterator it = m_models.begin(); it != m_models.end(); ++it)
	{
		delete *it;
	}

	m_models.clear();

	///////////////////////////

	for(MaterialList::iterator it = m_materials.begin(); it != m_materials.end(); ++it)
	{
		delete *it;
	}

	m_materials.clear();
}

////////////////////////////////////////////////////
void AssetManager::freeSceneAssets()
{
	for(Texture2DAssetList::iterator it = m_textures.texture2d.begin();
		it != m_textures.texture2d.end();)
	{
		if(it->second->isSceneBound())
		{
			delete it->second;
			it = m_textures.texture2d.erase(it);
		}
		else
		{
			++it;
		}
	}
}

//////////////////////////////////////////////////
Texture2DAsset* AssetManager::loadTexture2D(const std::string &id, const std::string &path, const bool scenebound)
{
	Texture2DAsset* result = getTexture2D(id);

	if(result == NULL)
	{
		result = new(std::nothrow) Texture2DAsset(path);
		assert(result && "Allocation failed");

		if(result)
		{
			result->setSceneBound(scenebound);

			result->loadAsset();

			m_textures.texture2d.insert(std::make_pair(id, result));
		}
	}

	return result;
}

//////////////////////////////////////////////////
Texture2DAsset* AssetManager::getTexture2D(const std::string &id)
{
	Texture2DAsset* result = NULL;

	Texture2DAssetList::iterator it = m_textures.texture2d.find(id);
	if(it != m_textures.texture2d.end())
	{
		result = it->second;
	}

	return result;
}

//////////////////////////////////////////////////
TextureCubemap* AssetManager::loadTextureCubemap(const std::string &assetID, const std::string& left, const std::string& right, const std::string& top, const std::string& bottom, const std::string& front, const std::string& back)
{
	TextureCubemap* result = getTextureCubemap(assetID);

	if(result == NULL)
	{
		result = new TextureCubemap();

		if(!result->loadFromFile(left, right, top, bottom, front, back))
		{
			delete result;
			result = NULL;
		}
		else
		{
			m_textures.texturecubemaps.insert(std::make_pair(assetID, result));
		}
	}

	return result;
}

//////////////////////////////////////////////////
TextureCubemap* AssetManager::getTextureCubemap(const std::string &assetID)
{
	TextureCubemap* result = NULL;

	TextureCubemapList::iterator it = m_textures.texturecubemaps.find(assetID);
	if(it != m_textures.texturecubemaps.end())
	{
		result = it->second;
	}

	return result;
}

//////////////////////////////////////////////////
MeshData* AssetManager::loadMesh(const std::string &id, const std::string &path)
{
	MeshData* result = NULL;
	result = new MeshData();
	assert(result && "Allocation failed");

	if(!MeshLoader::loadMesh(path, result))
	{
		delete result;
		result = NULL;
	}
	else
	{
		m_meshdata.insert(std::make_pair(id, result));
	}
	
	return result;
}

//////////////////////////////////////////////////
MeshData* AssetManager::getMesh(const std::string &id)
{
	MeshData* result = NULL;

	MeshDataList::iterator it = m_meshdata.find(id);
	if(it != m_meshdata.end())
	{
		result = it->second;
	}

	return result;
}

//////////////////////////////////////////////////
ModelAsset* AssetManager::createModel(const std::string &path, const bool scenebound)
{
	ModelAsset* result = NULL;
	result = new ModelAsset(path);

	result->setSceneBound(scenebound);
	result->loadAsset();

	m_models.push_back(result);

	return result;
}

//////////////////////////////////////////////////
Material* AssetManager::createMaterial(const Material::Type type, MaterialAssets assets)
{
	Material* material = NULL;

	switch(type)
	{
	case Material::Plain:
		material = MaterialFactory::plain();
		break;
	case Material::Diffuse:
		material = MaterialFactory::diffuse(assets[Texture::Diffuse]);
		break;
	case Material::SpecularDiffuse:
		material = MaterialFactory::specular(assets[Texture::Diffuse]);
		break;
	case Material::Skybox:
		material = MaterialFactory::skybox(assets[Texture::Diffuse]);
		break;
	default:	return NULL; break;
	}

	assert(material != NULL);

	m_materials.push_back(material);

	return material;
}

//////////////////////////////////////////////////
Material* AssetManager::createMaterial(const Material::Type type, const std::string& diffuse)
{
	MaterialAssets assets;
	assets.insert(std::make_pair(Texture::Diffuse, diffuse));

	return createMaterial(type, assets);
}

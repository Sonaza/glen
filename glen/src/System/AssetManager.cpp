#include <glen/System/AssetManager.hpp>

#include <glen/System/Assets/Texture2DAsset.hpp>
#include <glen/System/Assets/ModelAsset.hpp>
#include <glen/System/Assets/MaterialAsset.hpp>

using namespace glen;

namespace
{
	Texture2DAssetList	m_textures;
	ModelAssetList		m_models;
	MaterialList		m_materials;
}

////////////////////////////////////////////////////
void AssetManager::unload()
{
	for(Texture2DAssetList::iterator it = m_textures.begin();
		it != m_textures.end(); ++it)
	{
		delete it->second;
	}

	m_textures.clear();

	///////////////////////////

	for(ModelAssetList::iterator it = m_models.begin();
		it != m_models.end(); ++it)
	{
		delete it->second;
	}

	m_models.clear();

	///////////////////////////

	for(MaterialList::iterator it = m_materials.begin();
		it != m_materials.end(); ++it)
	{
		delete it->second;
	}

	m_materials.clear();
}

////////////////////////////////////////////////////
void AssetManager::freeSceneAssets()
{
	for(Texture2DAssetList::iterator it = m_textures.begin();
		it != m_textures.end();)
	{
		if(it->second->isSceneBound())
		{
			delete it->second;
			it = m_textures.erase(it);
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
	Texture2DAsset* result = NULL;
	result = new(std::nothrow) Texture2DAsset(path);
	assert(result && "Allocation failed");

	if(result)
	{
		result->setSceneBound(scenebound);

		result->loadAsset();

		m_textures.insert(std::make_pair(id, result));
	}

	return result;
}

//////////////////////////////////////////////////
Texture2DAsset* AssetManager::getTexture2D(const std::string &id)
{
	Texture2DAsset* result = NULL;

	Texture2DAssetList::iterator it = m_textures.find(id);
	if(it != m_textures.end())
	{
		result = it->second;
	}

	return result;
}

//////////////////////////////////////////////////
ModelAsset* AssetManager::loadModel(const std::string &id, const std::string &path, const bool scenebound)
{
	ModelAsset* result = NULL;
	result = new(std::nothrow) ModelAsset(path);
	assert(result && "Allocation failed");

	if(result)
	{
		result->setSceneBound(scenebound);

		result->loadAsset();

		m_models.insert(std::make_pair(id, result));
	}

	return result;
}

//////////////////////////////////////////////////
ModelAsset* AssetManager::getModel(const std::string &id)
{
	ModelAsset* result = NULL;

	ModelAssetList::iterator it = m_models.find(id);
	if(it != m_models.end())
	{
		result = it->second;
	}

	return result;
}

//////////////////////////////////////////////////
Material* AssetManager::createMaterial(const std::string &id, Material* material)
{
	assert(material != NULL && "Material can't be null");

	m_materials.insert(std::make_pair(id, material));

	return material;
}

//////////////////////////////////////////////////
Material* AssetManager::getMaterial(const std::string &id)
{
	Material* result = NULL;

	MaterialList::iterator it = m_materials.find(id);
	if(it != m_materials.end())
	{
		result = it->second;
	}

	return result;
}

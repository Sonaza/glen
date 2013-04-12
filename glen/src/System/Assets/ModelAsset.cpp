#include <glen/System/AssetManager.hpp>
#include <glen/System/Assets/ModelAsset.hpp>

#include <glen/System/ErrorStream.hpp>

using namespace glen;

////////////////////////////////////////////////////
ModelAsset::ModelAsset(const std::string &path) :
	TAsset(path)
{
}

////////////////////////////////////////////////////
ModelAsset::~ModelAsset()
{
}

////////////////////////////////////////////////////
bool ModelAsset::loadAsset()
{
	assert(!m_loaded && "Texture has already been loaded");
	assert(!m_filename.empty() && "Must have file name");

	m_asset = new(std::nothrow) Model();
	assert(m_asset && "Allocation failed");

	if(!m_asset->loadFromFile(m_filename))
	{
		err << "Unable to open model: " << m_filename << ErrorStream::error;

		return false;
	}

	m_loaded = true;

	return true;
}

////////////////////////////////////////////////////
void ModelAsset::setMaterial(const std::string &assetID)
{
	Material* material = AssetManager::getMaterial(assetID);

	if(material)
	{
		m_asset->setMaterial(material);
	}
}
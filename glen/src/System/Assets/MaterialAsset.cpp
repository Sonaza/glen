#include <glen/System/Assets/MaterialAsset.hpp>
#include <glen/System/ErrorStream.hpp>

namespace glen
{

////////////////////////////////////////////////////
MaterialAsset::MaterialAsset(const std::string &path) :
	TAsset(path)
{
}

////////////////////////////////////////////////////
MaterialAsset::~MaterialAsset()
{
}

////////////////////////////////////////////////////
bool MaterialAsset::loadAsset()
{
	assert(!m_loaded && "Texture has already been loaded");
	assert(!m_filename.empty() && "Must have file name");

	/*m_asset = new(std::nothrow) Material();
	assert(m_asset && "Allocation failed");

	if(!m_asset->loadFromFile(m_filename))
	{
		err << "Unable to open model: " << m_filename << ErrorStream::error;

		return false;
	}

	m_loaded = true;*/

	return true;
}

}
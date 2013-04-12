#include <glen/System/Assets/Texture2DAsset.hpp>
#include <glen/System/ErrorStream.hpp>

namespace glen
{

////////////////////////////////////////////////////
Texture2DAsset::Texture2DAsset(const std::string &path) :
	TAsset(path)
{
}

////////////////////////////////////////////////////
Texture2DAsset::~Texture2DAsset()
{
}

////////////////////////////////////////////////////
bool Texture2DAsset::loadAsset()
{
	assert(!m_loaded && "Texture has already been loaded");
	assert(!m_filename.empty() && "Must have file name");

	m_asset = new(std::nothrow) Texture2D();
	assert(m_asset && "Allocation failed");

	if(!m_asset->loadFromFile(m_filename))
	{
		err << "Unable to open texture: " << m_filename << ErrorStream::error;

		return false;
	}

	m_loaded = true;

	return true;
}

}
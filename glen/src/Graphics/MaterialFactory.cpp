#include <glen/Graphics/MaterialFactory.hpp>
#include <glen/Graphics/Material.hpp>

#include <glen/System/AssetManager.hpp>
#include <glen/System/Assets/Texture2DAsset.hpp>

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
/*void MaterialFactory::uninit()
{
	for(std::vector<Material*>::iterator it = _materials.begin();
		it != _materials.end(); ++it)
	{
		delete *it;
	}

	_materials.clear();
}*/

//////////////////////////////////////////////////////
/*void MaterialFactory::unload(Material* material)
{
	assert(material != NULL && "Must not be null");

	std::vector<Material*>::iterator it = std::find(
		_materials.begin(), _materials.end(), material);

	if(it != _materials.end())
	{
		delete *it;
		_materials.erase(it);
	}
}*/

//////////////////////////////////////////////////////
Material* MaterialFactory::diffuse(const std::string &diffuse)
{
	Material* result = new(std::nothrow) Material();

	if(result)
	{
		result->_loadshaders("res/diffuse.vert", "res/diffuse.frag");

		Texture2DAsset* ta = AssetManager::getTexture2D("diffuse");
		result->setTexture<Texture2D::Diffuse>(*ta->getAsset());

		//_materials.push_back(result);
	}

	return result;
}

#include <glen/Graphics/MaterialFactory.hpp>


namespace glen
{

namespace
{
	std::vector<Material*>	_materials;
	MaterialFactory* _materialfactory = NULL;
}

//////////////////////////////////////////////////////
MaterialFactory::MaterialFactory(void)
{
}

//////////////////////////////////////////////////////
MaterialFactory::~MaterialFactory(void)
{

}

//////////////////////////////////////////////////////
void MaterialFactory::deinit()
{
	for(std::vector<Material*>::iterator it = _materials.begin();
		it != _materials.end(); ++it)
	{
		delete *it;
	}

	_materials.clear();
}

//////////////////////////////////////////////////////
void MaterialFactory::unload(Material* material)
{
	assert(material != NULL && "Must not be null");

	std::vector<Material*>::iterator it = std::find(
		_materials.begin(), _materials.end(), material);

	if(it != _materials.end())
	{
		delete *it;
		_materials.erase(it);
	}
}

//////////////////////////////////////////////////////
Material* MaterialFactory::diffuse(Texture2D& diffuse)
{
	Material* result = new(std::nothrow) Material();

	if(result)
	{
		result->_loadshaders("res/diffuse.vert", "res/diffuse.frag");
		result->setTexture<Texture2D::Diffuse>(diffuse);

		_materials.push_back(result);
	}

	return result;
}

}
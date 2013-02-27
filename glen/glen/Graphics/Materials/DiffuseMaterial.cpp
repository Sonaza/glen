#include <glen/Graphics/Materials/DiffuseMaterial.hpp>

namespace glen
{

///////////////////////////////////////////////////////	
DiffuseMaterial::DiffuseMaterial(void) :
	Material()
{
	_loadshaders("res/diffuse.vert", "res/diffuse.frag");
}

}
#include <glen/Graphics/ShaderAsset.hpp>

using namespace glen;

////////////////////////////////////////////////////
ShaderAsset::ShaderAsset() :
	 vertex(0), fragment(0), program(0)
{
}

////////////////////////////////////////////////////
ShaderAsset::~ShaderAsset()
{
	if(vertex)		delete vertex;
	if(fragment)	delete vertex;
	if(program)		delete program;
}
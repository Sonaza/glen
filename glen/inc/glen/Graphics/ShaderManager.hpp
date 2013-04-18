#ifndef GLEN_SHADERMANAGER_HPP
#define GLEN_SHADERMANAGER_HPP

#include <glen/opengl.hpp>

#include <string>
#include <vector>

#include <glen/Graphics/ShaderAsset.hpp>

namespace glen
{
	
	//typedef std::tr1::unordered_map<std::string, ShaderAsset*> ShaderAssetList;
	typedef std::vector<ShaderAsset*> ShaderAssetList;

	namespace ShaderManager
	{
		extern void unload();

		extern ShaderAsset* loadShader(const std::string &vertex, const std::string &fragment, ShaderDefines defines);
	}
	
}

#endif GLEN_SHADERMANAGER_HPP

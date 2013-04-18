#ifndef GLEN_SHADER_ASSET_HPP
#define GLEN_SHADER_ASSET_HPP

#include <glen/Graphics/Shader.hpp>
#include <glen/Graphics/ShaderProgram.hpp>

namespace glen
{

	class ShaderAsset
	{
	public:
		ShaderAsset();
		~ShaderAsset();

		Shader*			vertex;
		Shader*			fragment;
		ShaderProgram*	program;

		ShaderDefines	defines;
	};

}

#endif
#ifndef GLEN_TEXTURE2D_ASSET_HPP
#define GLEN_TEXTURE2D_ASSET_HPP

#include <glen/System/Assets/TAsset.hpp>
#include <glen/Graphics/Texture/Texture2D.hpp>

namespace glen
{
	
	class Texture2DAsset : public TAsset<Texture2D>
	{
	public:
		Texture2DAsset(const std::string &path);
		~Texture2DAsset();

		bool loadAsset();

	};
	
}

#endif GLEN_TEXTURE2D_ASSET_HPP

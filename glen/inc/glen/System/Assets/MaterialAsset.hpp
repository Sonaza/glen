#ifndef GLEN_MATERIAL_ASSET_HPP
#define GLEN_MATERIAL_ASSET_HPP

#include <glen/System/Assets/TAsset.hpp>
#include <glen/Graphics/Material.hpp>

namespace glen
{
	
	class MaterialAsset : public TAsset<Material>
	{
	public:
		MaterialAsset(const std::string &path);
		~MaterialAsset();

		bool loadAsset();

	};
	
}

#endif GLEN_MATERIAL_ASSET_HPP

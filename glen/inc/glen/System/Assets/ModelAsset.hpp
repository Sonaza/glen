#ifndef GLEN_MODEL_ASSET_HPP
#define GLEN_MODEL_ASSET_HPP

#include <glen/System/Assets/TAsset.hpp>
#include <glen/Graphics/Model.hpp>

namespace glen
{
	
	class Material;

	class ModelAsset : public TAsset<Model>
	{
	public:
		ModelAsset(const std::string &path);
		~ModelAsset();

		bool loadAsset();

		ModelAsset* setMaterial(Material* material);

	};
	
}

#endif GLEN_MODEL_ASSET_HPP

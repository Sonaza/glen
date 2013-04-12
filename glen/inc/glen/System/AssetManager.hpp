#ifndef GLEN_ASSET_MANAGER_HPP
#define GLEN_ASSET_MANAGER_HPP

#include <string>
#include <map>

namespace glen
{

	class Texture2DAsset;
	class Material;
	class ModelAsset;

	typedef std::map<const std::string, Texture2DAsset*>	Texture2DAssetList;
	typedef std::map<const std::string, Material*>			MaterialList;
	typedef std::map<const std::string, ModelAsset*>		ModelAssetList;

	namespace AssetManager
	{

		void unload();
		void freeSceneAssets();

		Texture2DAsset* loadTexture2D(const std::string &assetID, const std::string &path, const bool scenebound = true);
		Texture2DAsset* getTexture2D(const std::string &assetID);

		ModelAsset* loadModel(const std::string &assetID, const std::string &path, const bool scenebound = true);
		ModelAsset* getModel(const std::string &assetID);

		Material* createMaterial(const std::string &assetID, Material* material);
		Material* getMaterial(const std::string &assetID);

	}

}

#endif

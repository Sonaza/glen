#ifndef GLEN_ASSET_MANAGER_HPP
#define GLEN_ASSET_MANAGER_HPP

#include <string>
#include <vector>
#include <map>

#include <glen/Graphics/Material.hpp>

namespace glen
{

	class Texture2DAsset;
	class TextureCubemap;
	class MeshData;
	class Material;
	class ModelAsset;

	typedef std::map<const std::string, Texture2DAsset*>	Texture2DAssetList;
	typedef std::map<const std::string, TextureCubemap*>	TextureCubemapList;
	typedef std::map<const std::string, MeshData*>			MeshDataList;
	typedef std::vector<Material*>							MaterialList;
	typedef std::map<const std::string, ModelAsset*>		ModelAssetList;

	typedef std::map<Texture::Type, std::string>			MaterialAssets;

	namespace AssetManager
	{

		void unload();
		void freeSceneAssets();

		Texture2DAsset* loadTexture2D(const std::string &assetID, const std::string &path, const bool scenebound = true);
		Texture2DAsset* getTexture2D(const std::string &assetID);

		TextureCubemap* loadTextureCubemap(const std::string &assetID, const std::string& left, const std::string& right, const std::string& top, const std::string& bottom, const std::string& front, const std::string& back);
		TextureCubemap* getTextureCubemap(const std::string &assetID);

		MeshData* loadMesh(const std::string &assetID, const std::string &path);
		MeshData* getMesh(const std::string &assetID);

		ModelAsset* loadModel(const std::string &assetID, const std::string &path, const bool scenebound = true);
		ModelAsset* getModel(const std::string &assetID);

		Material* createMaterial(const Material::Type type, const std::string& diffuse);
		Material* createMaterial(const Material::Type type, MaterialAssets assets);

	}

}

#endif

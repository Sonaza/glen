#ifndef GLEN_MATERIALFACTORY_HPP
#define GLEN_MATERIALFACTORY_HPP

#include <cassert>
#include <string>

namespace glen
{

	class Material;
	class Texture2D;

	class MaterialFactory
	{
	public:
		MaterialFactory(void);
		~MaterialFactory(void);

		//static void uninit();

		//static void unload(Material* material);

		static Material* diffuse(const std::string &diffuse);
		//static Material* bumped_diffuse(const std::string &diffuse, const std::string &normal);

		static Material* skyplane(const std::string &diffuse);

		static Material* skybox(const std::string &diffuse);

	private:

		static Texture2D* _getTexture(const std::string &id);
	};

}

#endif

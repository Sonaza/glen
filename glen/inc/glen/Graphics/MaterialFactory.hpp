#ifndef GLEN_MATERIALFACTORY_HPP
#define GLEN_MATERIALFACTORY_HPP

#include <cassert>
#include <string>

namespace glen
{

	class Material;

	class MaterialFactory
	{
	public:
		MaterialFactory(void);
		~MaterialFactory(void);

		//static void uninit();

		//static void unload(Material* material);

		static Material* diffuse(const std::string &diffuse);

		static Material* skyplane(const std::string &skyplane);
	};

}

#endif

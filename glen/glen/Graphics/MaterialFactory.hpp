#ifndef GLEN_MATERIALFACTORY_HPP
#define GLEN_MATERIALFACTORY_HPP

#include <cassert>
#include <vector>
#include <algorithm>

namespace glen
{

	class Texture2D;
	class Material;

	class MaterialFactory
	{
	public:
		MaterialFactory(void);
		~MaterialFactory(void);

		static void deinit();

		static void unload(Material* material);

		static Material* diffuse(Texture2D& diffuse);
	};

}

#endif

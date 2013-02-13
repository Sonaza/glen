#ifndef GLEN_MESHLOADER_HPP
#define GLEN_MESHLOADER_HPP

#include <glen/Graphics/MeshData.hpp>
#include <string>

namespace glen
{

	namespace MeshLoader
	{

		extern bool loadMesh(const std::string& path, MeshData *out);

	}

}

#endif

#ifndef GLEN_MESHDATA_HPP
#define GLEN_MESHDATA_HPP

#include <vector>
#include <glen/ogl.h>

namespace glen
{

	class MeshData
	{
	public:

		MeshData() : data(NULL), drawCount(0) {}

		// Data format Vertex XYZ / Texture Coord XYZ / Normals XYZ
		std::vector<GLfloat> data;
		GLuint drawCount;
	};

}

#endif

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
		~MeshData()
		{
			//if(data != NULL)
			//	delete[] data;
		}

		// Data format Vertex XYZ/Texture Coord XY/Normals XYZ
		std::vector<GLfloat> data;
		GLuint drawCount;
	};

}

#endif

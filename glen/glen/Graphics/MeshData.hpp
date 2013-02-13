#ifndef GLEN_MESHDATA_HPP
#define GLEN_MESHDATA_HPP

#include <glen/ogl.h>

namespace glen
{

	class MeshData
	{
	public:

		MeshData() : data(NULL), vertices(0) {}
		~MeshData()
		{
			if(data != NULL)
				delete[] data;
		}

		GLfloat* data;
		GLuint vertices;
	};

}

#endif

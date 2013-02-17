#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <glen/Config.hpp>
#include <glen/Graphics/MeshLoader.hpp>
#include <glen/System/Vector2.hpp>
#include <glen/System/Vector3.hpp>

namespace
{
	//////////////////////////////////////////////////////////////
	template <typename T>
	T strto(const std::string& s)
	{
		std::stringstream ss(s);
		T temp;
		ss >> temp;

		return temp;
	}

}

namespace glen
{

	namespace MeshLoader
	{
		////////////////////////////////////////////////
		bool loadMesh(const std::string& path, MeshData *out)
		{
			std::ifstream file(path);

			if(!file.is_open())
			{
				std::cout << "Unable to open mesh file: " <<  path << std::endl;
				return false;
			}

			std::vector<Vector3f> vertices;
			std::vector<Vector3f> normals;
			std::vector<Vector2f> texCoords;

			// Make sure data target is empty
			out->data.clear();

			int32 faceCount = 0;
			int32 vertexDrawCount = 0;

			std::string line;
			while(std::getline(file, line))
			{
				std::stringstream data(line);

				std::string id;
				double d1, d2, d3;

				data >> id;

				// Parse data according to type
				if(id == "v") // Vertex coordinates
				{
					data >> d1 >> d2 >> d3;

					vertices.push_back(Vector3f(
						static_cast<float>(d1),
						static_cast<float>(d2),
						static_cast<float>(d3)
					));
				}
				else if(id == "vt") // Texture coordinates
				{
					data >> d1 >> d2;

					texCoords.push_back(Vector2f(
						static_cast<float>(d1),
						static_cast<float>(d2)
					));
				}
				else if(id == "vn") // Vertex normals
				{
					data >> d1 >> d2 >> d3;

					normals.push_back(Vector3f(
						static_cast<float>(d1),
						static_cast<float>(d2),
						static_cast<float>(d3)
					));
				}
				else if(id == "f") // Faces
				{
					faceCount++;

					std::vector<std::string> indices;
					std::string item;

					// Extract all face indices
					while(data >> item)
						indices.push_back(item);

					// Check if face is unsupported
					if(indices.size() > 4)
					{
						std::cout << "OBJ Loader supports meshes with only triangles or quads" << std::endl;
						return false;
					}

					// If face is a quad sort indices differently
					if(indices.size() == 4)
					{
						std::vector<std::string> temp = indices;
						indices.clear();

						indices.push_back(temp[0]);
						indices.push_back(temp[1]);
						indices.push_back(temp[2]);
						indices.push_back(temp[2]);
						indices.push_back(temp[3]);
						indices.push_back(temp[0]);

						// Take one more face into account
						faceCount++;
					}

					// Append to the vertex buffer data array according to the indices
					for(std::vector<std::string>::iterator it = indices.begin();
						it != indices.end(); ++it)
					{
						std::stringstream temp(*it);
						std::string node;

						int32 i = 0;
						while(std::getline(temp, node, '/'))
						{
							int32 index = strto<int>(node)-1;

							if(i == 0) // Vertex Coordinate
							{
								out->data.push_back(vertices[index].x);
								out->data.push_back(vertices[index].y);
								out->data.push_back(vertices[index].z);

								vertexDrawCount++;
							}
							else if(i == 1) // Texture Coordinate
							{
								out->data.push_back(texCoords[index].x);
								out->data.push_back(texCoords[index].y);
							}
							else if(i == 2) // Vertex Normal
							{
								out->data.push_back(normals[index].x);
								out->data.push_back(normals[index].y);
								out->data.push_back(normals[index].z);
							}

							i++;
						}
					}
				}
			}

			//std::cout << "Vertex Count: " << vertexDrawCount << std::endl;

			// Calculate amount of vertices to be drawn
			out->drawCount = vertexDrawCount;

			return true;
		}

	}

}

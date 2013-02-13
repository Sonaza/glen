#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>

#include <glen/Config.hpp>
#include <glen/Graphics/MeshLoader.hpp>
#include <glen/System/Vector2.hpp>
#include <glen/System/Vector3.hpp>

namespace
{
	//////////////////////////////////////////////////////////////
	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
	{
		std::stringstream ss(s);
		std::string item;

		while(std::getline(ss, item, delim))
		{
			elems.push_back(item);
		}

		return elems;
	}

	//////////////////////////////////////////////////////////////
	std::vector<std::string> split(const std::string &s, char delim)
	{
		std::vector<std::string> elems;
		return split(s, delim, elems);
	}

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
			std::vector<GLfloat> final;

			int32 fc = 0;

			std::string line;
			while(std::getline(file, line))
			{
				std::stringstream data(line);

				std::string id;
				double d1, d2, d3;

				data >> id;

				if(id == "v")
				{
					data >> d1 >> d2 >> d3;

					vertices.push_back(Vector3f(
						static_cast<float>(d1),
						static_cast<float>(d2),
						static_cast<float>(d3)
					));
				}
				else if(id == "vt")
				{
					data >> d1 >> d2;

					texCoords.push_back(Vector2f(
						static_cast<float>(d1),
						static_cast<float>(d2)
					));
				}
				else if(id == "vn")
				{
					data >> d1 >> d2 >> d3;

					normals.push_back(Vector3f(
						static_cast<float>(d1),
						static_cast<float>(d2),
						static_cast<float>(d3)
					));
				}
				if(id == "f")
				{
					fc++;

					std::vector<std::string> indices;
					std::string item;

					while(data >> item)
					{
						indices.push_back(item);
					}

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
								final.push_back(vertices[index].x);
								final.push_back(vertices[index].y);
								final.push_back(vertices[index].z);
							}
							else if(i == 1) // Texture Coordinate
							{
								final.push_back(texCoords[index].x);
								final.push_back(texCoords[index].y);
							}
							else if(i == 2) // Vertex Normal
							{
								final.push_back(normals[index].x);
								final.push_back(normals[index].y);
								final.push_back(normals[index].z);
							}

							i++;
						}
					}
				}
			}

			// Calculate amount of vertices to be drawn
			out->vertices = vertices.size() * fc;

			GLfloat* temp = new GLfloat[final.size()];
			std::copy(final.begin(), final.end(), temp);

			out->data = temp;

			return true;
		}

	}

}
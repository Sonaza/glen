#include <glen/Graphics/Image.hpp>
#include <glen/System/ErrorStream.hpp>

#include "stb_image/stb_image.h"

using namespace glen;

////////////////////////////////////////////////////
Image::Image() :
	m_loaded(false),
	m_channels(0)
{
	
}

////////////////////////////////////////////////////
Image::~Image()
{
	
}

////////////////////////////////////////////////////
bool Image::loadFromFile(const std::string &path)
{	
	m_pixels.clear();
	m_loaded = false;

	int width, height, channels;
	uint8* data = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);

	if(data)// && m_size.x && m_size.y)
	{
		m_size.x = width;
		m_size.y = height;
		m_channels = channels;

		m_pixels.resize(m_size.x * m_size.y * 4);
		memcpy(&m_pixels[0], data, m_pixels.size());
		
		stbi_image_free(data);

		m_loaded = true;

		return true;
	}
	else
	{
		err << "Unable to open image file: " << path << "\n\n"
			<< stbi_failure_reason() << "" << ErrorStream::error;

		m_size.x = 0;
		m_size.y = 0;
		m_channels = 0;

		return false;
	}
}
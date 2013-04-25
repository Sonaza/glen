#ifndef GLEN_IMAGE_HPP
#define GLEN_IMAGE_HPP

#include <vector>
#include <string>

#include <glen/System/Types.hpp>
#include <glen/System/Types.hpp>

namespace glen
{

	class Image
	{
	public:
		Image();
		~Image();

		bool loadFromFile(const std::string &path);

		inline void* getPixels() { return m_loaded ? static_cast<void*>(&m_pixels[0]) : NULL; }

		inline vec2i getSize() const { return m_size; }
		inline int32 getWidth() const { return m_size.x; }
		inline int32 getHeight() const { return m_size.y; }

		inline int32 getChannels() const { return m_channels; }

	private:

		std::vector<uint8> m_pixels;

		vec2i	m_size;
		int32		m_channels;

		bool		m_loaded;

	};
	
}

#endif GLEN_IMAGE_HPP

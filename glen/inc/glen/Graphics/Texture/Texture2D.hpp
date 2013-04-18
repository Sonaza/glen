#ifndef GLEN_TEXTURE_HPP
#define GLEN_TEXTURE_HPP

#include <glen/Graphics/Texture/Texture.hpp>

namespace glen
{

	class Texture2D : public Texture
	{
	public:
		Texture2D(void);
		virtual ~Texture2D(void);

		void bind() const;

		bool loadFromFile(const std::string& path);

		Vector2i getSize() const { return m_image->getSize(); }

	private:

		Image*		m_image;

	};

}

#endif

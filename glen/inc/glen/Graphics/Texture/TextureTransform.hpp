#ifndef GLEN_TEXTURETRANSFORM_HPP
#define GLEN_TEXTURETRANSFORM_HPP

#include <glen/System/Transformable.hpp>
#include <glen/System/Types.hpp>

namespace glen
{

	class TextureTransform : public Transformable
	{
	public:
		TextureTransform(void);
		~TextureTransform(void);

		virtual mat4 getMatrix();
	};

}

#endif

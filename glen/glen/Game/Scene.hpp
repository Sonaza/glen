#ifndef SCENE_HPP
#define SCENE_HPP

namespace glen
{
	
	class Scene
	{
	public:
		Scene(void);
		virtual ~Scene(void);

		virtual void load() =0;
		virtual void unload() =0;

		virtual void update() =0;

		virtual void draw() =0;
	};

}

#endif

#ifndef TESTSCENE_HPP
#define TESTSCENE_HPP

#include <glen/Graphics/Scene.hpp>

class TestScene : public glen::Scene
{
public:
	TestScene(void);
	~TestScene(void);

	void load();
	void unload();

	void update();

	void draw();
};

#endif

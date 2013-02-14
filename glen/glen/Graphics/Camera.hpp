#ifndef GLEN_CAMERA_HPP
#define GLEN_CAMERA_HPP

#include <glm/glm.hpp>
#include <glen/System/Vector3.hpp>
#include <glen/System/Transformable.hpp>

namespace glen
{

class Camera : public Transformable
{
public:
	Camera(void);
	~Camera(void);

	void lookAt(Vector3f target, Vector3f worldUp);

private:

	glm::mat4	m_matrix;

};

}

#endif
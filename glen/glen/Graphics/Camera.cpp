#include <glen/Graphics/Camera.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace glen
{
///////////////////////////////////////////////
Camera::Camera(void)
{
}

///////////////////////////////////////////////
Camera::~Camera(void)
{
}

///////////////////////////////////////////////
void Camera::lookAt(Vector3f target, Vector3f worldUp)
{
	m_matrix = glm::lookAt(
		getPosition().vec3(),
		target.vec3(),
		worldUp.vec3()
	);
}

}
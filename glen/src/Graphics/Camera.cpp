#include <glen/Graphics/Camera.hpp>
#include <glen/Window/Window.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <cassert>
#include <memory>

using namespace glen;

namespace
{
	typedef std::shared_ptr<Camera> CameraPtr;
	std::vector<CameraPtr>	m_cameras;
}

///////////////////////////////////////////////
Camera::Camera(void) :
	m_fov(0.f),
	m_znear(0.f),
	m_zfar(0.f),
	m_updateProjMatrix(true),
	m_active(false)
{
}

///////////////////////////////////////////////
Camera::Camera(float fov, float znear, float zfar) :
	m_fov(fov),
	m_znear(znear),
	m_zfar(zfar),
	m_updateProjMatrix(true),
	m_active(false)
{
}

///////////////////////////////////////////////
Camera::~Camera(void)
{
}

///////////////////////////////////////////////
Camera* Camera::create(float fov, float znear, float zfar, const bool activate)
{
	Camera* temp = new(std::nothrow) Camera(fov, znear, zfar);
	assert(temp != NULL && "Memory allocation for camera failed");

	if(temp)
	{
		m_cameras.push_back(CameraPtr(temp));

		if(activate) temp->activate();
	}

	return temp;
}

///////////////////////////////////////////////
void Camera::activate()
{
	for(std::vector<CameraPtr>::iterator it = m_cameras.begin();
		it != m_cameras.end(); ++it)
	{
		// Deactivate all
		(*it)->m_active = false;
	}
	
	// Activate only this one
	m_active = true;
}

///////////////////////////////////////////////
Camera* Camera::activeCamera()
{
	Camera* result = NULL;

	for(std::vector<CameraPtr>::iterator it = m_cameras.begin();
		it != m_cameras.end(); ++it)
	{
		if((*it)->isActive())
		{
			result = (*it).get();
			break;
		}
	}

	return result;
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

//////////////////////////////////////////////
glm::mat4 Camera::getMatrix()
{

	return m_matrix;
}

///////////////////////////////////////////////
glm::mat4 Camera::getProjectionMatrix()
{
	if(m_updateProjMatrix)
	{
		float ratio = Window::getAspectRatio();
		m_projMatrix = glm::perspective(m_fov, ratio, m_znear, m_zfar);

		m_updateProjMatrix = false;
	}

	return m_projMatrix;
}

///////////////////////////////////////////////
void Camera::refreshProjection()
{
	for(std::vector<CameraPtr>::iterator it = m_cameras.begin();
		it != m_cameras.end(); ++it)
	{
		(*it)->m_updateProjMatrix = true;
	}
}

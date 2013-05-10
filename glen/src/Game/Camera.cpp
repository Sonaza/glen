#include <glen/Game/Camera.hpp>

#include <glen/Game/Components/Transform.hpp>
#include <glen/Game/Components/CameraComponent.hpp>

#include <glen/System/ErrorStream.hpp>

using namespace glen;

CameraPtr Camera::camera = NULL;

////////////////////////////////////////////////////
Camera::Camera(float fov, float znear, float zfar)
{
	m_transform = new Transform;
	attachComponent(m_transform);

	m_camera = new CameraComponent(fov, znear, zfar);
	attachComponent(m_camera);

	m_camera->calculateProjection();

	if(!camera)
	{
		camera.reset(this);
	}
	else
	{
		err << "You can't have more than one camera" << ErrorStream::error;
	}
}

////////////////////////////////////////////////////
Camera::~Camera()
{
	
}

////////////////////////////////////////////////////
void Camera::update()
{
	
}

////////////////////////////////////////////////////
mat4& Camera::getView()
{
	return m_camera->getViewMatrix();
}

////////////////////////////////////////////////////
mat4& Camera::getProjection()
{
	return m_camera->getProjectionMatrix();
}

////////////////////////////////////////////////////
void Camera::updateProjection()
{
	m_camera->calculateProjection();
}

////////////////////////////////////////////////////
void Camera::setPosition(vec3f v)
{
	m_transform->setPosition(v);
}

////////////////////////////////////////////////////
void Camera::setPosition(float x, float y, float z)
{
	m_transform->setPosition(x, y, z);
}

////////////////////////////////////////////////////
vec3f Camera::getPosition() const
{
	return m_transform->getPosition();
}

////////////////////////////////////////////////////
void Camera::setRotation(vec3f v)
{
	m_transform->setRotation(v);
}

////////////////////////////////////////////////////
void Camera::setRotation(float x, float y, float z)
{
	m_transform->setRotation(x, y, z);
}

////////////////////////////////////////////////////
vec3f Camera::getRotation() const
{
	return m_transform->getRotation();
}

////////////////////////////////////////////////////
vec3f Camera::getForward()
{
	return m_transform->getForward();
}

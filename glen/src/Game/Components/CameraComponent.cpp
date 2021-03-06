#include <glen/Game/Components/CameraComponent.hpp>
#include <glen/Window/Window.hpp>

#include <glen/System/Utility.hpp>

#include <glen/Game/Components/Transform.hpp>

using namespace glen;

#define PI 3.14159265f
#define torad(__deg) (__deg * PI / 180.f)

////////////////////////////////////////////////////
CameraComponent::CameraComponent(float fov, float znear, float zfar) : Component("camera"),
	m_fov(fov),
	m_znear(znear),
	m_zfar(zfar)
{
	
}

////////////////////////////////////////////////////
CameraComponent::~CameraComponent()
{
	
}

////////////////////////////////////////////////////
void CameraComponent::attached()
{
	m_transform = m_entity->getComponent<Transform>("transform");
}

////////////////////////////////////////////////////
void CameraComponent::update()
{
	//calculateProjection();

	vec3f dir = m_transform->getForward();

	vec3f pos = m_transform->getPosition();
	vec3f rot = m_transform->getRotation();

	mat4 mat; mat.rotate(rot.z, dir).rotate(rot.y, vec3f::up);

	vec4f up = mat * vec4f(vec3f::up, 1.f);
	vec3f roll(up.x, up.y, up.z);

	m_view.lookAt(pos, pos + dir, roll);
}

////////////////////////////////////////////////////
void CameraComponent::lookAt(const vec3f &target)
{
	vec3f pos = request<vec3f>("getPosition");
	vec3f dir = normalize(target - pos);

	//float x = asin(-dir.y);
	//float y = acos(dir.x / cos(x));

	m_view.lookAt(pos, target, vec3f::up);
}

////////////////////////////////////////////////////
mat4& CameraComponent::getProjectionMatrix()
{
	return m_projection;
}

////////////////////////////////////////////////////
mat4& CameraComponent::getViewMatrix()
{
	return m_view;
}

////////////////////////////////////////////////////
void CameraComponent::calculateProjection()
{
	vec2f size = static_cast<vec2f>(Window::getDimensions());
	calculateProjection(size.x / size.y);
}

////////////////////////////////////////////////////
void CameraComponent::calculateProjection(float aspect)
{
	m_projection.perspective(m_fov, aspect, m_znear, m_zfar);
	//m_projection.ortho(-8.f, 8.f, -5.25f, 5.25f, m_znear, m_zfar);
}

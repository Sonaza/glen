#include <glen/Game/Components/CameraComponent.hpp>
#include <glen/Window/Window.hpp>

using namespace glen;

////////////////////////////////////////////////////
CameraComponent::CameraComponent(float fov, float znear, float zfar) : Component("CameraComponent"),
	m_fov(fov),
	m_znear(znear),
	m_zfar(zfar),
	m_updateProjection(true)
{
	
}

////////////////////////////////////////////////////
CameraComponent::~CameraComponent()
{
	
}

////////////////////////////////////////////////////
void CameraComponent::attached()
{

}

////////////////////////////////////////////////////
void CameraComponent::update()
{
	if(m_updateProjection)
	{
		float aspect = Window::getDimensions().x / static_cast<float>(Window::getDimensions().y);
		m_projection.perspective(m_fov, aspect, m_znear, m_zfar);

		m_updateProjection = false;
	}


}

////////////////////////////////////////////////////
void CameraComponent::lookAt(const vec3f &target)
{
	vec3f pos = request<vec3f>("getPosition");

	vec3f dir = normalize(target - pos);


}

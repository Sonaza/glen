#ifndef GLEN_CAMERACOMPONENT_HPP
#define GLEN_CAMERACOMPONENT_HPP

#include <glen/System/Types.hpp>
#include <glen/Game/Component.hpp>

#include <cmath>

namespace glen
{
	
	class CameraComponent : public Component
	{
	public:
		CameraComponent(float fov, float znear, float zfar);
		~CameraComponent();

		void attached();
		void update();

		void lookAt(const vec3f &target);

		mat4& getProjectionMatrix();
		mat4& getViewMatrix();

	private:

		mat4 m_projection;
		bool m_updateProjection;

		float m_fov;
		float m_znear, m_zfar;

	};
	
}

#endif GLEN_CAMERACOMPONENT_HPP

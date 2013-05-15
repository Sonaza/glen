#ifndef GLEN_CAMERACOMPONENT_HPP
#define GLEN_CAMERACOMPONENT_HPP

#include <glen/Game/Component.hpp>
#include <glen/System/Types.hpp>

#include <cmath>

namespace glen
{

	class Transform;
	
	class CameraComponent : public Component
	{
		friend class Camera;

	public:
		CameraComponent(float fov, float znear, float zfar);
		~CameraComponent();

		void attached();
		void update();

		void lookAt(const vec3f &target);

		mat4& getProjectionMatrix();
		mat4& getViewMatrix();

		void calculateProjection();
		void calculateProjection(float aspect);

	protected:

		Transform*	m_transform;

		mat4		m_view;
		mat4		m_projection;

		// Camera field of view
		float m_fov;

		// Near and far planes
		float m_znear;
		float m_zfar;

	};
	
}

#endif GLEN_CAMERACOMPONENT_HPP

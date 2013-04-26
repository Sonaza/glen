#ifndef GLEN_CAMERA_HPP
#define GLEN_CAMERA_HPP

#include <glen/System/Types.hpp>
#include <glen/System/Transformable.hpp>

#include <vector>

namespace glen
{

	class Camera : public Transformable
	{
	public:
		Camera(void);
		~Camera(void);
	
		void lookAt(vec3f target, vec3f worldUp);

		void activate();

		mat4 getMatrix();
		mat4 getProjectionMatrix();

		inline bool isActive() const { return m_active; }

		static Camera* create(float fov, float znear, float zfar, const bool activate = true);
		static Camera* activeCamera();

		static void refreshProjection();

	private:

		Camera(float fov, float znear, float zfar);

		float m_fov;
		float m_znear, m_zfar;

		bool	m_active;

		bool	m_updateProjMatrix;
		mat4	m_projMatrix;

		mat4	m_matrix;

	};

}

#endif
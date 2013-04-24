#ifndef GLEN_CAMERA_HPP
#define GLEN_CAMERA_HPP

#include <glm/glm.hpp>
#include <glen/Config.hpp>
#include <glen/System/Vector3.hpp>
#include <glen/System/Transformable.hpp>

#include <vector>

namespace glen
{

	class Camera : public Transformable
	{
	public:
		Camera(void);
		~Camera(void);
	
		void lookAt(Vector3f target, Vector3f worldUp);

		void activate();

		glm::mat4 getMatrix();
		glm::mat4 getProjectionMatrix();

		inline bool isActive() const { return m_active; }

		static Camera* create(float fov, float znear, float zfar, const bool activate = true);
		static Camera* activeCamera();

		static void refreshProjection();

	private:

		Camera(float fov, float znear, float zfar);

		float m_fov;
		float m_znear, m_zfar;

		bool		m_active;

		bool		m_updateProjMatrix;
		glm::mat4	m_projMatrix;

		glm::mat4	m_matrix;

	};

}

#endif
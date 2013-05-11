#ifndef GLEN_CAMERA_HPP
#define GLEN_CAMERA_HPP

#include <glen/Game/Entity.hpp>
#include <glen/System/Types.hpp>

#include <cassert>
#include <memory>

namespace glen
{

	class Camera;
	class CameraComponent;
	class Transform;
	
	typedef std::shared_ptr<Camera> CameraPtr;

	class Camera : public Entity
	{
	public:
		Camera(float fov, float znear, float zfar);
		virtual ~Camera();

		static CameraPtr getCamera() { return camera; }

		void update();

		vec3f getForward();

		mat4& getView();
		mat4& getProjection();

		void updateProjection(float aspect);

		void setPosition(vec3f v);
		void setPosition(float x, float y, float z);
		vec3f getPosition() const;

		void setRotation(vec3f v);
		void setRotation(float x, float y, float z);
		vec3f getRotation() const;

	private:

		Transform*			m_transform;
		CameraComponent*	m_camera;

		static CameraPtr camera;

	};
	
}

#endif GLEN_CAMERA_HPP

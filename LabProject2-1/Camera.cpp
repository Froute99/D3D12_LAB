

#include "stdafx.h"
#include "Camera.h"

namespace _3DLab {
	void Camera::SetViewport(int left, int top, int width, int height) {
		m_pViewport = new Viewport(left, top, width, height);
		m_aspectRatio =
			float(m_pViewport->width) / float(m_pViewport->height);
	}

	void Camera::SetFOVAngle(float fovAngle) {
		this->fovAngle = fovAngle;
		projectionRectDistance =
			float(1.f / tan(DegreeToRadian(fovAngle * 0.5f)));
	}

	void Camera::Move(float x, float y, float z) {
		xPosition += x;
		yPosition += y;
		zPosition += z;
	}

	void Camera::Rotate(float pitch, float yaw, float roll) {
		xRotation += pitch;
		yRotation += yaw;
		zRotation += roll;
	}

	Point3D Camera::CameraTransform(Point3D& world) {
		Point3D camera = world;
		camera.x -= xPosition;
		camera.y -= yPosition;
		camera.z -= zPosition;

		float pitch = DegreeToRadian(-xRotation);
		float yaw	= DegreeToRadian(-yRotation);
		float roll	= DegreeToRadian(-zRotation);

		Point3D rotated = camera;
		if (pitch != 0.f) {
			rotated.y = float(camera.y * cos(pitch) -
				camera.z * sin(pitch));
			rotated.z = float(camera.y * sin(pitch) +
				camera.z * cos(pitch));
			camera.y = rotated.y;
			camera.z = rotated.z;
		}
		if (yaw != 0.f) {
			rotated.x = float(camera.x * cos(yaw) +
				camera.z * sin(yaw));
			rotated.z = float(-camera.x * sin(yaw) +
				camera.z * cos(yaw));
			camera.x = rotated.x;
			camera.z = rotated.z;
		}
		if (roll != 0.f) {
			rotated.x = float(camera.x * cos(roll) -
				camera.y * sin(roll));
			rotated.y = float(camera.x * sin(roll) +
				camera.y * cos(roll));
			camera.x = rotated.x;
			camera.y = rotated.y;
		}
		return camera;
	}

	Point3D Camera::ProjectionTransform(Point3D& camera) {
		Point3D project = camera;
		if (camera.z != 0.f) {
			project.x = float((camera.x * projectionRectDistance) /
				(m_aspectRatio * camera.z));
			project.y = float((camera.y * projectionRectDistance) /
				camera.z);
			project.z = camera.z;
		}

		return project;
	}

	Point3D Camera::ScreenTransform(Point3D& projection) {
		Point3D screen = projection;
		float halfWidth = m_pViewport->width * 0.5f;
		float halfHeight = m_pViewport->height * 0.5f;
		screen.x = (projection.x * halfWidth) +
			m_pViewport->left + halfWidth;
		screen.y = (-projection.y * halfHeight) +
			m_pViewport->top + halfHeight;
		return screen;
	}
}

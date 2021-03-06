
#pragma once
#include "Mesh.h"

namespace _3DLab {
	struct Viewport {
		Viewport(int left, int top, int width, int height)
			: left(left), top(top), width(width), height(height) {}

		int left;
		int top;
		int width;
		int height;
	};


	class Camera {
	public:
		Camera() {}
		virtual ~Camera() {
			if (m_pViewport) {
				delete m_pViewport;
			}
		}
		
		Point3D CameraTransform(Point3D& world);
		Point3D ProjectionTransform(Point3D& camera);
		Point3D ScreenTransform(Point3D& projection);
		
		void SetPosition(float x, float y, float z) {
			xPosition = x; yPosition = y; zPosition = z;
		}
		void SetRotation(float pitch, float yaw, float roll) {
			xRotation = pitch; yRotation = yaw; zRotation = roll;
		}

		void SetViewport(int xStart, int yStart, int width, int height);
		void SetFOVAngle(float fovAngle);

		void Move(float x, float y, float z);
		void Rotate(float pitch, float yaw, float roll);

	private:
		float xPosition = 0.f;
		float yPosition = 0.f;
		float zPosition = 0.f;

		float xRotation = 0.f;
		float yRotation = 0.f;
		float zRotation = 0.f;

		float xRotationSpeed = 0.f;
		float yRotationSpeed = 0.f;
		float zRotationSpeed = 0.f;

		float fovAngle = 0.f;
		float projectionRectDistance = 1.f;

		Viewport* m_pViewport = nullptr;

		float m_aspectRatio
			= float(FRAME_BUFFER_WIDTH) / float(FRAME_BUFFER_HEIGHT);
	};
}
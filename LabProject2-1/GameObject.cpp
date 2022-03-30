
#include "stdafx.h"
#include "GameObject.h"

namespace _3DLab {
	GameObject::~GameObject() {
		if (m_pMesh) {
			m_pMesh->Release();
		}
	}

	Point3D GameObject::WorldTransform(Point3D& model) {
		float pitch	= DegreeToRadian(xRotation);
		float yaw	= DegreeToRadian(yRotation);
		float roll	= DegreeToRadian(zRotation);

		Point3D world = model;
		Point3D rotated = model;

		if (pitch != 0.0f) {
			rotated.y = float(world.y * cos(pitch) - world.z *
				sin(pitch));
			rotated.z = float(world.y * sin(pitch) + world.z *
				cos(pitch));
			world.y = rotated.y;
			world.z = rotated.z;
		}
		if (yaw != 0.0f) {
			rotated.x = float(world.x * cos(yaw) + world.z *
				sin(yaw));
			rotated.z = float(-world.x * sin(yaw) + world.z *
				cos(yaw));
			world.x = rotated.x;
			world.z = rotated.z;
		}
		if (roll != 0.0f) {
			rotated.x = float(world.x * cos(roll) - world.y *
				sin(roll));
			rotated.y = float(world.x * sin(roll) + world.y *
				cos(roll));
			world.x = rotated.x;
			world.y = rotated.y;
		}

		world.x += xPosition;
		world.y += yPosition;
		world.z += zPosition;

		return(world);
	}

	void GameObject::Animate(float elapsedTime) {
		Rotate(xRotationSpeed * elapsedTime,
			yRotationSpeed * elapsedTime,
			zRotationSpeed * elapsedTime);
	}

	void GameObject::Render(HDC hDCFrameBuffer) {
		HPEN hPen = ::CreatePen(PS_SOLID, 0, m_color);
		HPEN holdPen = (HPEN)::SelectObject(hDCFrameBuffer, hPen);

		if (m_pMesh) {
			m_pMesh->Render(hDCFrameBuffer);
		}

		::SelectObject(hDCFrameBuffer, holdPen);
		::DeleteObject(hPen);
	}
}

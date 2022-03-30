

#pragma once
#include "Mesh.h"

namespace _3DLab {
	class GameObject {
	public:
		GameObject() {}
		~GameObject();
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

		Mesh* m_pMesh = nullptr;

		DWORD m_color = RGB(255, 0, 0);

	public:
		void SetMesh(Mesh* m_pMesh) {
			this->m_pMesh = m_pMesh;
			if (m_pMesh) {
				m_pMesh->AddRef();
			}
		}

		void SetColor(DWORD m_color) {
			this->m_color = m_color;
		}

		void SetPosition(float x, float y, float z) {
			xPosition = x; yPosition = y; zPosition = y;
		}
		void SetRotation(float x, float y, float z) {
			xRotation = x; yRotation = y; zRotation = z;
		}
		void SetRotationSpeed(float x, float y, float z) {
			xRotationSpeed = x; yRotationSpeed = y; zRotationSpeed = z;
		}

		void Move(float x, float y, float z) {
			xPosition += x; yPosition += y; zPosition += z;
		}

		void Rotate(float x, float y, float z) {
			xRotation += x; yRotation += y; zRotation += z;
		}

	public:
		// 메쉬의 정점 하나를 게임 객체의 위치와 방향을 사용하여 월드 좌표 변환
		Point3D WorldTransform(Point3D& model);

		virtual void Animate(float elapsedTime);
		virtual void Render(HDC hDCFrameBuffer);
	};
}

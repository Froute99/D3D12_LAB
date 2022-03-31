

#pragma once
#include "GameObject.h"
#include "Camera.h"

namespace _3DLab {
	class Player : public GameObject {
	public:
		Player() {}
		virtual ~Player() {
			if (m_pCamera) {
				delete m_pCamera;
			}
		}

		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);

		void Move(float x, float y, float z);
		void Rotate(float x, float y, float z);

		void SetCamera(Camera* pCamera) {
			m_pCamera = pCamera;
		}
		Camera* GetCamera() {
			return m_pCamera;
		}
	private:
		Camera* m_pCamera = nullptr;
	};
}

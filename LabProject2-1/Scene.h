
#pragma once
#include "GameObject.h"
#include "Camera.h"

namespace _3DLab {
	class Scene {
	public:
		Scene() {}
		virtual ~Scene() {}

		virtual void BuildObjects();
		virtual void ReleaseObjects();

		virtual void Animate(float elpasedTime);
		virtual void Render(HDC hDCFrameBuffer, Camera* pCamera);

	private:
		int m_objectNumber = 0;
		GameObject** m_ppObjects = nullptr;	// array pointer of gameobject
		
	};
}


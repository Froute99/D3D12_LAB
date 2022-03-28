

#pragma once
#include "GameObject.h"
#include "Camera.h"

namespace _3DLab {
	class GraphicsPipeline {
	public:
		static void	SetGameObject(GameObject* ptrToGameObject) {
			m_ptrToGameObject = ptrToGameObject;
		}
		static void SetCamera(Camera* ptrToCamera) {
			m_ptrToCamera = ptrToCamera;
		}
		static _3DLab::Point3D ScreenTransform(_3DLab::Point3D& projection);
		static _3DLab::Point3D Project(_3DLab::Point3D& model);
	private:
		static GameObject* m_ptrToGameObject;
		static Camera* m_ptrToCamera;
	};
}


#include "stdafx.h"
#include "Scene.h"
#include "GraphicsPipeline.h"

namespace _3DLab {
	void Scene::BuildObjects() {
		CubeMesh* pCubeMesh = new CubeMesh(8.f, 8.f, 8.f);

		m_objectNumber = 2;
		m_ppObjects = new GameObject* [m_objectNumber];

		m_ppObjects[0] = new GameObject();
		m_ppObjects[0]->SetMesh(pCubeMesh);
		m_ppObjects[0]->SetPosition(-8.5f, 0.f, -14.f);
		m_ppObjects[0]->SetRotation(0.f, 0.f, 0.f);
		m_ppObjects[0]->SetRotationSpeed(/*5.f, 30.f, 9.f*/-1.f,-1.f,-1.f);
		m_ppObjects[0]->SetColor(RGB(255, 0, 0));

		m_ppObjects[1] = new GameObject();
		m_ppObjects[1]->SetMesh(pCubeMesh);
		m_ppObjects[1]->SetPosition(+8.5f, 0.0f, -14.0f);
		m_ppObjects[1]->SetRotation(0.0f, 0.0f, 0.0f);
		m_ppObjects[1]->SetRotationSpeed(/*30.0f, 9.0f, 5.0f*/1.f,1.f,1.f);
		m_ppObjects[1]->SetColor(RGB(0, 0, 255));
	}

	void Scene::ReleaseObjects() {
		for (int i = 0; i < m_objectNumber; ++i) {
			if (m_ppObjects[i]) {
				delete m_ppObjects[i];
			}
		}
	}

	void Scene::Animate(float elpasedTime) {
		for (int i = 0; i < m_objectNumber; ++i) {
			m_ppObjects[i]->Animate(elpasedTime);
		}
	}

	void Scene::Render(HDC hDCFrameBuffer, Camera* pCamera) {
		if (pCamera) {
			GraphicsPipeline::SetCamera(pCamera);

			for (int i = 0; i < m_objectNumber; ++i) {
				GraphicsPipeline::SetGameObject(m_ppObjects[i]);
				m_ppObjects[i]->Render(hDCFrameBuffer);
			}
		}
	}
}

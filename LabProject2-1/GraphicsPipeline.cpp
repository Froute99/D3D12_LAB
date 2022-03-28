
#include "stdafx.h"
#include "GraphicsPipeline.h"

namespace _3DLab {
	GameObject* GraphicsPipeline::m_ptrToGameObject = nullptr;
	Camera* GraphicsPipeline::m_ptrToCamera = nullptr;

	Point3D GraphicsPipeline::Project(Point3D& model) {
		Point3D world = m_ptrToGameObject->worldTransform(model);
		Point3D camera = m_ptrToCamera->CameraTransform(world);
		Point3D projection = m_ptrToCamera->ProjectionTransform(camera);
		return(projection);
	}

	Point3D GraphicsPipeline::ScreenTransform(Point3D& projection) {
		Point3D screen = m_ptrToCamera->ScreenTransform(projection);
		return screen;
	}
}


#include "stdafx.h"
#include "Camera.h"

namespace _3DLab {
	void Camera::SetViewport(int left, int top, int width, int height) {
		m_pViewport = new Viewport(left, top, width, height);
		m_aspectRatio = float(m_pViewport->width);
	}
}

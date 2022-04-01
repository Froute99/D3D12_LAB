

#include "stdafx.h"
#include "GameFramwork.h"

namespace _3DLab {
	void GameFramework::OnCreate(HINSTANCE hInstance, HWND hMainWnd) {
		m_hInstance = hInstance;
		m_hWnd = hMainWnd;

		//������ ȭ���� �����Ѵ�
		BuildFrameBuffer();
		//�÷��̾�� ���� ����(��)�� �����Ѵ�
		BuildObjects();
	}

	void GameFramework::OnDestroy() {
		ReleaseObjects();
		if (m_hBitmapFrameBuffer) {
			::DeleteObject(m_hBitmapFrameBuffer);
		}
		if (m_hDCFrameBuffer) {
			::DeleteDC(m_hDCFrameBuffer);
		}
	}

	void GameFramework::BuildFrameBuffer() {
		::GetClientRect(m_hWnd, &m_clientRect);
		HDC hDC = ::GetDC(m_hWnd);
		m_hDCFrameBuffer = ::CreateCompatibleDC(hDC);
		m_hBitmapFrameBuffer = ::CreateCompatibleBitmap(hDC,
			m_clientRect.right - m_clientRect.left,
			m_clientRect.bottom - m_clientRect.top);
		::SelectObject(m_hDCFrameBuffer, m_hBitmapFrameBuffer);
		::ReleaseDC(m_hWnd, hDC);
		::SetBkMode(m_hDCFrameBuffer, TRANSPARENT);
	}
	
	void GameFramework::ClearFrameBuffer(DWORD color) {
		HPEN hPen = ::CreatePen(PS_SOLID, 0, color);
		HPEN holdPen = (HPEN)::SelectObject(m_hDCFrameBuffer, hPen);
		HBRUSH hBrush = ::CreateSolidBrush(color);
		HBRUSH holdBrush = (HBRUSH)::SelectObject(m_hDCFrameBuffer, hBrush);
	}
	
	void GameFramework::PresentFrameBuffer() {
		HDC hDC = ::GetDC(m_hWnd);
		::BitBlt(hDC, m_clientRect.left, m_clientRect.top,
			m_clientRect.right - m_clientRect.left,
			m_clientRect.bottom - m_clientRect.top,
			m_hDCFrameBuffer, m_clientRect.left,
			m_clientRect.top, SRCCOPY);
		::ReleaseDC(m_hWnd, hDC);
	}

	void GameFramework::BuildObjects() {
		// ī�޶� �����ϰ� ����Ʈ�� �þ߰�(FOV)�� �����Ѵ�
		Camera* pCamera = new Camera();
		pCamera->SetViewport(0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT);
		pCamera->SetFOVAngle(60.f);

		// �÷��̾� ���� ��ü�� �����ϰ� ī�޶�� ��ġ�� �����Ѵ�
		m_pPlayer = new Player();
		m_pPlayer->SetCamera(pCamera);
		m_pPlayer->SetPosition(0.f, 3.f, -40.f);

		// �� ��ü�� �����ϰ� ���� ��ü���� �����Ѵ�
		m_pScene = new Scene();
		m_pScene->BuildObjects();
	}

	void GameFramework::ReleaseObjects() {
		if (m_pScene) {
			m_pScene->ReleaseObjects();
			delete m_pScene;
		}
		if (m_pPlayer) {
			delete m_pPlayer;
		}
	}

	void GameFramework::ProcessInput() {
		static UCHAR pKeyBuffer[256];
		if (::GetKeyboardState(pKeyBuffer)) {
			float cxKeyDelta = 0.0f, cyKeyDelta = 0.0f, czKeyDelta = 0.0f;

			if (pKeyBuffer[VK_UP] & 0xF0) czKeyDelta = +0.125f;
			if (pKeyBuffer[VK_DOWN] & 0xF0) czKeyDelta = -0.125f;
			if (pKeyBuffer[VK_LEFT] & 0xF0) cxKeyDelta = -0.125f;
			if (pKeyBuffer[VK_RIGHT] & 0xF0) cxKeyDelta = +0.125f;
			if (pKeyBuffer[VK_PRIOR] & 0xF0) cyKeyDelta = +0.125f;
			if (pKeyBuffer[VK_NEXT] & 0xF0) cyKeyDelta = -0.125f;

			m_pPlayer->Move(cxKeyDelta, cyKeyDelta, czKeyDelta);
		}
	}

	void GameFramework::AnimateObjects() {
		if (m_pScene) {
			m_pScene->Animate(1.f / 60.f);
		}
	}

	void GameFramework::FrameAdvance() {
		// ����� �Է� ó��
		ProcessInput();
		AnimateObjects();
		ClearFrameBuffer(RGB(90, 103, 224));

		Camera* pCamera = m_pPlayer->GetCamera();
		if (m_pScene) {
			m_pScene->Render(m_hDCFrameBuffer, pCamera);
		}

		PresentFrameBuffer();
	}
}

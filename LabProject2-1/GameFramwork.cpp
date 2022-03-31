

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

	}

	void GameFramework::BuildObjects() {

	}

	void GameFramework::ReleaseObjects() {

	}

	void GameFramework::ProcessInput() {

	}

	void GameFramework::AnimateObjects() {

	}

	void GameFramework::FrameAdvance() {

	}
}

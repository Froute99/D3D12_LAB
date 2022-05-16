#include "GameFramework.h"

CGameFramework::CGameFramework() {
	m_pdxgiFactory = nullptr;
	m_pdxgiSwapChain = nullptr;
	m_pd3dDevice = nullptr;

	m_pd3dCommandAllocator = nullptr;
	m_pd3dCommandQueue = nullptr;
	m_pd3dPipelineState = nullptr;
	m_pd3dCommandList = nullptr;

	for (int i = 0; i < m_nSwapChainBuffers; ++i)
		m_ppd3dRenderTargetBuffers[i] = nullptr;
	m_pd3dRtvDescriptorHeap = nullptr;
	m_nRtvDescriptorIncrementSize = 0;

	m_pd3dDepthStencilBuffer = nullptr;
	m_pd3dRtvDescriptorHeap = nullptr;
	m_nDtvDescriptorIncrementSize = 0;

	m_nSwapChainBufferIndex = 0;
	
	m_hFenceEvent = nullptr;
	m_pd3dFence = nullptr;
	m_nFenceValue = 0;

	m_nWndClientWidth = FRAME_BUFFER_WIDTH;
	m_nWndClientHeight = FRAME_BUFFER_HEIGHT;
}

bool CGameFramework::OnCreate(HINSTANCE hInstance, HWND hMainWnd) {
	m_hInstance = hInstance;
	m_hWnd = hMainWnd;

	// Direct3D 디바이스, 명령 큐와 명령 리스트, 스왑 체인 등을 생성하는 함수를 호출한다.
	CreateDirect3DDevice();
	CreateCommandQueueAndList();
	CreateSwapChain();
	CreateRtvAndDsvDescriptorHeaps();
	CreateRenderTargetViews();
	CreateDepthStencilView();

	// 렌더링할 게임 객체를 생성한다.
	BuildObjects();

	return true;
}

void CGameFramework::OnDestroy() {
	// GPU가 모든 명령 리스트를 실행할 때 까지 기다린다.
	WaitForGpuComplete();
}

CGameFramework::~CGameFramework() {

}

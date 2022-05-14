
#pragma once
#include "stdafx.h"
#include "GameFramework.h"

class CGameFramework {
public:
	CGameFramework();
	~CGameFramework();
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	int m_nWndClientWidth;
	int m_nWndClientHeight;

	// DXGI 팩토리 인터페이스에 대한 포인터이다.
	IDXGIFactory4* m_pdxgiFactory;
	// 스왑 체인 인터페이스에 대한 포인터이다. 주로 디스플레이를 제어하기 위하여 필요하다.
	IDXGISwapChain3* m_pdxgiSwapChain;
	// Direct3D 디바이스 인터페이스에 대한 포인터이다. 주로 리소스를 생성하기 위하여 필요하다.
	ID3D12Device* m_pd3dDevice;

	bool m_bMsaa4xEnable = false;

	// MSAA 다중 샘플링을 활성화하고 다중 샘플링 레벨을 설정한다.
	UINT m_nMsaa4xQualityLevels = 0;

	// 스왑 체인의 후면 버퍼의 개수이다.
	static const UINT m_nSwapChainBuffers = 2;
	// 현재 스왑 체인의 후면 버퍼 인덱스이다. 
	UINT m_nSwapChainBufferIndex;

	// 렌더 타겟 버퍼, 서술자 힙 인터페이스 포인터, 렌더 타겟 서술자 원소의 크기이다.
	ID3D12Resource* m_ppd3dRenderTargetBuffers[m_nSwapChainBuffers];
	ID3D12DescriptorHeap* m_pd3dRtvDescriptorHeap;
	UINT m_nRtvDescriptorIncrementSize;

	// 깊이-스텐실 버퍼, 서술자 힙 인터페이스 포인터, 깊이-스텐실 서술자 원소의 크기이다.
	ID3D12Resource* m_pd3dDepthStencilBuffer;
	ID3D12DescriptorHeap* m_pd3dRtvDescriptorHeap;
	UINT m_nRtvDescriptorIncrementSize;

	// 명령 큐, 명령 할당자, 명령 리스트 인터페이스 포인터이다.
	ID3D12CommandQueue* m_pd3dCommandQueue;
	ID3D12CommandAllocator* m_pd3dCommandAllocator;
	ID3D12GraphicsCommandList* m_pd3dCommandList;


};


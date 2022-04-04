

#pragma once

class CGameFramework {
public:
	CGameFramework();
	~CGameFramework();

	// 프레임워크를 초기화하는 함수(주 윈도우가 생성되면 호출)
	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	void OnDestroy();

	void CreateSwapChain();					// 스왑체인 생성
	void CreateRtvAndDsvDescriptorHeaps();	// 디바이스 생성
	void CreateDirect3DDevice();			// 서술자 힙 생성
	void CreateCommandQueueAndList();		// 명령 큐/할당자/리스트를 생성

	// 렌더 타겟 뷰 생성하는 함수
	void CreateRenderTargetViews();
	// 깊이-스텐실 뷰 생성
	void CreateDepthStencilView();

	// 렌더링할 메쉬와 게임 객체를 생성 및 소멸
	void BuildObjects();
	void ReleaseObjects();

	// 프레임워크의 핵심을 구성하는 함수
	void ProcessInput();		// 사용자 입력
	void AnimateObjects();		// 애니메이션
	void FrameAdvance();		// 렌더링

	// CPU와 GPU를 동기화
	void WaitForGpuComplete();
	
	// 윈도우의 메시지(마우스)
	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam,
		LPARAM lParam);
	// 윈도우의 메시지(키보드)
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam,
		LPARAM lParam);
	// 윈도우메세지를 처리하는 콜백 함수
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID,
		WPARAM wParam, LPARAM lParam);
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	int m_nWndClientWidth;
	int m_nWndClientHeight;

	// DXGI 팩토리 인터페이스에 대한 포인터
	IDXGIFactory4* m_pdxgiFactory;
	// 스왑 체인 인터페이스에 대한 포인터. 주로 디스플레이를 제어하기 위해 필요
	IDXGISwapChain3 * m_pdxgiSwapChain;
	// Direct3D 디바이스 인터페이스에 대한 포인터. 주로 리소스를 생성하기 위해 필요
	ID3D12Device* m_pd3dDevice;

	bool m_bMsaa4xEnable = false;
	// MSAA 다중 샘플링을 활성화하고 다중 샘플링 레벨을 설정한다
	UINT m_nMsaa4xQualityLevels = 0;

	// 스왑 체인의 후면 버퍼의 개수이다
	static const UINT m_nSwapChainBuffers = 2;
	// 현재 스왑 체인의 후면 버퍼 인덱스이다
	UINT m_nSwapChainBufferIndex;

	// 렌더 타겟 버퍼 인터페이스 포인터
	ID3D12Resource* m_ppd3dRenderTargetBuffers[m_nSwapChainBuffers];
	// 서술자 힙 인터페이스 포인터
	ID3D12DescriptorHeap* m_pd3dRtvDescriptorHeap;
	// 렌더 타겟 서술자 원소의 크기 rtv = render target view
	UINT m_nRtvDescriptorIncrementSize;

	// 깊이-스텐실 버퍼 인터페이스 포인터
	ID3D12Resource* m_pd3dDepthStencilBuffer;
	// 서술자 힙 인터페이스 포인터
	ID3D12DescriptorHeap* m_pd3dDsvDescriptorHeap;
	// 깊이-스텐실 서술자 원소의 크기 dsv depth stencil view
	UINT m_nDsvDescriptorIncrementSize;

	// 명령 큐 인터페이스 포인터
	ID3D12CommandQueue* m_pd3dCommandQueue;
	// 명령 할당자 인터페이스 포인터
	ID3D12CommandAllocator* m_pd3dCommandAllocator;
	// 명령 리스트 인터페이스 포인터
	ID3D12GraphicsCommandList* m_pd3dCommandList;

	// 그래픽스 파이프라인 상태 객체에 대한 인터페이스 포인터
	ID3D12PipelineState* m_pd3dPipelineState;

	// 펜스 인터페이스 포인터
	ID3D12Fence* m_pd3dFence;
	// 펜스 값
	UINT64 m_nFenceValue;
	// 이벤트 핸들
	HANDLE m_hFenceEvent;

	// 뷰포트
	D3D12_VIEWPORT m_d3dViewport;
	// 씨저 사각형
	D3D12_RECT m_d3dScissorRect;
};


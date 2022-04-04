

#pragma once

class CGameFramework {
public:
	CGameFramework();
	~CGameFramework();

	// �����ӿ�ũ�� �ʱ�ȭ�ϴ� �Լ�(�� �����찡 �����Ǹ� ȣ��)
	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	void OnDestroy();

	void CreateSwapChain();					// ����ü�� ����
	void CreateRtvAndDsvDescriptorHeaps();	// ����̽� ����
	void CreateDirect3DDevice();			// ������ �� ����
	void CreateCommandQueueAndList();		// ��� ť/�Ҵ���/����Ʈ�� ����

	// ���� Ÿ�� �� �����ϴ� �Լ�
	void CreateRenderTargetViews();
	// ����-���ٽ� �� ����
	void CreateDepthStencilView();

	// �������� �޽��� ���� ��ü�� ���� �� �Ҹ�
	void BuildObjects();
	void ReleaseObjects();

	// �����ӿ�ũ�� �ٽ��� �����ϴ� �Լ�
	void ProcessInput();		// ����� �Է�
	void AnimateObjects();		// �ִϸ��̼�
	void FrameAdvance();		// ������

	// CPU�� GPU�� ����ȭ
	void WaitForGpuComplete();
	
	// �������� �޽���(���콺)
	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam,
		LPARAM lParam);
	// �������� �޽���(Ű����)
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam,
		LPARAM lParam);
	// ������޼����� ó���ϴ� �ݹ� �Լ�
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID,
		WPARAM wParam, LPARAM lParam);
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	int m_nWndClientWidth;
	int m_nWndClientHeight;

	// DXGI ���丮 �������̽��� ���� ������
	IDXGIFactory4* m_pdxgiFactory;
	// ���� ü�� �������̽��� ���� ������. �ַ� ���÷��̸� �����ϱ� ���� �ʿ�
	IDXGISwapChain3 * m_pdxgiSwapChain;
	// Direct3D ����̽� �������̽��� ���� ������. �ַ� ���ҽ��� �����ϱ� ���� �ʿ�
	ID3D12Device* m_pd3dDevice;

	bool m_bMsaa4xEnable = false;
	// MSAA ���� ���ø��� Ȱ��ȭ�ϰ� ���� ���ø� ������ �����Ѵ�
	UINT m_nMsaa4xQualityLevels = 0;

	// ���� ü���� �ĸ� ������ �����̴�
	static const UINT m_nSwapChainBuffers = 2;
	// ���� ���� ü���� �ĸ� ���� �ε����̴�
	UINT m_nSwapChainBufferIndex;

	// ���� Ÿ�� ���� �������̽� ������
	ID3D12Resource* m_ppd3dRenderTargetBuffers[m_nSwapChainBuffers];
	// ������ �� �������̽� ������
	ID3D12DescriptorHeap* m_pd3dRtvDescriptorHeap;
	// ���� Ÿ�� ������ ������ ũ�� rtv = render target view
	UINT m_nRtvDescriptorIncrementSize;

	// ����-���ٽ� ���� �������̽� ������
	ID3D12Resource* m_pd3dDepthStencilBuffer;
	// ������ �� �������̽� ������
	ID3D12DescriptorHeap* m_pd3dDsvDescriptorHeap;
	// ����-���ٽ� ������ ������ ũ�� dsv depth stencil view
	UINT m_nDsvDescriptorIncrementSize;

	// ��� ť �������̽� ������
	ID3D12CommandQueue* m_pd3dCommandQueue;
	// ��� �Ҵ��� �������̽� ������
	ID3D12CommandAllocator* m_pd3dCommandAllocator;
	// ��� ����Ʈ �������̽� ������
	ID3D12GraphicsCommandList* m_pd3dCommandList;

	// �׷��Ƚ� ���������� ���� ��ü�� ���� �������̽� ������
	ID3D12PipelineState* m_pd3dPipelineState;

	// �潺 �������̽� ������
	ID3D12Fence* m_pd3dFence;
	// �潺 ��
	UINT64 m_nFenceValue;
	// �̺�Ʈ �ڵ�
	HANDLE m_hFenceEvent;

	// ����Ʈ
	D3D12_VIEWPORT m_d3dViewport;
	// ���� �簢��
	D3D12_RECT m_d3dScissorRect;
};


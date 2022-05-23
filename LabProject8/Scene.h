
#pragma once
#include "Timer.h"
#include "Camera.h"

class CShader;
class CGameObject;

class CScene {
public:
	CScene();
	~CScene();

	// ������ ���콺�� Ű���� �޽����� ó���Ѵ�.
	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam,
		LPARAM lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam,
		LPARAM lParam);

	void BuildObjects(ID3D12Device* pd3dDevice,
		ID3D12GraphicsCommandList* pd3dCommandList);
	void ReleaseObjects();
	
	bool ProcessInput(UCHAR* pKeysBuffer);
	void AnimateObjects(float fTimeElapsed);
	void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera);

	void ReleaseUploadBuffers();

	// �׷��� ��Ʈ �ñ׳��ĸ� �����Ѵ�.
	ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device* pd3dDevice);
	ID3D12RootSignature* GetGraphicsRootSignature();

protected:
	CGameObject** m_ppObjects = NULL;
	int m_nObjects = 0;

	// ��Ʈ �ñ״�ó�� ��Ÿ���� �������̽� �������̴�.
	ID3D12RootSignature* m_pd3dGraphicsRootSignature = NULL;
};

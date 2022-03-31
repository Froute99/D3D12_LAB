


#pragma once
#include "Player.h"
#include "Scene.h"

namespace _3DLab {
	class GameFramework {
	public:
		GameFramework() { }
		~GameFramework() { }
	private:
		//������ �������α׷��� �ν��Ͻ� �ڵ�� �� ������ �ڵ��̴�.
		HINSTANCE m_hInstance = nullptr;
		HWND m_hWnd = nullptr;
		
		//�� �������� Ŭ���̾�Ʈ �簢�� �����̴�.
		RECT m_clientRect;
		
		//�������� ����� �Ǵ� ȭ�鿡 �ش��ϴ� ��Ʈ�ʰ� ��Ʈ�� ����̽� ���ؽ�Ʈ(Device Context)�̴�.
		HDC m_hDCFrameBuffer = nullptr;
		HBITMAP m_hBitmapFrameBuffer = nullptr;
		HBITMAP m_hBitmapSelect = nullptr;
		
		//�÷��̾� ��ü�̴�.
		Player* m_pPlayer = nullptr;
		
		//���� ��ü���� �����ϴ� ��(���� ����) Ŭ�����̴�. 
		Scene* m_pScene = nullptr;
	public:
		//�����ӿ�ũ�� �����ϴ� �Լ��̴�(�� �����찡 �����Ǹ� ȣ��ȴ�). 
		void OnCreate(HINSTANCE hInstance, HWND hMainWnd);
		
		//�����ӿ�ũ�� �Ҹ��ϴ� �Լ��̴�(�������α׷��� ����Ǹ� ȣ��ȴ�). 
		void OnDestroy();
		
		//���� ���踦 �������� ��Ʈ�� ǥ���� �����ϰ�, �����, Ŭ���̾�Ʈ �������� �����Ѵ�.
		void BuildFrameBuffer();
		void ClearFrameBuffer(DWORD color);
		void PresentFrameBuffer();
		
		//�������� �޽��� ���� ��ü�� �����ϰ� �Ҹ��ϴ� �Լ��̴�.
		void BuildObjects(); 
		void ReleaseObjects();
		
		//�����ӿ�ũ�� �ٽ�(����� �Է�, �ִϸ��̼�, ������)�� �����ϴ� �Լ��̴�.
		void ProcessInput();
		void AnimateObjects();
		void FrameAdvance();
	};
}

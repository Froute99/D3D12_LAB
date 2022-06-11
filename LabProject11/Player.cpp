#include "stdafx.h"
#include "Player.h"
#include "Shader.h"

CPlayer::CPlayer()
{
	m_pCamera = NULL;
	m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_xmf3Right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_xmf3Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_xmf3Look = XMFLOAT3(0.0f, 0.0f, 1.0f);

	m_xmf3Velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_xmf3Gravity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_fMaxVelocityXZ = 0.0f;
	m_fMaxVelocityY = 0.0f;
	m_fFriction = 0.0f;

	m_fPitch = 0.0f;
	m_fRoll = 0.0f;
	m_fYaw = 0.0f;

	m_pPlayerUpdatedContext = NULL;
	m_pCameraUpdatedContext = NULL;
}

CPlayer::~CPlayer()
{
	ReleaseShaderVariables();
	if (m_pCamera) delete m_pCamera;
}

void CPlayer::CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	CGameObject::CreateShaderVariables(pd3dDevice, pd3dCommandList);

	if (m_pCamera) m_pCamera->CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CPlayer::ReleaseShaderVariables()
{
	CGameObject::ReleaseShaderVariables();

	if (m_pCamera) m_pCamera->ReleaseShaderVariables();
}

void CPlayer::UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList)
{
	CGameObject::UpdateShaderVariables(pd3dCommandList);
}

/*플레이어의 위치를 변경하는 함수이다. 플레이어의 위치는 기본적으로 사용자가 플레이어를 이동하기 위한 키보드를
누를 때 변경된다. 플레이어의 이동 방향(dwDirection)에 따라 플레이어를 fDistance 만큼 이동한다.*/
void CPlayer::Move(DWORD dwDirection, float fDistance, bool bUpdateVelocity)
{
	if (dwDirection)
	{
		XMFLOAT3 xmf3Shift = XMFLOAT3(0, 0, 0);
		//화살표 키 ‘↑’를 누르면 로컬 z-축 방향으로 이동(전진)한다. ‘↓’를 누르면 반대 방향으로 이동한다.
		if (dwDirection & DIR_FORWARD) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Look, fDistance);
		if (dwDirection & DIR_BACKWARD) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Look, -fDistance);
		//화살표 키 ‘→’를 누르면 로컬 x-축 방향으로 이동한다. ‘←’를 누르면 반대 방향으로 이동한다.
		if (dwDirection & DIR_RIGHT) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Right, fDistance);
		if (dwDirection & DIR_LEFT) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Right, -fDistance);
		//‘Page Up’을 누르면 로컬 y-축 방향으로 이동한다. ‘Page Down’을 누르면 반대 방향으로 이동한다.
		if (dwDirection & DIR_UP) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Up, fDistance);
		if (dwDirection & DIR_DOWN) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Up, -fDistance);

		//플레이어를 현재 위치 벡터에서 xmf3Shift 벡터만큼 이동한다.
		Move(xmf3Shift, bUpdateVelocity);
	}
}

void CPlayer::Move(const XMFLOAT3& xmf3Shift, bool bUpdateVelocity)
{
	// bUpdateVelocity가 참이면 플레이어를 이동하지 않고 속도 벡터를 변경한다.
	if (bUpdateVelocity)
	{
		// 플레이어의 속도 벡터를 xmf3Shift 벡터만큼 변경한다.
		m_xmf3Velocity = Vector3::Add(m_xmf3Velocity, xmf3Shift);
	}
	else
	{
		// 플레이어를 현재 위치 벡터에서 xmf3Shift 벡터만큼 이동한다.
		m_xmf3Position = Vector3::Add(m_xmf3Position, xmf3Shift);
		// 플레이어의 위치가 변경되었으므로 카메라의 위치도 xmf3Shift 벡터만큼 이동한다.
		if (m_pCamera) m_pCamera->Move(xmf3Shift);
	}
}

// 플레이어를 로컬 x-축, y-축, z-축을 중심으로 회전한다.
void CPlayer::Rotate(float x, float y, float z)
{
	DWORD nCameraMode = m_pCamera->GetMode();
	// 1인칭 카메라 또는 3인칭 카메라의 경우 플레이어의 회전은 약간의 제약이 따른다.
	if ((nCameraMode == FIRST_PERSON_CAMERA) || (nCameraMode == THIRD_PERSON_CAMERA))
	{
		/* 로컬 x-축을 중심으로 회전하는 것은 고개를 앞뒤로 숙이는 동작에 해당한다. 그러므로 x-축을 중심으로 회전하는
		각도는 -89.0~+89.0도 사이로 제한한다. x는 현재의 m_fPitch에서 실제 회전하는 각도이므로 x만큼 회전한 다음
		Pitch가 +89도 보다 크거나 -89도 보다 작으면 m_fPitch가 +89도 또는 -89도가 되도록 회전각도(x)를 수정한다. */
		if (x != 0.0f)
		{
			m_fPitch += x;
			if (m_fPitch > +89.0f) { x -= (m_fPitch - 89.0f); m_fPitch = +89.0f; }
			if (m_fPitch < -89.0f) { x -= (m_fPitch + 89.0f); m_fPitch = -89.0f; }
		}
		if (y != 0.0f)
		{
			// 로컬 y-축을 중심으로 회전하는 것은 몸통을 돌리는 것이므로 회전 각도의 제한이 없다.
			m_fYaw += y;
			if (m_fYaw > 360.0f) m_fYaw -= 360.0f;
			if (m_fYaw < 0.0f) m_fYaw += 360.0f;
		}
		if (z != 0.0f)
		{
			/* 로컬 z-축을 중심으로 회전하는 것은 몸통을 좌우로 기울이는 것이므로 회전 각도는 -20.0~+20.0도 사이로 제한된
			다. z는 현재의 m_fRoll에서 실제 회전하는 각도이므로 z만큼 회전한 다음 m_fRoll이 +20도 보다 크거나 -20도보다
			작으면 m_fRoll이 +20도 또는 -20도가 되도록 회전각도(z)를 수정한다. */
			m_fRoll += z;
			if (m_fRoll > +20.0f) { z -= (m_fRoll - 20.0f); m_fRoll = +20.0f; }
			if (m_fRoll < -20.0f) { z -= (m_fRoll + 20.0f); m_fRoll = -20.0f; }
		}
		// 카메라를 x, y, z 만큼 회전한다. 플레이어를 회전하면 카메라가 회전하게 된다.
		m_pCamera->Rotate(x, y, z);

		/* 플레이어를 회전한다. 1인칭 카메라 또는 3인칭 카메라에서 플레이어의 회전은 로컬 y-축에서만 일어난다. 플레이어
		의 로컬 y-축(Up 벡터)을 기준으로 로컬 z-축(Look 벡터)와 로컬 x-축(Right 벡터)을 회전시킨다. 기본적으로 Up 벡터를
		기준으로 회전하는 것은 플레이어가 똑바로 서있는 것을 가정한다는 의미이다. */
		if (y != 0.0f)
		{
			XMMATRIX xmmtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3Up), XMConvertToRadians(y));
			m_xmf3Look = Vector3::TransformNormal(m_xmf3Look, xmmtxRotate);
			m_xmf3Right = Vector3::TransformNormal(m_xmf3Right, xmmtxRotate);
		}
	}
	else if (nCameraMode == SPACESHIP_CAMERA)
	{
		/*스페이스-쉽 카메라에서 플레이어의 회전은 회전 각도의 제한이 없다. 그리고 모든 축을 중심으로 회전을 할 수 있다.*/
		m_pCamera->Rotate(x, y, z);
		if (x != 0.0f)
		{
			XMMATRIX xmmtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3Right), XMConvertToRadians(x));
			m_xmf3Look = Vector3::TransformNormal(m_xmf3Look, xmmtxRotate);
			m_xmf3Up = Vector3::TransformNormal(m_xmf3Up, xmmtxRotate);
		}
		if (y != 0.0f)
		{
			XMMATRIX xmmtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3Up), XMConvertToRadians(y));
			m_xmf3Look = Vector3::TransformNormal(m_xmf3Look, xmmtxRotate);
			m_xmf3Right = Vector3::TransformNormal(m_xmf3Right, xmmtxRotate);
		}
		if (z != 0.0f)
		{
			XMMATRIX xmmtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3Look), XMConvertToRadians(z));
			m_xmf3Up = Vector3::TransformNormal(m_xmf3Up, xmmtxRotate);
			m_xmf3Right = Vector3::TransformNormal(m_xmf3Right, xmmtxRotate);
		}
	}

	/*회전으로 인해 플레이어의 로컬 x-축, y-축, z-축이 서로 직교하지 않을 수 있으므로 z-축(Look 벡터)을 기준으로
	하여 서로 직교하고 단위벡터가 되도록 한다.*/
	m_xmf3Look = Vector3::Normalize(m_xmf3Look);
	m_xmf3Right = Vector3::CrossProduct(m_xmf3Up, m_xmf3Look, true);
	m_xmf3Up = Vector3::CrossProduct(m_xmf3Look, m_xmf3Right, true);
}


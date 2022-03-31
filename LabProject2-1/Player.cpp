
#include "stdafx.h"
#include "Player.h"

namespace _3DLab {
	void Player::SetPosition(float x, float y, float z) {
		GameObject::SetPosition(x, y, z);
		if (m_pCamera) {
			m_pCamera->SetPosition(x, y, z);
		}
	}

	void Player::SetRotation(float x, float y, float z) {
		GameObject::SetRotation(x, y, z);
		if (m_pCamera) {
			m_pCamera->SetRotation(x, y, z);
		}
	}

	void Player::Move(float x, float y, float z) {
		if (m_pCamera) {
			m_pCamera->Move(x, y, z);
		}
		GameObject::Move(x, y, z);
	}

	void Player::Rotate(float pitch, float yaw, float roll) {
		if (m_pCamera) {
			m_pCamera->Rotate(pitch, yaw, roll);
		}
		GameObject::Rotate(pitch, yaw, roll);
	}
}

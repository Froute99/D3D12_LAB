
#pragma once

class CScene {
public:
	void BuildObjects(ID3D12Device* pd3dDevice);
	void ReleaseObjects();
	void AnimateObjects(float elpasedTime);

	void Render(ID3D12GraphicsCommandList* pd3dCommandList);
};


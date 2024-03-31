#pragma once
#include "CameraMovement.h"

//================================================================
/// FPS�̂悤�ȃJ�����B�J�����N���X�ɃR���X�g���N�^�Œ�������
//================================================================
class TestCamera :public CameraMovement {
public:
	TestCamera();
	
	//-------------------------------------
	/// [�@�\]�J�����̏�Ԃ̍X�V
	//-------------------------------------
	void Excute(DirectX::XMFLOAT3& cameraPos,DirectX::XMFLOAT3& lookPos)override;
	

private:
	void Move(DirectX::XMFLOAT3& cameraPos);
	void Rotate();
	void UpdateLookPos(DirectX::XMFLOAT3& cameraPos,DirectX::XMFLOAT3& lookPos);

	DirectX::XMVECTOR mQuaternion;
	float mRoll;
};

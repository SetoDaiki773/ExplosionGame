#pragma once
#include <memory>
#include <vector>
#include <DirectXMath.h>

namespace Object {
	enum Type;
}


class Collider {
public:
	//-----------------------------------------------------------------------------------
	/// [�@�\] �������̃^�C�v�̃I�u�W�F�N�g�Ƒ������̓����蔻�肪�����������𒲂ׂ�
	//-----------------------------------------------------------------------------------
	static bool IsHit(Object::Type detectionTarget, const class SphereHitBox& hitBox);
	//------------------------------------------------------------------------------------
	/// [�@�\] �������̓����蔻�肪���������������^�C�v�̃I�u�W�F�N�g�̃|�C���^��n��
	//------------------------------------------------------------------------------------
	static std::shared_ptr<class GameObject> GetHitObject(Object::Type detectionTarget,const class SphereHitBox& hitBox);
	//--------------------------------------------------------------------------------------------
	/// [�@�\] �������̓����蔻�肪���������������^�C�v�̃I�u�W�F�N�g��S�ēn��
	//--------------------------------------------------------------------------------------------
	static std::vector<std::shared_ptr<class GameObject>> GetHitObjects(Object::Type detectionTarget, const class SphereHitBox& hitBox);
	//---------------------------------------------------
	/// [�@�\] �ǂɓ������������ׂ�
	//---------------------------------------------------
	static bool IsHitWithWall(const DirectX::XMFLOAT3& pos);
	//---------------------------------------------------
	/// [�@�\] ���E�̕ǂɓ������������ׂ�
	//---------------------------------------------------
	static bool IsHitSideWall(const DirectX::XMFLOAT3& pos);
	//---------------------------------------------------
	/// [�@�\] �O��̕ǂɓ����������𒲂ׂ�
	//---------------------------------------------------
	static bool IsHitFrontOrBackWall(const DirectX::XMFLOAT3& pos);
};

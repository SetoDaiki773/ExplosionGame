#pragma once
#include <memory>

using IsDead = bool;

//======================================
///  HP�Ǘ��N���X
//======================================
class HitPoint {
public:
	

	HitPoint(unsigned maxHitPoint,int invincibleTime = 0);
	
	void Update();
	//---------------------------------------
	/// [�@�\] HP��amount���񕜂���
	//---------------------------------------
	void Recovery(unsigned amount);
	//------------------------------------------------------------
	/// [�@�\] HP��amount�����炵�A���񂾂��ǂ�����߂�l�ŕԂ�
	//------------------------------------------------------------
	IsDead Damege(unsigned amount);
	//------------------------------------------------------------
	/// [�@�\] HP�̐������n�[�g��`�悷��B
	//------------------------------------------------------------
	void RenderHitPoint(const class Camera& camera);
	bool IsInvincible();

private:
	const unsigned mMaxHP;
	unsigned mCurrentHP;
	std::unique_ptr<class UI> mHitPointUI;
	std::unique_ptr<class WorldTransform> mHitPointUIWorld;
	std::unique_ptr<class InvincibleTime> mInvincible;

};

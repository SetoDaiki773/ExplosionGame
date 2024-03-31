#pragma once
#include"GameObject.h"

class Monster : public GameObject {
public:
	Monster();

	void Update()override;

private:
	int mCount;
	int mMissileInterval; // �~�T�C�����΂��C���^�[�o��
	std::unique_ptr<class RotationMovement> mMovement; // ��]
};

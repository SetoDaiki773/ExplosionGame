#pragma once
#include"GameObject.h"

class Monster : public GameObject {
public:
	Monster();

	void Update()override;

private:
	int mCount;
	int mMissileInterval; // ミサイルを飛ばすインターバル
	std::unique_ptr<class RotationMovement> mMovement; // 回転
};

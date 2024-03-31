#pragma once
#include "GameObject.h"

/// 振る舞いを持たないゲームオブジェクト
class NullObject : public GameObject {
public:
	NullObject();
	void Render(const class Camera&)override;


};

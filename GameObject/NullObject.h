#pragma once
#include "GameObject.h"

/// �U�镑���������Ȃ��Q�[���I�u�W�F�N�g
class NullObject : public GameObject {
public:
	NullObject();
	void Render(const class Camera&)override;


};

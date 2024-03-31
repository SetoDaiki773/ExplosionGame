#pragma once
#include "GameObject.h"
#include <memory>

namespace Object {
	enum Type;
}

using SpawnFunc = GameObjectPtrS(*)();


/// �I�u�W�F�N�g���������ŃX�|�[������I�u�W�F�N�g
class Spawner : public GameObject{
public:

	Spawner(SpawnFunc spawnFunc, unsigned spawnCycle);
	~Spawner()override {};

	void Update()override;

private:
	void DecideSpawnPos();

	SpawnFunc mSpawnFunc; // �I�u�W�F�N�g�̐����֐�
	unsigned mSpawnCycle; // ��������
	unsigned mCount;      // �o�ߎ���

};

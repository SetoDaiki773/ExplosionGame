#pragma once
#include "GameObject.h"
#include <memory>

namespace Object {
	enum Type;
}

using SpawnFunc = GameObjectPtrS(*)();


/// オブジェクトを一定周期でスポーンするオブジェクト
class Spawner : public GameObject{
public:

	Spawner(SpawnFunc spawnFunc, unsigned spawnCycle);
	~Spawner()override {};

	void Update()override;

private:
	void DecideSpawnPos();

	SpawnFunc mSpawnFunc; // オブジェクトの生成関数
	unsigned mSpawnCycle; // 生成周期
	unsigned mCount;      // 経過時間

};

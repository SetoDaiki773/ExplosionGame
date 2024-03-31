#include "Spawner.h"
#include "Manager/GameObjectManager.h"
#include "ObjectComponent/WorldTransform.h"
#include "ObjectComponent/Sprite.h"
#include "Common/Random.h"
#include "Common/MyMath.h"

using namespace DirectX;

Spawner::Spawner(SpawnFunc spawnFunc,unsigned spawnCycle) 
	:GameObject(ObjectResourcePtrS(new Sprite(L"Asset/RobotSpawner.png")), WorldPtrU(new WorldTransform()))
	,mSpawnFunc(spawnFunc)
	,mSpawnCycle(spawnCycle)
	,mCount(0)
{
	XMVECTOR rot = Math::QuaternionRotateEuler(270.0f, 0.0f, 0.0f);
	mWorld->SetRot(rot);
	XMFLOAT3 scale(2.0f,2.0f,2.0f);
	mWorld->SetScale(scale);

	DecideSpawnPos();

}


void Spawner::Update() {
	mCount++;
	// スポーン時間になったら
	if (mCount >= mSpawnCycle ) {
		// 渡された関数をもとに作る
		GameObjectPtrS spawnObject = mSpawnFunc();
		XMFLOAT3 spawnObjectPos = GetPos(); // スぽーナーの位置が
		spawnObject->SetPos(spawnObjectPos); // スポーンされたオブジェクトの位置
		DecideSpawnPos(); // 次のすぽーなーの位置を決定して
		mCount = 0; // カウントを0に

	}

}


void Spawner::DecideSpawnPos() {
	XMFLOAT3 pos;
	// -45～45をすぽーなーの位置に決定する
	pos.x = Random::RandomFloat(-45.0f, 45.0f);
	pos.z = Random::RandomFloat(-45.0f, 45.0f);
	pos.y = 5.01f;
	mWorld->SetPos(pos);
}
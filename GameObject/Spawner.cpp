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
	// �X�|�[�����ԂɂȂ�����
	if (mCount >= mSpawnCycle ) {
		// �n���ꂽ�֐������Ƃɍ��
		GameObjectPtrS spawnObject = mSpawnFunc();
		XMFLOAT3 spawnObjectPos = GetPos(); // �X�ہ[�i�[�̈ʒu��
		spawnObject->SetPos(spawnObjectPos); // �X�|�[�����ꂽ�I�u�W�F�N�g�̈ʒu
		DecideSpawnPos(); // ���̂��ہ[�ȁ[�̈ʒu�����肵��
		mCount = 0; // �J�E���g��0��

	}

}


void Spawner::DecideSpawnPos() {
	XMFLOAT3 pos;
	// -45�`45�����ہ[�ȁ[�̈ʒu�Ɍ��肷��
	pos.x = Random::RandomFloat(-45.0f, 45.0f);
	pos.z = Random::RandomFloat(-45.0f, 45.0f);
	pos.y = 5.01f;
	mWorld->SetPos(pos);
}
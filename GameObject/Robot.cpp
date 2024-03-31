#include "Robot.h"
#include "ObjectComponent/WorldTransform.h"
#include "ObjectComponent/Model.h"
#include "Manager/ModelManager.h"
#include "Manager/GameObjectManager.h"
#include "ObjectComponent/Sprite.h"
#include "Common/MyMath.h"
#include "Common/Random.h"
#include "Common/Printer.h"
#include "Collision/SphereHitBox.h"
#include "Collision/Collider.h"
#include "AudioSystem.h"
#include "Event.h"
#include "Camera/Camera.h"
#include <iostream>
#include <cmath>

using namespace DirectX;

std::unique_ptr<Sprite> Robot::mBombAttachingNotifier; 

Robot::Robot()
	:GameObject(ModelPtrS(ModelManager::GetModel("Asset/robot.fbx")),WorldPtrU(new WorldTransform(XMFLOAT3(0.0f,5.1f,0.0f))))
	,mRevisedValue(0.3f)
	,mBombAttaching(false)
{
	XMFLOAT3 pos = mWorld->GetPos();
	pos.y = 4.0f;
	mWorld->SetPos(pos);
	mWorld->SetScale(XMFLOAT3(0.003f,0.003f,0.003f));
	float moveAngle = Random::RandomFloat(0, 360);  // ランダムでy軸周りの回転を決定
	mRotY = moveAngle;
	XMVECTOR robotRotate = Math::QuaternionRotateEuler(0.0f, moveAngle, 0.0f);
	mWorld->SetRot(robotRotate);
	mMoveDirection = Math::GetFront(robotRotate);  // 前方方向に移動する
	mMoveDirection = mRevisedValue * mMoveDirection; // 補正

	mHitBox = std::make_unique<SphereHitBox>(mWorld->GetPos(), 2.0f);

	static bool isFirst = true;
	// static変数の割り当て
	if (isFirst) {
		// 自分にボムが取り付けられていることを知らせるスプライト
		mBombAttachingNotifier = std::make_unique<Sprite>(L"Asset/Bomb.png");
		isFirst = false;
	}
}

Robot::~Robot() {

}



void Robot::Update() {

	// 壁に当たったら動き反転
	if (Collider::IsHitFrontOrBackWall(mWorld->GetPos())) ReverseMovementZ();
	if (Collider::IsHitSideWall(mWorld->GetPos())) ReverseMovementX();
	
	// プレイヤーに当たったら押される
	std::vector<GameObjectPtrS> gameObject = GameObjectManager::GetGameObject(Object::EPlayer);
	if (!gameObject.empty()) {
		const HitBox& playerHitBox = gameObject[0]->GetHitBox();
		if (playerHitBox.IsHitWithSphere(static_cast<const SphereHitBox&>(GetHitBox()))) {
			BePushedByPlayer(gameObject[0]->GetWorld().GetPos());
			return;  //押されたらそのまま帰る
		}
	}

	
	const bool isHitExplosion = Collider::IsHit(Object::EExplosion, static_cast<const SphereHitBox&>(GetHitBox()));
	const bool isHitBigExplosion = Collider::IsHit(Object::EBigExplosion, static_cast<const SphereHitBox&>(GetHitBox()));
	const bool isHitRobot = Collider::IsHit(Object::ERobot, static_cast<const SphereHitBox&>(GetHitBox()));
	const bool explosionFlag = isHitExplosion || isHitBigExplosion || isHitRobot; // 爆発かでかい爆発かロボットに当たったら爆発。
	if (explosionFlag) {
		Explosion(); // 爆発
	}
	

	mWorld->AddPos(mMoveDirection);
	
}


void Robot::Render(const Camera& camera) {

	GameObject::Render(camera); // ロボットを描画
	// ボムが取り付けているなら
	if (mBombAttaching) {
		
		XMFLOAT3 notifierPos = GetPos();
		notifierPos.y += 10.0f; // ロボットの少し上の位置に
		XMVECTOR notifierRot = Math::QuaternionRotateEuler(0.0f,180.0f,0.0f);
		XMFLOAT3 notifierScale(2.0f, 2.0f, 2.0f);
		WorldTransform notifierWorld(notifierPos,notifierScale,notifierRot);
		notifierWorld.UpdateWorldMat();

		mBombAttachingNotifier->Render(notifierWorld.GetWorldMat(), camera); // ボムが取り付いていることを知らせる、スプライトを描画する。
	}
}


void Robot::ReceiveEvent(const Event& event) {
	switch(event.mType)
	{
	case (Event::Type::EAttachBomb): // ボム取り付けイベントを受け取ったら、
		AttachBomb();                // ボム取り付け
		break;

	case (Event::Type::EExplosion):  // 爆発イベントを受け取ったら
		Explosion();                 // 爆散
		break;
	case (Event::Type::EDetonate):   // 起爆イベントを受け取ったら
		Detonate();                  // 起爆
	default:
		break;
	}
}

//------------------------------
//   爆弾を取り付ける
//------------------------------
void Robot::AttachBomb() {
	if (!mBombAttaching) {
		AudioSystem& audioSystem = AudioSystem::GetInstance();
		audioSystem.PlayEvent("event:/Attach");
		mBombAttaching = true;
	}
}


//-------------------------------
//   爆散する
//-------------------------------
void Robot::Explosion() {

	GameObjectPtrS explosion = GameObjectManager::CreateExplosion(GetPos());
	mState = State::EDead;

}

//--------------------------------
//  起爆する
//--------------------------------
void Robot::Detonate() {
	if (mBombAttaching) {
		GameObjectManager::CreateBigExplosion(GetPos());
		mState = EDead;
	}
}



//----------------------------------------
//  Z軸方向の移動を反転させる
//----------------------------------------
void Robot::ReverseMovementZ() {
	mRotY = 360.0f - mRotY;                      // X軸移動反転後の角度は ・・・ 180°- 前の角度 
	XMVECTOR quaternion = Math::QuaternionRotateEuler(0.0f, mRotY, 0.0f);
	mWorld->SetRot(quaternion);
	mMoveDirection = Math::GetFront(quaternion);
	mMoveDirection = mRevisedValue * mMoveDirection;
}

//------------------------------------------
//   X軸方向の移動を反転させる
//------------------------------------------
void Robot::ReverseMovementX() {
	mRotY = 180.0f - mRotY;                      // Z軸移動反転後の角度は  ・・・ 360 - 前の角度
	XMVECTOR quaternion = Math::QuaternionRotateEuler(0.0f, mRotY, 0.0f);
	mWorld->SetRot(quaternion);
	mMoveDirection = Math::GetFront(quaternion);
	mMoveDirection = mRevisedValue * mMoveDirection;
}


//--------------------------------
//   プレイヤーに押される
//--------------------------------
void Robot::BePushedByPlayer(const DirectX::XMFLOAT3& playerPos) {
	DirectX::XMFLOAT3 moveVec = mWorld->GetPos() - playerPos;   // プレイヤーからロボットの方向ベクトルが移動方向の元
	// 斜め移動をしないようにxzで小さい移動量を消す
	if (std::abs(moveVec.x) > std::abs(moveVec.z)) {
		moveVec.z = 0.0f;
	}
	else {
		moveVec.x = 0.0f;
	}
	moveVec = 0.20f * moveVec;                                  // 移動量の調整
	moveVec.y = 0.0f;                                           // y軸移動はしない
	DirectX::XMFLOAT3 pos = moveVec + mWorld->GetPos();         // 移動量を現在位置に加える
	if (Collider::IsHitFrontOrBackWall(pos) || Collider::IsHitSideWall(pos)) {      // 加えた結果どれかの壁に当たるなら
		pos = pos - moveVec;						            // 移動をなかったことにする
	}

	mWorld->SetPos(pos);                                        // 位置の更新
}




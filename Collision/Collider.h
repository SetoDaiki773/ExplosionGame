#pragma once
#include <memory>
#include <vector>
#include <DirectXMath.h>

namespace Object {
	enum Type;
}


class Collider {
public:
	//-----------------------------------------------------------------------------------
	/// [機能] 第一引数のタイプのオブジェクトと第二引数の当たり判定が当たったかを調べる
	//-----------------------------------------------------------------------------------
	static bool IsHit(Object::Type detectionTarget, const class SphereHitBox& hitBox);
	//------------------------------------------------------------------------------------
	/// [機能] 第二引数の当たり判定が当たった第一引数タイプのオブジェクトのポインタを渡す
	//------------------------------------------------------------------------------------
	static std::shared_ptr<class GameObject> GetHitObject(Object::Type detectionTarget,const class SphereHitBox& hitBox);
	//--------------------------------------------------------------------------------------------
	/// [機能] 第二引数の当たり判定が当たった第一引数タイプのオブジェクトを全て渡す
	//--------------------------------------------------------------------------------------------
	static std::vector<std::shared_ptr<class GameObject>> GetHitObjects(Object::Type detectionTarget, const class SphereHitBox& hitBox);
	//---------------------------------------------------
	/// [機能] 壁に当たったか調べる
	//---------------------------------------------------
	static bool IsHitWithWall(const DirectX::XMFLOAT3& pos);
	//---------------------------------------------------
	/// [機能] 左右の壁に当たったか調べる
	//---------------------------------------------------
	static bool IsHitSideWall(const DirectX::XMFLOAT3& pos);
	//---------------------------------------------------
	/// [機能] 前後の壁に当たったかを調べる
	//---------------------------------------------------
	static bool IsHitFrontOrBackWall(const DirectX::XMFLOAT3& pos);
};

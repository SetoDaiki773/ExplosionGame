#pragma once
#include <memory>

using IsDead = bool;

//======================================
///  HP管理クラス
//======================================
class HitPoint {
public:
	

	HitPoint(unsigned maxHitPoint,int invincibleTime = 0);
	
	void Update();
	//---------------------------------------
	/// [機能] HPをamount分回復する
	//---------------------------------------
	void Recovery(unsigned amount);
	//------------------------------------------------------------
	/// [機能] HPをamount分減らし、死んだかどうかを戻り値で返す
	//------------------------------------------------------------
	IsDead Damege(unsigned amount);
	//------------------------------------------------------------
	/// [機能] HPの数だけハートを描画する。
	//------------------------------------------------------------
	void RenderHitPoint(const class Camera& camera);
	bool IsInvincible();

private:
	const unsigned mMaxHP;
	unsigned mCurrentHP;
	std::unique_ptr<class UI> mHitPointUI;
	std::unique_ptr<class WorldTransform> mHitPointUIWorld;
	std::unique_ptr<class InvincibleTime> mInvincible;

};

#pragma once

using AlreadyInvincible = bool;

//=========================================
/// 無敵時間クラス。
//=========================================
class InvincibleTime {
public:
	/// 引数は無敵時間
	InvincibleTime(unsigned duration);

	//-----------------------------------
	/// [機能] 無敵時間の開始
	/// [返り値] 既に無敵時間だったか
	//-----------------------------------
	AlreadyInvincible Start();
	void Update();
	bool IsInvincible();


private:
	const unsigned mDuration;
	unsigned mElapsedTime;
	bool mIsInvincible;

};
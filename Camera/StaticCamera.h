#pragma once
#include "CameraMovement.h"

//===========================================================
/// 動かないカメラ。カメラクラスのコンストラクタで注入する
//===========================================================
class StaticCamera :public CameraMovement {
public:
	StaticCamera();
	
	//-------------------------------------
	/// [機能]カメラの状態の更新
	//-------------------------------------
	void Excute(DirectX::XMFLOAT3& pos,DirectX::XMFLOAT3& lookPos)override;
	
private:

};

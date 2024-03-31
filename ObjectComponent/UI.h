#pragma once
#include "ObjectResource.h"
#include <DirectXMath.h>
#include <string>

//========================================
/// 二次元オブジェクト。カメラの影響を受けない
//========================================
class UI : public ObjectResource {
public:
	UI(const std::wstring& textureName);
	~UI();
	UI(UI&& ui);
	

	void Render(const DirectX::XMMATRIX& worldmat,const class Camera& camera)override;

private:
	std::unique_ptr<class MyMesh> mMesh;
	std::unique_ptr<class Renderer> mRenderer;

};

#pragma once
#include <memory>
#include <vector>
#include <DirectXMath.h>
#include <string>
#include "ObjectResource.h"

//=============================================
/// 2次元オブジェクト。カメラの影響を受ける
//=============================================
class Sprite : public ObjectResource{
public:
	Sprite(const std::wstring& textureName);
	~Sprite();
	void Render(const DirectX::XMMATRIX& worldMat, const class Camera& camera)override;

private:
	void CreateSprite(const std::wstring& textureName);
	std::unique_ptr<class MyMesh> mMesh;
	std::unique_ptr<class Renderer> mRenderer;

};
#include "HitBox.h"
#include "GameObject/GameObject.h"
#include "ObjectComponent/WorldTransform.h"
#include "Common/Printer.h"

HitBox::HitBox(const DirectX::XMFLOAT3& ownerPos) 
	:mOwnerPos(ownerPos) // “–‚½‚è”»’è‚Ì‚¿å‚ÌˆÊ’u‚ğQÆ‚·‚é
{
	
}


const DirectX::XMFLOAT3& HitBox::GetPos()const {
	return mOwnerPos;
}

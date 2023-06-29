#include "FieldEffect.h"

#include<GameEngineCore/GameEngineRenderer.h>
#include<GameEngineCore/ResourcesManager.h>
#include<GameEnginePlatform/GameEngineWindowTexture.h>

FieldEffect::FieldEffect()
{
}

FieldEffect::~FieldEffect()
{
}


void FieldEffect::SetGroundTexture(const std::string& _GroundTextureName)
{
	GroundTexture = ResourcesManager::GetInst().FindTexture(_GroundTextureName);

	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("�������� �ʴ� �ؽ�ó�� �ȼ��浹�� �Ϸ��� �߽��ϴ�.");
	}

}

int FieldEffect::GetGroundColor(unsigned int _DefaultColor, float4 _Pos)
{
	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("�� üũ�� �ؽ�ó�� �������� �ʽ��ϴ�.");
	}

	return GroundTexture->GetColor(_DefaultColor, GetPos() + _Pos);
}

void FieldEffect::Update(float _Delta)
{


	if (nullptr != Renderer)
	{
		if (true==Renderer->IsAnimationEnd())
		{
			Death();
		}
	}
	else 
	{
		Death();
	}
}


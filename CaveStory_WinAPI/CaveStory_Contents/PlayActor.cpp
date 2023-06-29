#include "PlayActor.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/ResourcesManager.h>

PlayActor::PlayActor()
{
}

PlayActor::~PlayActor()
{
}

void PlayActor::Gravity(float _Delta)
{
	if (false == IsGravity)
	{
		return;
	}

	GravityVector += float4::DOWN * GravityPower * _Delta;

	AddPos(GravityVector);

}

void PlayActor::CameraFocus()
{
	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();
	
	
	float4 CheckPos = GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() };
	
	if (CheckPos.X < 0)
	{
		CheckPos.X = 0;

	}
	if (CheckPos.X > Boundery.X - WindowScale.X)
	{
		CheckPos.X = Boundery.X - WindowScale.X;
	}
	if (CheckPos.Y < 0)
	{
		CheckPos.Y = 0;
	}
	if (CheckPos.Y > Boundery.Y - WindowScale.Y)
	{
		CheckPos.Y = Boundery.Y-WindowScale.Y;
	}

		//GetLevel()->GetMainCamera()->SetPos(GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() });
	GetLevel()->GetMainCamera()->SetPos(CheckPos);
}

void PlayActor::SetGroundTexture(const std::string& _GroundTextureName)
{
	GroundTexture = ResourcesManager::GetInst().FindTexture(_GroundTextureName);

	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("�������� �ʴ� �ؽ�ó�� �ȼ��浹�� �Ϸ��� �߽��ϴ�.");
	}

}

void PlayActor::SetGroundTexture(GameEngineWindowTexture* _GroundTexture)
{
	if (nullptr == _GroundTexture)
	{
		MsgBoxAssert("�������� �ʴ� �ؽ�ó�� GroundTexture�� �Ϸ��� �߽��ϴ�.");
	}

	GroundTexture = _GroundTexture;
}

int PlayActor::GetGroundColor(unsigned int _DefaultColor, float4 _Pos)
{
	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("�� üũ�� �ؽ�ó�� �������� �ʽ��ϴ�.");
	}

	return GroundTexture->GetColor(_DefaultColor, GetPos() + _Pos);
}

void PlayActor::SetActorBoundery(const std::string& _BounderyTextureName)
{
	BounderyTexture= ResourcesManager::GetInst().FindTexture(_BounderyTextureName);

	if (nullptr == BounderyTexture)
	{
		MsgBoxAssert("�������� �ʴ� �ؽ�ó�� ������ ���� ���� �ٿ������ ����Ϸ� �߽��ϴ�.");
	}

	Boundery = BounderyTexture->GetScale();
	
}



float4 PlayActor::ActorCameraPos()
{
	return GetPos() - GetLevel()->GetMainCamera()->GetPos();
}
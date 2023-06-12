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


//void PlayActor::Update(float _delta)
//{
//	float4 CheckPos = GetPos();
//
//	if (CheckPos.X < 0)
//	{
//		while (GetPos().X >=0 )
//		{
//			AddPos(float4::RIGHT);
//		}
//		
//	}
//	if (CheckPos.X > Boundery.X)
//	{
//		while (GetPos().X <=Boundery.X)
//		{
//			AddPos(float4::LEFT);
//		}
//	}
//	if(CheckPos.Y<0)
//	{
//		while (GetPos().Y >= 0)
//		{
//			AddPos(float4::DOWN);
//		}
//	}
//	if (CheckPos.Y > Boundery.Y)
//	{
//		while (GetPos().Y <= Boundery.Y)
//		{
//			AddPos(float4::UP);
//		}
//	}
//}

float4 PlayActor::ActorCameraPos()
{
	return GetPos() - GetLevel()->GetMainCamera()->GetPos();
}
#include "GameEngineRenderer.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include<GameEnginePlatform/GameEngineWindowTexture.h>
#include<GameEngineCore/GameEngineActor.h>
#include"GameEngineCamera.h"
#include "ResourcesManager.h"

GameEngineRenderer::GameEngineRenderer()
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

void GameEngineRenderer::SetTexture(const std::string& _Name)
{
	Texture = ResourcesManager::GetInst().FindTexture(_Name);
	if (nullptr == Texture)
	{
		MsgBoxAssert("�������� �ʴ� �ؽ��ĸ� �ҷ����� �õ��߽��ϴ�." + _Name);
	}

	SetCopyPos(float4::ZERO);
	SetCopyScale(Texture->GetScale());

	if (false == ScaleCheck)
	{
		SetRenderScaleToTexture();
	}

}
void GameEngineRenderer::SetRenderScaleToTexture()
{
	RenderScale = Texture->GetScale();
	ScaleCheck = false;
}

void GameEngineRenderer::Render(GameEngineCamera* _Camera)
{
	if (nullptr == Texture)
	{
		MsgBoxAssert("�̹����� ������ �ȵ� �������Դϴ�");
	}
	GameEngineWindowTexture* BackBuffer = GameEngineWindow::MainWindow.GetBackBuffer();

	BackBuffer->TransCopy(Texture, Master->GetPos() + RenderPos - _Camera->GetPos(), RenderScale, CopyPos,CopyScale);
}


bool GameEngineRenderer::IsDeath()
{
	return true == GameEngineObject::IsDeath() || Master->IsDeath();
}

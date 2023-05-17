#include "PlayLevel.h"
#include<GameEngineBase/GameEngineDebug.h>
#include<GameEnginePlatform/GameEngineWindow.h>
#include<GameEnginePlatform/GameEngineInput.h>
#include<GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>



#include"Player.h"
#include "BackGround.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start()
{

	BackGround* Back = CreateActor<BackGround>();
	Back->Init("StageTest.Bmp",3);

	LevelPlayer = CreateActor<Player>();
}

void PlayLevel::Update(float _Delta)
{

	if (true == GameEngineInput::IsDown('O'))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}

}

void PlayLevel::Render()
{
}

void PlayLevel::Release()
{
}


void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�");
	}

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	//LevelPlayer->SetPos(WinScale.Half());
	// 0 0
	// x y
	GetMainCamera()->SetPos(LevelPlayer->GetPos() - WinScale.Half());

}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}
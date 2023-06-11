#include "EggCorridor.h"
#include "ContentsEnum.h"

#include<GameEngineBase/GameEngineDebug.h>
#include<GameEnginePlatform/GameEngineWindow.h>
#include<GameEnginePlatform/GameEngineInput.h>
#include<GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include<GameEngineCore/ResourcesManager.h>
#include<GameEngineCore/GameEngineRenderer.h>



#include"Player.h"
#include "BackGround.h"
EggCorridor::EggCorridor()
{
}

EggCorridor::~EggCorridor()
{
}

void EggCorridor::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("EggCorridor_Ground.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resources\\Texture\\Map");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("EggCorridor_Ground.Bmp"));
	}



	BackGround* FrontPtr = CreateActor<BackGround>(RenderOrder::FrontGround);
	FrontPtr->Init("EggCorridor_Front.Bmp");
	
	
	

	MiddlePtr = CreateActor<BackGround>(RenderOrder::BackGround);
	MiddlePtr->Init("EggCorridor_Middle.Bmp", "EggCorridor_Ground.Bmp");

	LevelPlayer = CreateActor<Player>();
	LevelPlayer->SetGroundTexture("EggCorridor_Ground.Bmp");
	LevelPlayer->SetPos(float4{ 925 ,500 });
	
}

void EggCorridor::Update(float _Delta)
{

	if (true == GameEngineInput::IsDown('O'))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}
	if (true == GameEngineInput::IsDown('J'))
	{
		MiddlePtr->SwitchRender();
	}
}


void EggCorridor::Release()
{
}


void EggCorridor::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�");
	}


	LevelPlayer->SetGroundTexture("EggCorridor_Ground.Bmp");

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	//LevelPlayer->SetPos(WinScale.Half());
	// 0 0
	// x y

}

void EggCorridor::LevelEnd(GameEngineLevel* _NextLevel)
{

}
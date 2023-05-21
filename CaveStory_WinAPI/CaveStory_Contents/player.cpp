#include "Player.h"
#include"ContentsEnum.h"

#include <Windows.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include<GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <CaveStory_Contents/Bullet.h>

Player* Player::MainPlayer = nullptr;

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("MyChar.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("Resources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("MyChar.bmp"), 11, 2);



		//FolderPath.MoveChild("Resources\\Texture\\");

		//ResourcesManager::GetInst().CreateSpriteFolder("FolderPlayer", FolderPath.PlusFilePath("FolderPlayer"));

		//ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Test.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HPBar.bmp"));
	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);



		MainRenderer->CreateAnimation("Left_Idle", "MyChar.bmp", 0,0,0.2f, false);
		MainRenderer->CreateAnimation("Right_Idle", "MyChar.bmp", 11, 11,0.1f, false);

		MainRenderer->CreateAnimation("Left_Run", "MyChar.bmp", 0, 2, 0.2f, true);
		MainRenderer->CreateAnimation("Right_Run", "MyChar.bmp", 11, 13, 0.2f, true);


		MainRenderer->ChangeAnimation("Left_Idle");
		MainRenderer->SetScaleRatio(4.0f);
	}

	{
		GameEngineRenderer* Ptr = CreateRenderer("HPBar.bmp", RenderOrder::Play);
		Ptr->SetRenderPos({ 0, -100 });
		Ptr->SetRenderScale({ 200, 40 });
		Ptr->SetTexture("HPBar.bmp");
	}

	ChanageState(PlayerState::Idle);
	Dir = PlayerDir::Right;
}


void Player::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Idle:
		return IdleUpdate(_Delta);
	case PlayerState::Run:
		return RunUpdate(_Delta);
	default:
		break;
	}

}

void Player::ChanageState(PlayerState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Run:
			RunStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void Player::DirCheck()
{
	PlayerDir CheckDir = PlayerDir::Max;

	bool ChangeDir = false;

	if (true == GameEngineInput::IsDown('A'))
	{
		CheckDir = PlayerDir::Left;
	}
	if (true == GameEngineInput::IsDown('D'))
	{
		CheckDir = PlayerDir::Right;
	}

	if (true == GameEngineInput::IsPress('A') && true == GameEngineInput::IsUp('D') /*&& Dir == PlayerDir::Right*/)
	{
		CheckDir = PlayerDir::Left;
	}

	if (true == GameEngineInput::IsPress('D') && true == GameEngineInput::IsUp('A') /*&& Dir == PlayerDir::Left*/)
	{
		CheckDir = PlayerDir::Right;
	}


	if (CheckDir != PlayerDir::Max)
	{
		ChangeDir = true;
		Dir = CheckDir;
	}

	if (CheckDir != PlayerDir::Max && true == ChangeDir)
	{
		ChangeAnimationState(CurState);
	}

}

void Player::ChangeAnimationState(const std::string& _StateName)
{
	// "Idle"
	// _StateName

	std::string AnimationName;

	switch (Dir)
	{
	case PlayerDir::Right:
		AnimationName = "Right_";
		break;
	case PlayerDir::Left:
		AnimationName = "Left_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}

void Player::LevelStart()
{
	MainPlayer =this;
}

#include "GameEngineCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include<GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include "GameEngineLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>

std::string GameEngineCore::WindowTitle = "";
std::map<std::string,class GameEngineLevel*>GameEngineCore::AllLevel;
GameEngineLevel* GameEngineCore::CurLevel=nullptr;
GameEngineLevel* GameEngineCore::NextLevel = nullptr;
CoreProcess* GameEngineCore::Process = nullptr;

GameEngineCore::GameEngineCore()
{
}

GameEngineCore::~GameEngineCore()
{
}

void GameEngineCore::CoreStart(HINSTANCE _Inst)
{
	GameEngineWindow::MainWindow.Open(WindowTitle, _Inst);
	GameEngineInput::InputInit();

	Process->Start();
}

void GameEngineCore::CoreUpdate()
{
	if (nullptr != NextLevel)
	{

		if (nullptr != CurLevel)
		{
			CurLevel->LevelStart(NextLevel);
			CurLevel->ActorLevelEnd();
		}

		NextLevel->LevelStart(CurLevel);
		NextLevel->ActorLevelStart();

		CurLevel = NextLevel;
		NextLevel = nullptr;
		GameEngineTime::MainTimer.Reset();
	}

	GameEngineTime::MainTimer.Update();
	float Delta = GameEngineTime::MainTimer.GetDeltaTime();


	if (true == GameEngineWindow::IsFocus())
	{
		GameEngineInput::Update(Delta);
	}
	else
	{
		GameEngineInput::Reset();
	}

	CurLevel->Update(Delta);
	CurLevel->ActorUpdate(Delta);

	GameEngineWindow::MainWindow.ClearBackBuffer();
	CurLevel->ActorRender(Delta);
	CurLevel->Render();
	GameEngineWindow::MainWindow.DoubleBuffering();

	CurLevel->ActorRelease();
}

void GameEngineCore::CoreEnd() 
{
	Process->Release();

	if (nullptr != Process)
	{
		delete Process;
		Process = nullptr;
	}

	for (std::pair<std::string, GameEngineLevel*> _Pair : AllLevel)
	{
		if (nullptr != _Pair.second)
		{
			delete _Pair.second;
			_Pair.second = nullptr;
		}
	}

}

void GameEngineCore::LevelInit(GameEngineLevel* _Level)
{
	_Level->Start();
}

void GameEngineCore::EngineStart(const std::string& _Title, HINSTANCE _Inst, CoreProcess* _Ptr)
{
	GameEngineDebug::LeckCheck();

	Process = _Ptr;
	WindowTitle = _Title;
	GameEngineWindow::MessageLoop(_Inst, CoreStart, CoreUpdate, CoreEnd);
}
#include "GameEngineCamera.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineCamera::GameEngineCamera()
{
}

GameEngineCamera::~GameEngineCamera()
{
}

void GameEngineCamera::PushRenderer(GameEngineRenderer* _Renderer, int _Order)
{
	if (nullptr == _Renderer)
	{
		MsgBoxAssert("nullptr�� �������� �׷쿡 ���ϰ� �Ϸ��� �߽��ϴ�.");
	}

	Renderers[_Order].push_back(_Renderer);
}

void GameEngineCamera::Release()
{

	std::map<int, std::list<GameEngineRenderer*>>::iterator GroupStartlter = Renderers.begin();
	std::map<int, std::list<GameEngineRenderer*>>::iterator GroupEndlter = Renderers.end();

	for (; GroupStartlter != GroupEndlter; ++GroupStartlter)
	{
		std::list<GameEngineRenderer*> Group = GroupStartlter->second;

		std::list<GameEngineRenderer*>::iterator ActorStartlter = Group.begin();
		std::list<GameEngineRenderer*>::iterator ActorEndlter = Group.end();

		for (; ActorStartlter != ActorEndlter;)
		{
			GameEngineRenderer* Object = *ActorStartlter;

			if (false == Object->IsUpdate())
			{
				++ActorStartlter;
				continue;
			}
			if (nullptr == Object)
			{
				MsgBoxAssert("nullptr�� �������� ������ ����Ʈ�� �� �־����ϴ�.");
				continue;
			}
			ActorStartlter= Group.erase(ActorStartlter);
		}
	}
}


void GameEngineCamera::Render()
{
	std::map<int, std::list<GameEngineRenderer*>>::iterator GroupStartIter = Renderers.begin();
	std::map<int, std::list<GameEngineRenderer*>>::iterator GroupEndIter = Renderers.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<GameEngineRenderer*>& List = GroupStartIter->second;

		std::list<GameEngineRenderer*>::iterator RenderStartIter = List.begin();
		std::list<GameEngineRenderer*>::iterator RenderEndIter = List.end();


		for (; RenderStartIter != RenderEndIter; ++RenderStartIter)
		{
			GameEngineRenderer* Render = *RenderStartIter;

			if (false == Render->IsUpdate())
			{
				continue;
			}

			Render->Render(this);
		}
	}
}

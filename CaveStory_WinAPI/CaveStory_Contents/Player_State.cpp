#include "Player.h"
#include "HoverEffect.h"
#include"QuestionMark.h"
#include "CureMachine.h"
#include"TelePorter.h"
#include "Door.h"
#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>

#define SpeedLimit 300.0f
#define JumpTimeLimit 0.6f



void Player::IdleStart()
{
	if (true == GameEngineInput::IsFree(VK_UP))
	{
		Look = PlayerLook::Middle;
	}
	
	ChangeAnimationState("Idle");
	
}

void Player::RunStart()
{
	ChangeAnimationState("Run");
}


void Player::JumpStart()
{
	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));

		if (RGB(255, 255, 255) == Color)
		{
			return;
		}

	}

	ChangeAnimationState("Jump");

}
void Player::HoverStart()
{
	
}

void Player::SearchStart()
{
	if (false == CanSearch)
	{
		ChanageState(PlayerState::Idle);
		return;
	}
	ChangeAnimationState("Back");
}



void Player::IdleUpdate(float _Delta)
{
	if (float4::ZERO != MovePos)
	{

		MovePos = MovePos.LerpClimp(MovePos, float4::ZERO, 0.03f);

		AddPos(MovePos * _Delta);

		if (MovePos.Size() < float4{ 1.0f }.Size())
		{
			MovePos = float4::ZERO;
		}

	}

	///////////////Gravity
	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (RGB(255, 255, 255) == Color)
		{
			
			Gravity(_Delta);
		}
		
		else
		{
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			while (CheckColor != RGB(255, 255, 255))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
				AddPos(float4::UP);
			}


			GravityReset();
		}
	}


	if (true == GameEngineInput::IsDown(VK_LEFT)
		|| true == GameEngineInput::IsDown(VK_RIGHT)
		|| true == GameEngineInput::IsPress(VK_LEFT)
		|| true == GameEngineInput::IsPress(VK_RIGHT)
		)
	{
		DirCheck();
		ChanageState(PlayerState::Run);
		return;
	}

	if (true == GameEngineInput::IsDown('Z'))
	{
		DirCheck();
		ChanageState(PlayerState::Jump);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_DOWN))
	{
		ChanageState(PlayerState::Search);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_UP))
	{
		Look = PlayerLook::Up;
		ChangeAnimationState(CurState);

	}
	if (true == GameEngineInput::IsUp(VK_UP))
	{
		Look = PlayerLook::Middle;
		ChangeAnimationState(CurState);
	}

	// ������ �������� 
	//if (true)
	//{
	//	ChanageState(PlayerState::Idle);
	//}

}


void Player::RunUpdate(float _Delta)
{
	
	
	

	DirCheck();

	//�ӵ� ������ ���� ���ߺξ� ����
	if (0.0f <= GetGravityVector().Y)
	{
		float4 CheckPos = float4::DOWN;
		int CountCheck = 0;
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		while (RGB(255, 255, 255) != Color)
		{
			CheckPos += float4::DOWN;
			Color = GetGroundColor(RGB(255, 255, 255), CheckPos);
			++CountCheck;
		}

		if (3 > CountCheck)
		{
			SetPos(GetPos() + CheckPos);
		}

		CheckPos = UpCheck;
	}

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (RGB(255, 255, 255) == Color)
		{
			
			Gravity(_Delta);
		}
		
		else
		{
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			while (CheckColor != RGB(255,255, 255))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
				AddPos(float4::UP);
			}


			GravityReset();
		}

	}

	{
	//static float PlayerSpeed =0.0f;

	if (true == GameEngineInput::IsPress(VK_LEFT)&&Dir==PlayerDir::Left)
		{
			//PlayerSpeed +=_Delta*100;
		
			BodyCheckPos = LeftBodyCheck;
			UpCheck.X = LeftHeadCheck.X; 
			if (SpeedLimit < abs(MovePos.X))
				{

					MovePos = { -SpeedLimit ,  0.0f };

				}
			else
				{
					MovePos = MovePos.LerpClimp(MovePos, { -SpeedLimit ,  0.0f }, 0.04f) ;
				}
			

		}
	else if (true == GameEngineInput::IsPress(VK_RIGHT) && Dir == PlayerDir::Right)
		{
			//PlayerSpeed += _Delta*100;
		
		BodyCheckPos = RightBodyCheck;
		UpCheck.X = RightHeadCheck.X;
		if (SpeedLimit < abs(MovePos.X))
			{

 				MovePos = { SpeedLimit ,  0.0f };
			}
		else
			{
				MovePos = MovePos.LerpClimp(MovePos, {   SpeedLimit ,  0.0f }, 0.04f) ;
			}
		
		}
		else
			 {
		
				MovePos	=MovePos.LerpClimp( MovePos, float4::ZERO, 0.04f) ;
		
			 }

	

	}

	if (true == GameEngineInput::IsDown(VK_DOWN)&&float4::ZERO==GetGravityVector())
	{
		MovePos = float4::ZERO;
		ChanageState(PlayerState::Search);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_UP))
	{
		Look = PlayerLook::Up;
		ChangeAnimationState(CurState);
	}
	if (true == GameEngineInput::IsUp(VK_UP))
	{
		Look = PlayerLook::Middle;
		ChangeAnimationState(CurState);
	}
	if (true == GameEngineInput::IsDown(VK_DOWN)&&float4::ZERO != GetGravityVector())
	{
		Look = PlayerLook::Down;
		ChangeAnimationState(CurState);

	}
	if (true == GameEngineInput::IsUp(VK_DOWN))
	{
		Look = PlayerLook::Middle;
		ChangeAnimationState(CurState);
	}
	
	


	if (true == GameEngineInput::IsDown('Z'))
	{
			DirCheck();
			ChanageState(PlayerState::Jump);
			return;

	}

	


	if (MovePos.Size() < float4{1.0f}.Size())
	{
		DirCheck();
		ChanageState(PlayerState::Idle);
		return;
	}

	{
		
		unsigned int CeilingColor = GetGroundColor(RGB(255, 255, 255), UpCheck);
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), BodyCheckPos);
		if(CeilingColor== RGB(255, 255, 255))
		{
			if (Color == RGB(255, 255, 255))
			{
				AddPos(MovePos*_Delta);
				GetLevel()->GetMainCamera()->AddPos(MovePos);
			}
			
		}
		
	}
	DirCheck();

	
	{
		static float TimeCheck = 0.0f;
		
		if (0.2f <= TimeCheck)
		{


			PlayerSound = GameEngineSound::SoundPlay("PlayerWalk.Wav");
			TimeCheck = 0.0f;

		}
			
			
			
		TimeCheck += _Delta;
			
	}
	
	
	


}
	
	




void Player::JumpUpdate(float _Delta) 
{
	
	
	float4 JumpVector= float4::UP;
	JumpVector.Normalize();

	static float DeltaCheck= 0.0f;


	if (JumpTimeLimit > DeltaCheck)
	{
		if (true == GameEngineInput::IsPress('Z'))
			{

				AddPos(JumpVector * _Delta * 500.0f);
				DeltaCheck += _Delta;
				if (JumpTimeLimit <= DeltaCheck)
				{
					GravityReset();
				}
		
			}

		if (true == GameEngineInput::IsUp('Z'))
		{
			GravityReset();
			
			DeltaCheck = 10.0f;
		}


	}
	
	DirCheck();

	//static float PlayerSpeed = 0.0f;

	if (true == GameEngineInput::IsDown(VK_UP))
	{
		Look = PlayerLook::Up;
		ChangeAnimationState(CurState);

	}
	if (true == GameEngineInput::IsUp(VK_UP))
	{
		Look = PlayerLook::Middle;
		ChangeAnimationState(CurState);
	}
	if (true == GameEngineInput::IsDown(VK_DOWN))
	{
		Look = PlayerLook::Down;
		ChangeAnimationState(CurState);

	}
	if (true == GameEngineInput::IsUp(VK_DOWN))
	{
		Look = PlayerLook::Middle;
		ChangeAnimationState(CurState);
	}


	if (true == GameEngineInput::IsPress(VK_LEFT) && Dir == PlayerDir::Left)
	{
		//PlayerSpeed += _Delta;

		BodyCheckPos = LeftBodyCheck;
		UpCheck.X = LeftHeadCheck.X;
		if (SpeedLimit < abs(MovePos.X))
		{

			MovePos = { -SpeedLimit ,  0.0f };

		}
		else
		{
			MovePos = MovePos.LerpClimp(MovePos, { -SpeedLimit ,  0.0f }, 0.03f);
		}



	}else if (true == GameEngineInput::IsPress(VK_RIGHT) && Dir == PlayerDir::Right)
	{
		//PlayerSpeed += _Delta;

		BodyCheckPos = RightBodyCheck;
		UpCheck.X = RightHeadCheck.X;
		if (SpeedLimit < abs(MovePos.X))
		{

			MovePos = { SpeedLimit ,  0.0f };

		}
		else
		{
			MovePos = MovePos.LerpClimp(MovePos, { SpeedLimit ,  0.0f }, 0.03f);
		}


	}
	else
	{
		MovePos = MovePos.LerpClimp(MovePos, float4::ZERO, 0.03f);


	}
	

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (RGB(255, 255, 255) == Color)
		{
			Gravity(_Delta);

			if (true == GameEngineInput::IsDown('Z'))
			{
				if (true == CanHover)
				{
					DeltaCheck = 0.0f;
					GravityReset();
					ChanageState(PlayerState::Hover);
					return;
				}
			}

		}
		else if (RGB(0, 255, 0) == Color)
		{
			
			Gravity(_Delta);
		}
		else
		{
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			while (CheckColor != RGB(255, 255, 255))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
				AddPos(float4::UP);
			}

			DeltaCheck = 0.0f;
			ChanageState(PlayerState::Idle);
			return;
		}

	}

	{

			unsigned int CeilingColor = GetGroundColor(RGB(255, 255, 255), UpCheck);
			unsigned int Color = GetGroundColor(RGB(255, 255, 255), BodyCheckPos);

			if (CeilingColor != RGB(255, 255, 255))
			{
			
				while (CeilingColor != RGB(255, 255, 255))
				{
					CeilingColor = GetGroundColor(RGB(255, 255, 255), float4::DOWN);
					AddPos(float4::DOWN);

				}

				GravityReset();
				PlayerSound = GameEngineSound::SoundPlay("Playerbonkhead.Wav");
				DeltaCheck = 10.0f;

			}
	}



	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), BodyCheckPos);


		if (Color == RGB(255, 255, 255))
		{
			AddPos(MovePos*_Delta);
			GetLevel()->GetMainCamera()->AddPos(MovePos);

		}
	}


	
	
}

void Player::HoverUpdate(float _Delta)
{
	  static float HoverTime = 1.0f;
	  static float HoverRespawnTime = 0.0f;
	  
	
	

	

	if (true == GameEngineInput::IsPress('Z'))
	{
		if (0.0f < HoverTime)
		{
			
			AddGravityVector(float4::UP * _Delta * 2.8f);

			if (0.2f <= HoverRespawnTime)
			{

				HoverEffect* NewHoverEffect = GetLevel()->CreateActor<HoverEffect>(RenderOrder::BackPlay);
				NewHoverEffect->SetPos(GetPos());
				HoverRespawnTime = 0.0f;
			}



			HoverRespawnTime += _Delta;
			HoverTime -= _Delta;


		}


	}

	DirCheck();
	//static float PlayerSpeed = 0.0f;

	if (true == GameEngineInput::IsDown(VK_UP))
	{
		Look = PlayerLook::Up;
		ChangeAnimationState(CurState);

	}
	if (true == GameEngineInput::IsUp(VK_UP))
	{
		Look = PlayerLook::Middle;
		ChangeAnimationState(CurState);
	}
	if (true == GameEngineInput::IsDown(VK_DOWN))
	{
		Look = PlayerLook::Down;
		ChangeAnimationState(CurState);

	}
	if (true == GameEngineInput::IsUp(VK_DOWN))
	{
		Look = PlayerLook::Middle;
		ChangeAnimationState(CurState);
	}


	if (true == GameEngineInput::IsPress(VK_LEFT) && Dir == PlayerDir::Left)
	{
		//PlayerSpeed += _Delta*10;

		BodyCheckPos = LeftBodyCheck;
		UpCheck.X = LeftHeadCheck.X;
		MovePos = { -SpeedLimit * _Delta, 0.0f };


	}else
	if (true == GameEngineInput::IsPress(VK_RIGHT) && Dir == PlayerDir::Right)
	{
		//PlayerSpeed += _Delta*10;

		BodyCheckPos = RightBodyCheck;
		UpCheck.X = RightHeadCheck.X;
		MovePos = { SpeedLimit * _Delta, 0.0f };

	}
	else
	{
		MovePos = float4::ZERO;

	}


		{
			unsigned int Color = GetGroundColor(RGB(255, 255, 255));
			if (RGB(255, 255, 255) != Color)
			{
			


				HoverTime = 1.0f;
				ChanageState(PlayerState::Idle);
				return;
			}
			else
			{

				Gravity(_Delta);

			}
			

		}

		
	{
		unsigned int CeilingColor = GetGroundColor(RGB(255, 255, 255), UpCheck);

		if (CeilingColor != RGB(255, 255, 255))
		{
			while (CeilingColor != RGB(255, 255, 255))
			{
				CeilingColor = GetGroundColor(RGB(255, 255, 255), float4::DOWN);
				AddPos(float4::DOWN);
				HoverTime = 0.0f;

			}
			GravityReset();
			PlayerSound = GameEngineSound::SoundPlay("Playerbonkhead.Wav");


		}
	}

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), BodyCheckPos);
		

		if (Color == RGB(255, 255, 255))
		{
			AddPos(MovePos);
			GetLevel()->GetMainCamera()->AddPos(MovePos);

		}
	}



			
}

void Player::SearchUpdate(float _Delta)
{


	{
		
	
		std::vector<GameEngineCollision*> _Col;
		
		if (true == BodyCollision->Collision(CollisionOrder::CureMachine, _Col, CollisionType::Rect, CollisionType::Rect))
		{

			SetHp(MaxHp);
			GameEngineCollision* colli = _Col[0];
			CureMachine* colMachine = dynamic_cast<CureMachine*>(colli->GetActor());
			colMachine->GetSound();
			CanSearch = true;
			ChanageState(PlayerState::Idle);
			return;
		}


	}

	{
		std::vector<GameEngineCollision*> _Col;

		if (true == BodyCollision->Collision(CollisionOrder::Potal, _Col, CollisionType::Rect, CollisionType::Rect))
		{

		
			GameEngineCollision* colli = _Col[0];
			TelePorter* colMachine = dynamic_cast<TelePorter*>(colli->GetActor());
			colMachine->Teleport();
			CanSearch = true;
			ChanageState(PlayerState::Idle);
			return;
		}

	}

	{
		std::vector<GameEngineCollision*> _Col;

		if (true == BodyCollision->Collision(CollisionOrder::Door, _Col, CollisionType::Rect, CollisionType::Rect))
		{


			GameEngineCollision* colli = _Col[0];
			Door* colDoor = dynamic_cast<Door*>(colli->GetActor());
			colDoor->Open();
			CanSearch = true;
			ChanageState(PlayerState::Idle);
			return;
		}
	}



	if (true == CanSearch)
	{
	QuestionMark* NewQuestionMark = GetLevel()->CreateActor<QuestionMark>(RenderOrder::FrontPlay);
	
	NewQuestionMark->SetPos(GetPos());
	NewQuestionMark->AddPos({ 0,-40 });

	}
	
	
	if (true == GameEngineInput::IsDown(VK_LEFT)
		|| true == GameEngineInput::IsDown(VK_RIGHT)
		)
	{
		CanSearch = true;
		ChanageState(PlayerState::Idle);
		return;
	}

	if (true == GameEngineInput::IsDown('Z'))
	{
		CanSearch = true;
		ChanageState(PlayerState::Jump);
		return;
	}

	CanSearch = false;

}


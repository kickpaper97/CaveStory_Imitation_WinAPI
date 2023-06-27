#include "Monster.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include "Player.h"
#include"Bullet.h"

std::list<Monster*> Monster::AllMonster;


Monster::Monster()
{
	AllMonster.push_back(this);
}

Monster::~Monster()
{
}



void Monster::AllMonsterDeath()
{
	for (Monster* Monster : AllMonster)
	{
		Monster->Death();
	}

	AllMonster.clear();
}

void Monster::Update(float _Delta)
{
	// Player::MainPlayer = nullptr;
	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("������ �浹ü�� ���� ���� �ʾҽ��ϴ�.");
		return;
	}

	if (nullptr == Renderer)
	{
		MsgBoxAssert("������ �������� ���� ���� �ʾҽ��ϴ�.");
		return;
	}


	
	 if (0 >= Hp)
	 {
		 Death();
	 }


	std::vector<GameEngineCollision*> _Col;
	if (true == BodyCollision->Collision(CollisionOrder::Bullet, _Col, CollisionType::CirCle, CollisionType::Rect))
	{
		for (size_t i = 0; i <_Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			Bullet* HitBullet = dynamic_cast<Bullet*>(Collison->GetActor());

			 Hp-=HitBullet->GetDamage();
			 
			
		}
	}

}

void Monster::Start()
{
	
}


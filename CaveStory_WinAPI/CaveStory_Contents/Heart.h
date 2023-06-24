
#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Heart : public GameEngineActor
{
public:
	Heart();
	~Heart();

	Heart(const Heart& _Other) = delete;
	Heart(Heart&& _Other) noexcept = delete;
	Heart& operator=(const Heart& _Other) = delete;
	Heart& operator=(const Heart&& _Other) noexcept = delete;


protected:

	GameEngineSprite* Renderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;
private:

};


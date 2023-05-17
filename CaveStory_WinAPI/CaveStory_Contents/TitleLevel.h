
#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class TitleLevel :public GameEngineLevel
{
public:
	TitleLevel();
	~TitleLevel();

	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(const TitleLevel&& _Other) noexcept = delete;

	void Start();

protected:
	void Update(float _DeltaTime) override;

private:

};


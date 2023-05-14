
#pragma once
#include <Windows.h>

class GameEngineTime
{
public:
	static GameEngineTime MainTimer;

	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(const GameEngineTime&& _Other) noexcept = delete;

	float GetDeltaTime() 
	{
		return FloatDelta;
	}

	void Reset();
	void Update();

protected:

private:
	GameEngineTime();
	~GameEngineTime();

	LARGE_INTEGER Count = {0};
	LARGE_INTEGER Cur = {0};
	LARGE_INTEGER Prev = {0};
	__int64 Tick;
	double DoubleDelta;
	float FloatDelta;
};

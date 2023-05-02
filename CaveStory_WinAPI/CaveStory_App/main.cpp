#include <iostream>
#include<GameEngineCore/GameEngineCore.h>
#include<CaveStory_Contents/ContentsCore.h>


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{

    // CallBack ����̶�� �մϴ�.
    GameEngineCore::EngineStart<ContentsCore>("MyWindow", hInstance);
    return 0;

}
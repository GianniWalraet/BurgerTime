#include "MiniginPCH.h"

#define STEAMACHIEVEMENTS

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include <steam_api.h>

int main(int, char*[]) 
{
	dae::Minigin engine;
	engine.Run();
    return 0;
}
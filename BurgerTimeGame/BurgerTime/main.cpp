#include "pch.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "BurgerTime.h"

int main(int, char* [])
{
	BurgerTime game;
	game.Run();
	return 0;
}

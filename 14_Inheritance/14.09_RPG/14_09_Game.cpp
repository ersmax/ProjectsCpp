#include "14_09_Game.h"

namespace myNamespaceRPG
{
	Game::Game() : creatures(nullptr), numberCreatures(0)
	{ /* Body intentionally left empty */ }


	Game::Game(const CreaturePtr& creatures, int theSize) : creatures(creatures)
	{
		
	}
} // myNamespaceRPG
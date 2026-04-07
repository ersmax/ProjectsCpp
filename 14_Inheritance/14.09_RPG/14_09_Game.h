#ifndef GAME_14_09_H
#define GAME_14_09_H

#include "14_09_Game_Builder.h"

namespace myNamespaceRPG
{
	class Game
	{
	public:
		const Creature& operator [](int index) const;
	private:
		friend class GameBuilder;
		Game();
		Game(const CreaturePtr& theCreatures, int theSize);
		CreaturePtr creatures;
		int numberCreatures;
	};


} // myNamespaceRPG

#endif // GAME_14_09_H

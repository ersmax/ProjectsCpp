#ifndef GAME_14_09_H
#define GAME_14_09_H

#include "14_09_Game_Builder.h"

namespace myNamespaceRPG
{
	class Game
	{
	public:
		const Creature& operator [](int index) const;
		void playNextTurn();
	private:
		friend class GameBuilder;
		Game();
		Game(const CreaturePtr* theCreatures, int theSize);
		~Game();
		const CreaturePtr *creatures;
		// Dynamic arrays of pointers to a Creature object
		int numberCreatures;
		int turn;
	};


} // myNamespaceRPG

#endif // GAME_14_09_H

#ifndef GAME_14_09_H
#define GAME_14_09_H

#include "14_09_Creature.h"

namespace myNamespaceRPG
{
	class GameBuilder;
	// forward declaration

	typedef Creature *CreaturePtr;

	class Game
	{
	public:
		const Creature& operator [](int index) const;
		void playNextTurn();
		~Game();
	private:
		friend class GameBuilder;
		Game();
		Game(const CreaturePtr* theCreatures, int theSize);
		const CreaturePtr *creatures;
		// Dynamic arrays of pointers to a Creature object
		int numberCreatures;
		int turn;
	};


} // myNamespaceRPG

#endif // GAME_14_09_H

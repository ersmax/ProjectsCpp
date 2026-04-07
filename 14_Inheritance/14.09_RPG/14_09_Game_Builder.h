#ifndef GAME_BUILDER_14_09_H
#define GAME_BUILDER_14_09_H

#include "14_09_Creature.h"
#include "14_09_Game.h"


namespace myNamespaceRPG
{
	typedef Creature *CreaturePtr;

	class GameBuilder
	{
	public:
		GameBuilder();
		//   Postcondition: Initialize the dynamic array to a set of 0 creatures
		GameBuilder(const GameBuilder& anotherGame);
		GameBuilder& operator =(const GameBuilder& anotherGame);
		~GameBuilder();
		const Creature& operator [](int index) const;
		void showCreatures() const;
		void addCreature(const CreaturePtr& newCreature);
		void deleteCreature(int index);
		const Game build();
		//   Postcondition: move creatures into the immutable Game
	private:
		CreaturePtr *creatures;
		// Dynamic arrays of pointers to a Creature object
		int numberCreatures;
	};

} // myNamespaceRPG


#endif // GAME_BUILDER_14_09_H

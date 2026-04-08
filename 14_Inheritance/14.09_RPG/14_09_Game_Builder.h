#ifndef GAME_BUILDER_14_09_H
#define GAME_BUILDER_14_09_H

#include "14_09_Creature.h"


namespace myNamespaceRPG
{
	class Game;
	// forward declaration

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
		//   Postcondition: Output the list of creatures in the builder with their index
		void addCreature();
		//   Postcondition: Ask the user to choose a creature type and enter its stats, 
		// then add it to the builder
		void deleteCreature();
		//   Postcondition: Ask the user to enter the index of the creature to delete, then
		// delete the creature from the builder
		const Game build();
		//   Postcondition: move creatures into the immutable Game
	private:
		void addCreatureHelper(const CreaturePtr& newCreature);
		//   Postcondition: Add the new creature to the builder. 
		// The builder takes ownership of the creature
		void deleteCreatureHelper(int index);
		//   Precondition: index is within bounds (greater than or equal 0 and less than 
		// number of creatures)
		//   Postcondition: Delete the creature at the specified index from the builder
		// The builder no longer owns the creature at that index.
		CreaturePtr *creatures;
		// Dynamic arrays of pointers to a Creature object
		int numberCreatures;
	};

} // myNamespaceRPG


#endif // GAME_BUILDER_14_09_H

#ifndef ORGANISM_15_03_H
#define ORGANISM_15_03_H

#include <random>

namespace myGame
{
	// Turns for an ant to reproduce and for a Doodlebug to starve without eating
	constexpr int LIFE_CYCLE = 3;	

	class World;

	struct Position
	{
		int x;
		int y;
	};

	class Organism
	{
	public:
		Organism();
		Organism(const Organism& anotherOrganism) = default;
		Organism& operator=(const Organism& anotherOrganism) = default;
		virtual ~Organism() = default;
		virtual void move(World& theWorld) = 0;
		//   Postcondition: allows the Ant/Doodlebug to move according to the rules of the game,
		// and updates the position of the Ant/Doodlebug in the world.
		virtual char getCreature() const = 0;
		//   Postcondition: returns the character representing the Ant/Doodlebug
		void setBreedTime(int theTime);
		//   Postcondition: sets the breedTime of the Ant/Doodlebug to theTime
		void decreaseBreedTime();
		//   Postcondition: decreases the breedTime of the Ant/Doodlebug by 1
		virtual void resetBreedTime() = 0;
		//   Postcondition: resets the breedTime of the Ant/Doodlebug to the initial value
		int getBreedTime() const;
		void setPosition(const Position& thePosition);
		//   Postcondition: sets the position of the Ant/Doodlebug to thePosition
		void play();
		//   Postcondition: sets the played flag to true, 
		// indicating that the Ant/Doodlebug has played in the current time step
		void initializePlay();
		//   Postcondition: sets the played flag to false, 
		// indicating that the Ant/Doodlebug has not played in the current time step
		bool hasPlayed() const;
		//   Postcondition: returns whether the Ant/Doodlebug has played in the current time step
		const Position& chooseRandomPosition(const std::vector<Position>& thePositions) const;
		//   Postcondition: returns a random position from thePositions vector, 
		// which is a vector of possible positions for the Ant/Doodlebug to move or breed
		const Position& getPosition() const;
		//   Postcondition: returns the current position of the Ant/Doodlebug
	private:
		Position position;
		mutable std::mt19937 rng;	
		bool played;
		int breedTime;
		//   Postcondition: the number of turns left before the Ant/Doodlebug can reproduce.
		// For an Ant, the initial breedTime is 3, and for a Doodlebug, the initial breedTime is 8.
	};

} // myGame

#endif // ORGANISM_15_03_H

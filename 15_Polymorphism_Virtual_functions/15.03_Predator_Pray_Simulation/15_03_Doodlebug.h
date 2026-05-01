#ifndef DOODLEBUG_15_03_H
#define DOODLEBUG_15_03_H

#include "15_03_Organism.h"

namespace myGame
{
	// turns for a doodlebug to reproduce
	constexpr int REPRODUCTION_TIME = 8;

	class Doodlebug : public Organism
	{
	public:
		Doodlebug();
		virtual void move(World& theWorld) override final;
		virtual char getCreature() const override final;
		virtual void resetBreedTime() override final;
		void resetTurnsStarvation();
		void increaseStarvation();
		int getStarvation() const;
	private:
		char creature = 'X';
		int turnsToStarvation;
	};

} // myGame


#endif // DOODLEBUG_15_03_H

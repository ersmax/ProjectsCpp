#ifndef ANT_15_03_H
#define ANT_15_03_H

#include "15_03_Organism.h"

namespace myGame
{
	class Ant : public Organism
	{
	public:
		Ant();
		virtual void move() override final;
		virtual char getCreature() const override final;
	private:
		char creature = 'O';
	};

} // myGame


#endif // ANT_15_03_H

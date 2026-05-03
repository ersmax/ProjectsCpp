#ifndef BALRGOG_15_04_H
#define BALRGOG_15_04_H

#include "15_04_Demon.h"

namespace myRPG
{
	class Balrog : public Demon
	{
	public:
		Balrog();
		Balrog(int theStrength, int theHitpoints);
		virtual int getDamage() override final;
		virtual const std::string& getSpecies() const override final;
	private:
		std::string species = "Balrog";
	};
} // myRPG

#endif // BALRGOG_15_04_H

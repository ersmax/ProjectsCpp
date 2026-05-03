#ifndef CYBERDEMON_15_04_H
#define CYBERDEMON_15_04_H

#include "15_04_Demon.h"

namespace myRPG
{
	class Cyberdemon : public Demon
	{
	public:
		Cyberdemon();
		Cyberdemon(int theStrength, int theHitpoints);
		virtual const std::string& getSpecies() const override final;
	private:
		std::string species = "Cyberdemon";
	};

} // myRPG

#endif // CYBERDEMON_15_04_H

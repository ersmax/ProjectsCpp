#ifndef ORGANISM_15_03_H
#define ORGANISM_15_03_H

namespace myGame
{
	struct Position
	{
		int x;
		int y;
	};

	class Organism
	{
	public:
		Organism(const Position& thePosition, char theSymbol);
		virtual ~Organism() = default;
		void setPosition(const Position& thePosition);
		const Position& getPosition() const;
		char getSymbol() const;
	private:
		Position position;
		char symbol;
	};

} // myGame

#endif // ORGANISM_15_03_H

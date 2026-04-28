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
		Organism();
		virtual ~Organism() = default;
		virtual void move() = 0;
		virtual char getCreature() const = 0;
		void setPosition(const Position& thePosition);
		const Position& getPosition() const;
	private:
		Position position;
	};

} // myGame

#endif // ORGANISM_15_03_H

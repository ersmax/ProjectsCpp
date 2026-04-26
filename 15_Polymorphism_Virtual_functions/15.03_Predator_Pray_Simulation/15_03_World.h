#ifndef WORLD_15_03_H
#define WORLD_15_03_H

#include <vector>

namespace myGame
{
	constexpr int N_ROWS = 20;
	constexpr int N_COLS = 20;
	constexpr int INITIAL_ANTS = 100;
	constexpr int INITIAL_DOODLEBUGS = 5;
	constexpr char ANT = '0';
	constexpr char DOODLEBUG = 'X';
	constexpr char EMPTY = ' ';
	
	struct Position
	{
		int x;
		int y;
	};

	class World
	{
	public:
		World();
		void output() const;
	private:
		//const Position& returnPosition() const;
		char board[N_ROWS][N_COLS];
		int nAnts;
		int nDoodlebug;
		void initialize();
		void placeRandom(char creature, int numCreatures);
	};

} // myGame

#endif // WORLD_15_03_H

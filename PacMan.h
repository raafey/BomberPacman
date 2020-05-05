#ifndef PACMAN_H_
#define PACMAN_H_

#include "Point.h"
#include "Bomb.h"

class PacMan
{
	private :

		Point pos;			// position of pacman
		int count;			// counts lives lost
		int score;			// score of pacman
		Bomb bomb;

	public :

		PacMan();
		void MoveX(int);
		void MoveY(int);
		void PlantBomb(int, int);
		Bomb& getBomb();
		~PacMan();

		// getters and setters

		int getCount() const;
		void setCount(int count);
		Point getPos();
		void setPos(Point pos);
		int getScore() const;
		void setScore(int score);
};

#endif

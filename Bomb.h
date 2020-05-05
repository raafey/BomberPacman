#ifndef BOMB_H_
#define BOMB_H_

#include "Point.h"

class Bomb
{
	private :

		Point position;
		int timer;

	public :

		Bomb();
		void SetBomb(int, int);
		void setBombTimer(int);
		int getBombTimer() const;
		Point getBombPosition() const;
		~Bomb();
};

#endif

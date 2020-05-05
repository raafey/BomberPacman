#include "Bomb.h"
#include "Point.h"

Bomb :: Bomb()
{
	position.setX(0);
	position.setY(0);
	timer = 0;
}

void Bomb :: SetBomb(int x, int y)
{
	position.setX(x);
	position.setY(y);
}

void Bomb :: setBombTimer(int t)
{
	timer = t;
}

int Bomb :: getBombTimer() const
{
	return timer;
}

Point Bomb :: getBombPosition() const
{
	return position;
}

Bomb :: ~Bomb() {}

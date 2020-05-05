#include "PacMan.h"
#include "Point.h"
#include "Bomb.h"
#include <iostream>

using namespace std;

PacMan :: PacMan()
{
	pos.setX(80);
	pos.setY(90);
	count = 3;
	score = 0;
	bomb.setBombTimer(2);
}

void PacMan :: PlantBomb(int x, int y)
{
	bomb.SetBomb(x,y);
}

Bomb& PacMan :: getBomb()
{
	return bomb;
}

void PacMan :: MoveX(int x)
{
	pos.setX(x);
}

void PacMan :: MoveY(int y)
{
	pos.setY(y);
}

int PacMan :: getCount() const
{
	return count;
}

void PacMan :: setCount(int count)
{
	this->count = count;
}

Point PacMan :: getPos()
{
	return pos;
}

void PacMan :: setPos(Point pos)
{
	this->pos = pos;
}

int PacMan :: getScore() const
{
	return score;
}

void PacMan::setScore(int score)
{
	this->score = score;
}

PacMan :: ~PacMan() {}

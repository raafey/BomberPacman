#include "Ghost.h"
#include "Point.h"

Ghost :: Ghost()
{
	ghost_pos.setX(0);
	ghost_pos.setY(0);
	lifeStatus = true;
	state = false;
}

Ghost :: Ghost(int x, int y)
{
	ghost_pos.setX(x);
	ghost_pos.setY(y);
	spawn.setX(x);
	spawn.setY(y);
	lifeStatus = true;
	state = false;
}

void Ghost :: MoveGhost(int x, int y)
{
	ghost_pos.setX(x);
	ghost_pos.setY(y);
}

void Ghost :: MoveGhostX(int x)
{
	ghost_pos.setX(x);
}

void Ghost :: MoveGhostY(int y)
{
	ghost_pos.setY(y);
}

bool Ghost :: getLifeStatus() const
{
	return lifeStatus;
}

void Ghost:: setLifeStatus(bool l)
{
	lifeStatus = l;
}

void Ghost :: setState(bool flag)
{
	state = flag;
}

bool Ghost :: getState() const
{
	return state;
}

Point& Ghost :: getSpawnPoint()
{
	return spawn;
}

Point& Ghost :: getGhostPos()
{
	return ghost_pos;
}

Ghost :: ~Ghost() {}

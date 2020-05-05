#include "Timer.h"

Tick :: Tick()
{
	seconds = 180;
}

void Tick:: setTimer(int seconds)
{
	this->seconds = seconds;
}

int Tick :: getSeconds()
{
	return seconds;
}

Tick :: ~Tick() {}

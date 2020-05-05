#ifndef GHOST_H_
#define GHOST_H_

#include "Point.h"

class Ghost
{
	private :

		Point ghost_pos;
		bool lifeStatus;
		bool state;
		Point spawn;

	public :

		Ghost();
		Ghost(int, int);
		void MoveGhost(int, int);
		void MoveGhostX(int);
		void MoveGhostY(int);
		bool getLifeStatus() const;
		void setLifeStatus(bool l);
		void setState(bool flag);
		bool getState() const;
		void setStateTime(int);
		int getStateTime();
		Point& getGhostPos();
		Point& getSpawnPoint();
		~Ghost();

};

#endif

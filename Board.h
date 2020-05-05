/*
 * Board.h
 *
 *  Created on: May 2, 2014
 *      Author: Sibt ul Hussain
 */
#ifndef _BOARD_H_
#define _BOARD_H_

#include <GL/glut.h>
#include <iostream>
#include "util.h"

#include "PacMan.h"
#include "Timer.h"
#include "Ghost.h"

//#define WITH_TEXTURES

using namespace std;
class Board
{
	private:

		int xcellsize, ycellsize;
		int width, height;
		ColorNames pcolor, bcolor, gcolor;
		int bricks_destroyed;
		PacMan pacman;
		Tick countDown;
		int stateTime;
		Ghost *Inky;
		Ghost *Pinky;
		Ghost *Clyde;
		Ghost *Blinky;
		int ghosts_killed;

	public:

		int nPpressed;
		int direction;
		static const int BOARD_X;
		static const int BOARD_Y;

		Board(int xsize = 8, int ysize = 8);
		~Board(void);
		void InitalizeBoard(int, int);
		void Draw();					//draw the board

		void DisplayArrayOrder();
		void Eat();
		bool checkPath(int x, int y);
		int getBoardIdx(int x, int y);
		void Detonate();
		bool checkPacmanSafety();
		void RandomMovement(Ghost *G);
		void DrawFireTrail();
		void EatPacman(Ghost *G);
		void checkGhostSafety(Ghost *G);
		int getGhostCount();
		void setGhostCount(int);
		void triggerFrightenedState();
		void EatGhost(Ghost *G);

		void GetInitTextPosition(int &x, int &y);
		void GetInitPinkyPosition(int &x, int &y);

		static int GetBoardX()
		{
			return BOARD_X;
		}
		static int GetBoardY() {
			return BOARD_Y;
		}
		int GetMidX()
		{
			return BOARD_X * xcellsize / 2.0;
		}
		int GetMidY()
		{
			return BOARD_Y * ycellsize / 2.0;
		}
		int GetCellSize()
		{
			return xcellsize;
		}
		void GetInitBombermanPosition(int &x, int &y)
		{
			x = xcellsize + xcellsize / 2;
			y = ycellsize + ycellsize / 2;
		}
		PacMan& getPacman()
		{
			return pacman;
		}
		Tick& getCountDown()
		{
			return countDown;
		}
		int getBricksDestroyed()
		{
			return bricks_destroyed;
		}
		Ghost* getPinky() { return Pinky; }
		Ghost* getInky()  { return Inky; }
		Ghost* getBlinky(){ return Blinky; }
		Ghost* getClyde() { return Clyde; }
		void setstateTime(int t) {stateTime = t;}
		int getstateTime() {return stateTime;}
};

#ifdef WITH_TEXTURES
void RegisterTextures();
#endif

#endif

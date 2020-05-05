/*
 * Board.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Sibt ul Hussain
 */

#include "Board.h"
#include "Ghost.h"
#include "Timer.h"
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <iostream>
using namespace std;

const int Board :: BOARD_X = 17;
const int Board :: BOARD_Y = 14;

//here's Bomberman's crazy board

// Note that all these enum constants from NILL onwards
// have been given numbers in increasing order
// e.g. NILL = 0, and so on
// and these numbers are representint &yed in the board array...
enum BoardParts
{
	NILL, S_BRICK, G_BRICK, R_BRICK
};

// defining some utility functions...

static int board_array[Board::BOARD_Y][Board::BOARD_X] = { { 0 } };

#ifdef WITH_TEXTURES
const int nbricks = 3;

GLuint texture[nbricks];
GLuint tid[nbricks];
string tnames[] = {"solid-.png", "brick.png", "brick-green.png"};
GLuint mtid[nbricks];
int cwidth = 60, cheight = 60; // 60x60 pixels bricks...

void RegisterTextures()
/*Function is used to load the textures from the
 * files and display*/
{
	// allocate a texture name
	glGenTextures(nbricks, tid);

	vector<unsigned char> data;
	//ofstream ofile("image-data.bin", ios::binary | ios::out);
	// now load each bricks data...

	for (int i = 0; i < nbricks; ++i) {

		// Read current brick

		ReadImage(tnames[i], data);
		if (i == 0) {
			int length = data.size();
			//ofile.write((char*) &length, sizeof(int));
		}
		//ofile.write((char*) &data[0], sizeof(char) * data.size());

		cout << " Texture Id=" << tid[i] << endl;
		mtid[i] = tid[i];
		// select our current texture
		glBindTexture(GL_TEXTURE_2D, tid[i]);

		// select modulate to mix texture with color for shading
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		// when texture area is small, bilinear filter the closest MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_LINEAR_MIPMAP_NEAREST);
		// when texture area is large, bilinear filter the first MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// if wrap is true, the texture wraps over at the edges (repeat)
		//       ... false, the texture ends at the edges (clamp)
		bool wrap = true;
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
				wrap ? GL_REPEAT : GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
				wrap ? GL_REPEAT : GL_CLAMP);

		// build our texture MIP maps
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, cwidth, cheight, GL_RGB,
				GL_UNSIGNED_BYTE, &data[0]);
	}
	//ofile.close();

}
void Drawbrick(const BoardParts &cname, float fx, float fy, float fwidth,
		float fheight)
/*Draws a specfic brick at given position coordinate
 * sx = position of x-axis from left-bottom
 * sy = position of y-axis from left-bottom
 * cwidth= width of displayed brick in pixels
 * cheight= height of displayed bricki pixels.
 * */
{

	glPushMatrix();
	glEnable (GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mtid[cname - 1]);
//	glTranslatef(0, 0, 0);
//	glRotatef(-M_PI / 2, 0, 0, 1);
	glBegin (GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2d(fx, fy);
	glTexCoord2d(1.0, 0.0);
	glVertex2d(fx + fwidth, fy);
	glTexCoord2d(1.0, 1.0);
	glVertex2d(fx + fwidth, fy + fheight);
	glTexCoord2d(0.0, 1.0);
	glVertex2d(fx, fy + fheight);
	glEnd();

	glColor4f(1, 1, 1, 1);

//	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//glutSwapBuffers();
}
#endif

// Destructor

Board :: ~Board(void) {}

void Board :: InitalizeBoard(int w, int h)
{
	width = w;
	height = h;
	for (int i = 0; i < BOARD_Y - 1; ++i)
	{
		for (int j = 0; j < BOARD_X; ++j)
		{
			if (i == 0 || i == BOARD_Y - 2 || j == 0 || j == BOARD_X - 1)
				board_array[i][j] = S_BRICK;
			else if (i % 2 == 0 && j % 2 == 0)
				board_array[i][j] = S_BRICK;
			else
				board_array[i][j] =
						(GetRandInRange(0, 10)) < 8 ? NILL :
						(GetRandInRange(0, 10)) < 8 ? G_BRICK : R_BRICK;
		}
	}

}

void Board :: EatGhost(Ghost *G)
{
	if (G->getGhostPos().getX() / 60 == pacman.getPos().getX() / 60 and G->getGhostPos().getY() / 60 == pacman.getPos().getY() / 60 and G->getState() == true and G->getLifeStatus() == true)
	{
		pacman.setScore(pacman.getScore() + 200);
		G->setLifeStatus(false);
		ghosts_killed += 1;
	}
}

void Board :: triggerFrightenedState()
{
	if ((pacman.getPos().getX() / 60 == 1 and pacman.getPos().getY() / 60 == 420 / 60) or
		(pacman.getPos().getX() / 60 == 900/60 and pacman.getPos().getY() / 60 == 1) or
		(pacman.getPos().getX() / 60 == 900/60 and pacman.getPos().getY() / 60 == 660 / 60) or
		(pacman.getPos().getX() / 60 == 1 and pacman.getPos().getY() / 60 == 660 / 60))
	{
			if (Blinky->getLifeStatus() == true)
				Blinky->setState(true);
			if (Inky->getLifeStatus() == true)
				Inky->setState(true);
			if (Clyde->getLifeStatus() == true)
				Clyde->setState(true);
			if (Pinky->getLifeStatus() == true)
				Pinky->setState(true);
	}
}

void Board :: DrawFireTrail()
{
	int x = pacman.getBomb().getBombPosition().getX();
	int y =	pacman.getBomb().getBombPosition().getY();

	DrawLine( x, y, x + 85, y, 90, colors[CRIMSON]);
	DrawLine( x, y, x - 85, y, 90, colors[CRIMSON]);
	DrawLine( x, y, x, y - 85, 90, colors[CRIMSON]);
	DrawLine( x, y, x, y + 85, 90, colors[CRIMSON]);
}

void Board :: DisplayArrayOrder()
{
	char array[17][14];
	for (int i = 0; i < BOARD_Y - 1; ++i)
	{
		for (int j = 0; j < BOARD_X - 1; ++j)
		{
			if (board_array[i][j] == NILL)
			{
				array[i][j] = '.';
			}
			else if (board_array[i][j] == S_BRICK)
			{
				array[i][j] = 'S';
			}
			else if (board_array[i][j] == G_BRICK)
			{
				array[i][j] = 'G';
			}
			else if (board_array[i][j] == R_BRICK)
			{
				array[i][j] = 'R';
			}
		}
	}

	for (int i = 0; i < BOARD_Y - 1; ++i)
	{
		for (int j = 0; j < BOARD_X; ++j)
		{
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Board :: Eat()
{
	if (Blinky->getLifeStatus() == true)
		EatPacman(Blinky);
	if (Clyde->getLifeStatus() == true and bricks_destroyed >= 19)
		EatPacman(Clyde);
	if (Inky->getLifeStatus() == true and bricks_destroyed >= 8)
		EatPacman(Inky);
	if (Pinky->getLifeStatus() == true)
		EatPacman(Pinky);

	int x = pacman.getPos().getX() / 60;
	int y = 12 - pacman.getPos().getY() / 60;

	if (board_array[y][x] == NILL)
	{
		board_array[y][x] = BLACK;
		triggerFrightenedState();
		pacman.setScore(pacman.getScore() + 100);
	}

	EatGhost(Blinky);
	if (bricks_destroyed >= 19)
		EatGhost(Clyde);
	if (bricks_destroyed >= 8)
		EatGhost(Inky);
	EatGhost(Pinky);
}

void Board :: checkGhostSafety(Ghost *G)
{
	if ((pacman.getBomb().getBombPosition().getX()-20 == G->getGhostPos().getX() and pacman.getBomb().getBombPosition().getY()-30 == G->getGhostPos().getY())
		or (pacman.getBomb().getBombPosition().getX()-20 == G->getGhostPos().getX() + 60 and pacman.getBomb().getBombPosition().getY()-30 == G->getGhostPos().getY())
		or (pacman.getBomb().getBombPosition().getX()-20 == G->getGhostPos().getX() - 60 and pacman.getBomb().getBombPosition().getY()-30 == G->getGhostPos().getY())
		or (pacman.getBomb().getBombPosition().getX()-20 == G->getGhostPos().getX() and pacman.getBomb().getBombPosition().getY()-30 == G->getGhostPos().getY() - 60)
		or (pacman.getBomb().getBombPosition().getX()-20 == G->getGhostPos().getX() and pacman.getBomb().getBombPosition().getY()-30 == G->getGhostPos().getY() + 60))
	{
		G->setLifeStatus(false);
		pacman.setScore(pacman.getScore() + 100);
		ghosts_killed += 1;
	}
}

bool Board :: checkPacmanSafety()
{
	if ((pacman.getBomb().getBombPosition().getX() == pacman.getPos().getX() and pacman.getBomb().getBombPosition().getY() == pacman.getPos().getY())
		or (pacman.getBomb().getBombPosition().getX() == pacman.getPos().getX() + 60 and pacman.getBomb().getBombPosition().getY() == pacman.getPos().getY())
		or (pacman.getBomb().getBombPosition().getX() == pacman.getPos().getX() - 60 and pacman.getBomb().getBombPosition().getY() == pacman.getPos().getY())
		or (pacman.getBomb().getBombPosition().getX() == pacman.getPos().getX() and pacman.getBomb().getBombPosition().getY() == pacman.getPos().getY() - 60)
		or (pacman.getBomb().getBombPosition().getX() == pacman.getPos().getX() and pacman.getBomb().getBombPosition().getY() == pacman.getPos().getY() + 60))
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Board :: Detonate()
{
	if (pacman.getBomb().getBombTimer() == 0)
	{
		if (board_array[(12 - (pacman.getBomb().getBombPosition().getY()) / 60) - 1][((pacman.getBomb().getBombPosition().getX()) / 60)] == G_BRICK)
		{
			board_array[(12 - (pacman.getBomb().getBombPosition().getY()) / 60) - 1][((pacman.getBomb().getBombPosition().getX()) / 60)] = BLACK;
			pacman.setScore(pacman.getScore() + 50);
			bricks_destroyed++;
		}
		if (board_array[(12 - (pacman.getBomb().getBombPosition().getY()) / 60) - 1][((pacman.getBomb().getBombPosition().getX()) / 60)] == R_BRICK and countDown.getSeconds() <= 130)
		{
			pacman.setScore(pacman.getScore() + 200);
			board_array[(12 - (pacman.getBomb().getBombPosition().getY()) / 60) - 1][((pacman.getBomb().getBombPosition().getX()) / 60)] = BLACK;
			bricks_destroyed++;
		}

		if (board_array[(12 - (pacman.getBomb().getBombPosition().getY()) / 60) + 1][((pacman.getBomb().getBombPosition().getX()) / 60)] == G_BRICK)
		{
			board_array[(12 - (pacman.getBomb().getBombPosition().getY()) / 60) + 1][((pacman.getBomb().getBombPosition().getX()) / 60)] = BLACK;
			pacman.setScore(pacman.getScore() + 50);
			bricks_destroyed++;
		}
		if (board_array[(12 - (pacman.getBomb().getBombPosition().getY()) / 60) + 1][((pacman.getBomb().getBombPosition().getX()) / 60)] == R_BRICK and countDown.getSeconds() <= 130)
		{
			board_array[(12 - (pacman.getBomb().getBombPosition().getY()) / 60) + 1][((pacman.getBomb().getBombPosition().getX()) / 60)] = BLACK;
			pacman.setScore(pacman.getScore() + 250);
			board_array[(12 - (pacman.getBomb().getBombPosition().getY()) / 60) + 1][((pacman.getBomb().getBombPosition().getX()) / 60) - 1] = BLACK;
			bricks_destroyed++;
		}

		if (board_array[(12 - (pacman.getBomb().getBombPosition().getY()) / 60)][((pacman.getBomb().getBombPosition().getX()) / 60) + 1] == G_BRICK)
		{
			board_array[(12 - (pacman.getBomb().getBombPosition().getY()) / 60)][((pacman.getBomb().getBombPosition().getX()) / 60) + 1] = BLACK;
			pacman.setScore(pacman.getScore() + 50);
			bricks_destroyed++;
		}
		if (board_array[(12 - (pacman.getBomb().getBombPosition().getY()) / 60)][((pacman.getBomb().getBombPosition().getX()) / 60) + 1] == R_BRICK and countDown.getSeconds() <= 130)
		{
			board_array[(12 - (pacman.getBomb().getBombPosition().getY()) / 60)][((pacman.getBomb().getBombPosition().getX()) / 60) + 1] = BLACK;
			pacman.setScore(pacman.getScore() + 200);
			bricks_destroyed++;
		}

		if (board_array[(12 - (pacman.getBomb().getBombPosition().getY()) / 60)][((pacman.getBomb().getBombPosition().getX()) / 60) - 1] == G_BRICK)
		{
			board_array[(12 - (pacman.getBomb().getBombPosition().getY()) / 60)][((pacman.getBomb().getBombPosition().getX()) / 60) - 1] = BLACK;
			pacman.setScore(pacman.getScore() + 50);
			bricks_destroyed++;
		}
		if (board_array[(12 - (pacman.getBomb().getBombPosition().getY()) / 60)][((pacman.getBomb().getBombPosition().getX()) / 60) - 1] == R_BRICK and countDown.getSeconds() <= 130)
		{
			board_array[(12 - (pacman.getBomb().getBombPosition().getY()) / 60)][((pacman.getBomb().getBombPosition().getX()) / 60) - 1] = BLACK;
			pacman.setScore(pacman.getScore() + 250);
			board_array[(12 - (pacman.getBomb().getBombPosition().getY()) / 60)][((pacman.getBomb().getBombPosition().getX()) / 60) - 2] = BLACK;
			bricks_destroyed++;
		}
	}
}

//Constructor

Board :: Board(int xsize, int ysize)
{
	xcellsize = xsize;
	ycellsize = ysize;
	bricks_destroyed = 0;
	direction = 0;
	nPpressed = 0;
	ghosts_killed = 0;
	stateTime = 10;
	pcolor = CHOCOLATE;
	bcolor = ORANGE_RED;
	gcolor = PINK;

	Blinky = new Ghost(540, 120);
	Pinky = new Ghost(660 , 300);
	Inky = new Ghost(540 , 360);
	Clyde = new Ghost(420, 540);
}

int Board :: getGhostCount()
{
	return ghosts_killed;
}

void Board :: setGhostCount(int c)
{
	ghosts_killed = c;
}

void Board :: EatPacman(Ghost *G)
{
	if (G->getGhostPos().getX() / 60 == pacman.getPos().getX() / 60 and G->getGhostPos().getY() / 60 == pacman.getPos().getY() / 60 and G->getState() == false)
	{
		pacman.setCount((pacman.getCount() - 1));
		pacman.MoveX(80);
		pacman.MoveY(90);
	}
}

bool Board :: checkPath(int x, int y)
{
	if (board_array[x][y] == NILL or board_array[x][y] == BLACK)
		return true;
	else
		return false;
}

int Board :: getBoardIdx(int x, int y)
{
	return board_array[x][y];
}

void Board :: RandomMovement(Ghost *G)
{
	//srand (time(NULL));
	int n = rand() % 4;

	if (n == 0)
	{
		//cout << "left \n";
		if (checkPath((12 - (G->getGhostPos().getY() / 60)), (G->getGhostPos().getX() - 60) / 60) == true)
			G->MoveGhostX(G->getGhostPos().getX() - 60);  // Move one block to the right
	}
	else if (n == 1)
	{
		//cout << "right \n";
		if (checkPath((12 - (G->getGhostPos().getY() / 60)), (G->getGhostPos().getX() + 60) / 60) == true)
			G->MoveGhostX(G->getGhostPos().getX() + 60);  // Move one block to the left
	}
	else if (n == 2)
	{
		//cout << "up \n";
		if (checkPath((12 - ((G->getGhostPos().getY() + 60) / 60)) , G->getGhostPos().getX() / 60) == true)
			G->MoveGhostY(G->getGhostPos().getY() + 60);  // Move one block above
	}
	else if (n == 3)
	{
		//cout << "down \n";
		if (checkPath((12 - ((G->getGhostPos().getY() - 60) / 60)) , G->getGhostPos().getX() / 60) == true)
			G->MoveGhostY(G->getGhostPos().getY() - 60);	// Move one block below
	}
}

void Board :: Draw()
{
	glColor3f(0, 0, 1);
	glPushMatrix();

#ifdef WITH_TEXTURES
	for (int i = BOARD_Y - 2, y = 0; i >= 0; --i, y += xcellsize) {
		for (int j = 0, x = 0; j < BOARD_X; j++, x += (ycellsize)) {
			//			cout << " " << board_array[i][j] << " " << flush;
			switch (board_array[i][j]) {
				case NILL:
				// Empty space
				break;
				case S_BRICK:
					Drawbrick(S_BRICK, x - 90, y, cwidth,cheight);
					break;
				case G_BRICK:
					Drawbrick(G_BRICK, x - 10, y, cwidth,cheight);
					break;
				case R_BRICK:
					Drawbrick(R_BRICK, x - 10, y, cwidth,cheight);
					break;
				/*float fwidth = (float) (xcellsize) / width * 2, fheight =
				(float) ycellsize / height * 2;
				float fx = (float) (x - 10) / width * 2 - 1, fy = (float) y / height * 2 - 1;*/

				/*Drawbrick((BoardParts) board_array[i][j], fx, fy, fwidth,
				 fheight);*/
				/*Drawbrick((BoardParts) board_array[i][j], (float)x/width-1, (float)y/height-1, fwidth,
						fheight);*/
				//break;
			}
		}
	}
#else

	int arr[5] = {CORAL, TEAL , MAGENTA , GREEN , OLIVE};

	for (int i = BOARD_Y - 2, y = 0; i >= 0; --i, y += xcellsize)
	{
		for (int j = 0, x = 0; j < BOARD_X; j++, x += (ycellsize))
		{
			int k = arr[rand() % 5];
			switch (board_array[i][j])
			{
				case NILL:

					if (x == 60 and y == 420)
						DrawCircle(60 + 18, 420 + 30 , 10, colors[VIOLET]);
					else if (x == 900 and y == 60)
						DrawCircle(900 + 18, 60 + 30 , 10, colors[VIOLET]);
					else if (x == 900 and y == 660)
						DrawCircle(900 + 18, 660 + 30 , 10, colors[VIOLET]);
					else if (x == 60 and y == 660)
						DrawCircle(60 + 18, 660 + 30 , 10, colors[VIOLET]);
					else
						DrawCircle(x + 18, y + 30 , 5, colors[k]);

					break;

				case S_BRICK:
					DrawRectangle(x - 10, y, ycellsize, xcellsize, colors[SLATE_GRAY]);
					break;

				case G_BRICK:
					DrawRectangle(x - 10, y, ycellsize, xcellsize, colors[DARK_GRAY]);
					break;

				case R_BRICK:
					DrawRectangle(x - 10, y, ycellsize, xcellsize, colors[BLUE]);
					break;
			}
		}
	}

#endif
	glPopMatrix();
}

void Board::GetInitPinkyPosition(int &x, int &y)
{
	x = xcellsize * 3;
	y = (BOARD_Y - 3) * ycellsize;
}
void Board::GetInitTextPosition(int &x, int &y)
{
	x = xcellsize;
	y = (BOARD_Y - 1) * ycellsize + ycellsize / 2;
}

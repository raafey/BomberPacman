//============================================================================
// Name        : .cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Brick Slayer...
//============================================================================

#ifndef Bomberman_CPP_
#define Bomberman_CPP_
#include "Point.h"
#include "Board.h"
#include "PacMan.h"
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
bool bombStatus = false;
Board *b;
// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 *
 * */
void SetCanvasSize(int width, int height)
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

void DrawEnemy(int x/*starting x*/, int y/*starting y*/,
		ColorNames color/*color*/, float gw = 6/*Enemy Width in Units*/,
		float gh = 7/*Enemy Height in Units*/) {
	int ogw = 6, ogh = 7;

	glPushMatrix();
	float sx = (float) gw / ogw, sy = (float) gh / ogh;
	glTranslatef(x, y, 1);
	glScalef(sx, sy, 1);

	// Draw Enemy
	DrawRoundRect(0, 1, 6, 3, colors[color]);
	DrawCircle(3, 4, 3.01, colors[color]);
	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	//  legs
	DrawCircle(0.75, 1, 0.75, colors[color]);
	DrawCircle(3.25, 1, 0.75, colors[color]);
	DrawCircle(5.85, 1, 0.75, colors[color]);

	glPopMatrix();
	//	glPopMatrix();

	// eyes

	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	DrawCircle(1.85, 3.95, 0.75, colors[WHITE]);
	DrawCircle(4.95, 3.95, 0.75, colors[WHITE]);
	glPopMatrix();

	// eyes
	DrawCircle(1.65, 4.25, 0.45, colors[BLUE]);
	DrawCircle(4.45, 4.25, 0.45, colors[BLUE]);
	glPopMatrix();
}

//Number of Vertices used to draw Bomberman Circle...
// x= r cos (theta), y= r sin(theta)
const int npmvertices = 1220;
GLfloat pmvertices[npmvertices][2];
void InitPMVertices(float radius) {
	float hdegree = (M_PI - M_PI / 2.0) / 360.0;
	float angle; // -2 up, 1 for right, -8.3 down, -5 for left

		if (b->direction == 1)
			angle = M_PI + M_PI / 6.0;
		else if (b->direction == 2)
			angle = M_PI + -5*M_PI / 6.0;
		else if (b->direction == 3)
			angle = M_PI + -2*M_PI / 6.0;
		else if (b->direction == 4)
			angle = M_PI + -8.3*M_PI / 6.0;
		else
			angle = M_PI + M_PI / 6.0;

	for (int i = 0; i < npmvertices; ++i) {
		pmvertices[i][0] = radius * cos(angle);
		pmvertices[i][1] = radius * sin(angle);
		angle += hdegree;
	}
}

void DrawBomberman(float sx/*center x*/, float sy/*center y*/,
		float radius/*Radius*/,
		const ColorNames &colorname/*Bomberman Colour*/) {

	glColor3fv(colors[colorname]); // set the circle color
	InitPMVertices(radius);
	glBegin (GL_TRIANGLE_FAN);
	glVertex4f(sx, sy, 0, 1);
	for (int i = 0; i < npmvertices; ++i)
		glVertex4f(sx + pmvertices[i][0], sy + pmvertices[i][1], 0, 1);
	glEnd();
	DrawCircle(sx - radius + radius / 2, sy + (radius - radius / 2),
			radius / 10, colors[BLACK]);
}

/*
 * Main Canvas drawing function.
 * */
void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0.0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	//

	if (b->getCountDown().getSeconds() > 0 and b->getPacman().getCount() != 0 and b->getBricksDestroyed() != 27 and b->getGhostCount() < 4)
	{
		b->Draw();
		int x, y;


		if (b->getBlinky()->getLifeStatus() == true)
		{
			if (b->getBlinky()->getState() == false)
				DrawEnemy(b->getBlinky()->getGhostPos().getX(), b->getBlinky()->getGhostPos().getY(), CRIMSON, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
			else
				DrawEnemy(b->getBlinky()->getGhostPos().getX(), b->getBlinky()->getGhostPos().getY(), BLUE, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
		}

		if (b->getBricksDestroyed() >= 8 and b->getInky()->getLifeStatus() == true)
		{
			if (b->getInky()->getState() == false)
				DrawEnemy(b->getInky()->getGhostPos().getX(), b->getInky()->getGhostPos().getY(), TURQUOISE, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
			else
				DrawEnemy(b->getInky()->getGhostPos().getX(), b->getInky()->getGhostPos().getY(), BLUE, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
		}

		if (b->getBricksDestroyed() >= 19 and b->getClyde()->getLifeStatus() == true)
		{
			if (b->getClyde()->getState() == false)
				DrawEnemy(b->getClyde()->getGhostPos().getX(), b->getClyde()->getGhostPos().getY(),ORANGE, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
			else
				DrawEnemy(b->getClyde()->getGhostPos().getX(), b->getClyde()->getGhostPos().getY(),BLUE, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
		}

		if (b->getPinky()->getLifeStatus() == true)
		{
			if (b->getPinky()->getState() == false)
				DrawEnemy(b->getPinky()->getGhostPos().getX(), b->getPinky()->getGhostPos().getY(), DEEP_PINK, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
			else
				DrawEnemy(b->getPinky()->getGhostPos().getX(), b->getPinky()->getGhostPos().getY(), BLUE, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
		}

		//cout << b->getPacman().getPos() << endl;

		DrawBomberman(b->getPacman().getPos().getX(),b->getPacman().getPos().getY(), b->GetCellSize() / 2 - 2, ORANGE);
		b->GetInitTextPosition(x, y);
		y -= 10;

		int t;
		if (b->getCountDown().getSeconds() > 10)
			t = LIME_GREEN;
		else
			t = CORAL;

		DrawString(x, y, "Score : " + Num2Str(b->getPacman().getScore()), colors[BLUE]);
		DrawString(x + 400, y, "Time : ", colors[BLUE]);
		DrawString(x + 470, y, Num2Str(b->getCountDown().getSeconds()), colors[t]);
		DrawString(x + 800, y, "Lives left : " + Num2Str(b->getPacman().getCount()) , colors[BLUE]);

		if (b->nPpressed == 1)
			DrawString(x + 600, y, "Paused", colors[CORAL]);

		//	glPopMatrix();

		if (bombStatus == true)
		{
			if (b->getPacman().getBomb().getBombTimer() == 1)
				b->DrawFireTrail();
			DrawCircle(b->getPacman().getBomb().getBombPosition().getX(), b->getPacman().getBomb().getBombPosition().getY(), 26, colors[BLACKO]);
		}
	}
	else
	{
		string str;
		if (b->getGhostCount() == 4 or b->getBricksDestroyed() == 27)
			str = "You Win!!!";
		else
			str = "You Lose!!!";

		DrawString(310 , 650 , "GAME OVER - " + str , colors[WHITE]);
		DrawString(440, 590, "Score : " + Num2Str(b->getPacman().getScore()), colors[BLUE]);
		DrawString(80, 800 , "Press Esc to exit" , colors[LIME_GREEN]);
		DrawEnemy(60, 400, CRIMSON, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
		DrawEnemy(120, 400, TURQUOISE, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
		DrawEnemy(180, 400,ORANGE, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
		DrawEnemy(240,  400 , DEEP_PINK, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
		DrawBomberman(850 ,440 , b->GetCellSize() / 2 - 2, ORANGE);
		DrawLine(40 , 750, 40, 60, 4 ,colors[BLUE]);
		DrawLine(40 , 750, 950, 750, 4 ,colors[BLUE]);
		DrawLine(40 , 60, 950, 60, 4 ,colors[BLUE]);
		DrawLine(950 , 60, 950, 750, 4 ,colors[BLUE]);

	}

	glutSwapBuffers(); // do not modify this line..}

}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {

	if (b->getCountDown().getSeconds() > 0 and b->nPpressed != 1)
	{
		if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)
		{
			if (b->checkPath((12 - (b->getPacman().getPos().getY() - 30) / 60) , ((b->getPacman().getPos().getX() - 80) / 60)) == true)
			{
				b->getPacman().MoveX(b->getPacman().getPos().getX() - 60);
				b->Eat();
				b->direction = 1;
			}
		}
		else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/)
		{
			if (b->checkPath((12 - (b->getPacman().getPos().getY() - 30) / 60), ((b->getPacman().getPos().getX()  + 40) / 60)) == true)
			{
				b->getPacman().MoveX(b->getPacman().getPos().getX() + 60);
				b->Eat();
				b->direction = 2;
			}
		}
		else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/)
		{
			if (b->checkPath((12 - (b->getPacman().getPos().getY() + 30) / 60), ((b->getPacman().getPos().getX()  - 20) / 60)) == true)
			{
				b->getPacman().MoveY(b->getPacman().getPos().getY() + 60);
				b->Eat();
				b->direction = 3;
			}
		}
		else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/)
		{
			if (b->checkPath((12 - (b->getPacman().getPos().getY() - 90) / 60), ((b->getPacman().getPos().getX()  - 20) / 60)) == true)
			{
				b->getPacman().MoveY(b->getPacman().getPos().getY() - 60);
				b->Eat();
				b->direction = 4;
			}
		}
	}
		/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
		 * this function*/
		 glutPostRedisplay();
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y)
{
	if (key == 27/* Escape key ASCII*/)
	{
		exit(1); // exit the program when escape key is pressed.
	}

	if ((key == 'b' || key == 'B') and b->nPpressed != 1) //Key for placing the bomb
	{
		if (b->getPacman().getBomb().getBombTimer() == 2)
		{
			bombStatus = true;
			b->getPacman().PlantBomb(b->getPacman().getPos().getX(), b->getPacman().getPos().getY());
		}
	}

	if (key == 'P' or key == 'p')
	{
		b->nPpressed++;

		if (b->nPpressed == 2)
		{
			b->nPpressed = 0;
		}
	}

	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m)
{
	if (b->nPpressed != 1)
	{
		if (b->getCountDown().getSeconds() > 0)
		{
			b->getCountDown().setTimer((b->getCountDown().getSeconds() - 1));
		}

		if (bombStatus == true)
		{
			if (b->getPacman().getBomb().getBombTimer() >= 0)
			{
				b->getPacman().getBomb().setBombTimer(b->getPacman().getBomb().getBombTimer() - 1);
			}

			if (b->getPacman().getBomb().getBombTimer() == 0)
			{
				b->Detonate();

				if ((b->checkPacmanSafety() == false) and (b->getPacman().getCount() > 0))
				{
					b->getPacman().MoveX(80);
					b->getPacman().MoveY(90);
					b->getPacman().setCount(b->getPacman().getCount() - 1);
				}

				if (b->getPinky()->getLifeStatus() == true)
					b->checkGhostSafety(b->getPinky());
				if (b->getBlinky()->getLifeStatus() == true)
					b->checkGhostSafety(b->getBlinky());
				if (b->getBricksDestroyed() >= 8 and b->getInky()->getLifeStatus() == true)
					b->checkGhostSafety(b->getInky());
				if (b->getBricksDestroyed() >= 19 and b->getClyde()->getLifeStatus() == true)
					b->checkGhostSafety(b->getClyde());

				b->getPacman().getBomb().setBombTimer(2);
				bombStatus = false;
			}
		}

		if (b->getBlinky()->getLifeStatus() == true)
		{
			b->RandomMovement(b->getBlinky());
			b->EatPacman(b->getBlinky());
		}

		if (b->getPinky()->getLifeStatus() == true)
		{
			b->RandomMovement(b->getPinky());
			b->EatPacman(b->getPinky());
		}

		if (b->getBricksDestroyed() >= 8 and b->getInky()->getLifeStatus() == true)
		{
			b->RandomMovement(b->getInky());
			b->EatPacman(b->getInky());
		}

		if (b->getBricksDestroyed() >= 19 and b->getClyde()->getLifeStatus() == true)
		{
			b->RandomMovement(b->getClyde());
			b->EatPacman(b->getClyde());
		}

		if (b->getstateTime() >= 0 and (b->getBlinky()->getState() == true or b->getInky()->getState() == true or b->getClyde()->getState() == true or b->getPinky()->getState() == true))
		{
			b->setstateTime(b->getstateTime() - 1);
		}

		if (b->getstateTime() == 0)
		{
			b->getBlinky()->setState(false);
			b->getInky()->setState(false);
			b->getClyde()->setState(false);
			b->getPinky()->setState(false);
			b->setstateTime(10);
		}

	}
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0, Timer, 0);
	glutPostRedisplay();
}


/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	b = new Board(60, 60); // create a new board object to use in the Display Function ...
	int width = 1010, height = 840; // i have set my window size to be 800 x 600
	b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("CP's Bomberman"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...
	b->DisplayArrayOrder();
	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
#ifdef WITH_TEXTURES
	RegisterTextures();
#endif
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(700.0, Timer, 0);

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* Bomberman_CPP_ */

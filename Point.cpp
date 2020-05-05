#include "Point.h"
#include <iostream>
#include <cmath>

using namespace std;

Point :: Point()
{
	x = 0;
	y = 0;
}

Point :: Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Point :: setX(int x)
{
	this->x = x;
}

void Point :: setY(int y)
{
	this->y = y;
}

int Point :: getX() const
{
	return x;
}

int Point :: getY() const
{
	return y;
}

double Point :: distance(const Point &P)
{
	return pow(pow(x - P.x, 2) + pow(y - P.y, 2), 0.5);
}

ostream& operator << (ostream & out, const Point &p)
{
	cout << "(" << p.getX() << "," << p.getY() << ")";
	return out;
}

Point :: ~Point() {}

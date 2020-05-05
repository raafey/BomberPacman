#ifndef POINT_H_
#define POINT_H_

#include <iostream>
using namespace std;

class Point
{
	private :

		int x;
		int y;

	public :

		Point();
		Point(int,int);
		void setX(int);
		void setY(int);
		int getY()const;
		int getX() const;
		double distance(const Point &);
		~Point();
};

ostream& operator << (ostream & out, const Point &p);

#endif

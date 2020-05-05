#ifndef TIMER_H_
#define TIMER_H_

class Tick
{
	private :

		int seconds;

	public :

		Tick();
		void setTimer(int);
		int getSeconds();
		~Tick();
};

#endif

#ifndef BALL_H
#define BALL_H

#include "define.h"
#include "tools.h"


class Ball {
	
	
	private :
		Point centre_;  //coordonnée du centre
		double angle_;  //angle par rapport à l'horizentale
		
	public :
	
		Ball(Point c, double a)
		: centre_(c), angle_(a)
		{}
		
		Ball()
		: angle_(0)
		{}
	 
		void centre(Point c);  //changer du centre
		Point centre();       //optenir les coordonnée du centre
		
		void angle(double a);  //changer angle
		double angle();        //optenir l'angle
		


};

#endif

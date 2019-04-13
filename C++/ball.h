#ifndef BALL_H
#define BALL_H

#include "define.h"
#include "tools.h"

#include "player.h"
#include "obstacle.h"

class Player;
class Obstacle;
class Ball {
	
	
	private :
		Point centre_;  //coordonnée du centre
		double angle_;  //angle par rapport à l'horizentale
		double nbCells_;
		Point c_dessin_; //centre dans gtkmm
		
	public :
	
		
		Ball(Point c, double a, double n);
		
		
		Ball();
		
	 
		void centre(Point c);  //changer du centre
		Point centre();       //optenir les coordonnée du centre
		
		void angle(double a);  //changer angle
		double angle();        //optenir l'angle
		
		void c_dessin(Point c);
		Point c_dessin();
		
		void nbCells(double n);
		double nbCells();
		
		bool collide_with(Player p, double marge);
		
		bool collide_with(Ball b, double marge);
	
		bool collide_with(Obstacle o, double marge);
		
		Rond rond();


};

#endif

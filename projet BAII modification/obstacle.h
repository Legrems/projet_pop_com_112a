#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "define.h"
#include "tools.h"

#include "ball.h"
#include "player.h"

class Player;
class Ball;

class Obstacle {
	
	private :
	
		int ligne_;     //ligne de l'obstacle 
		int colonne_;   //colonne de l'obstacle
		double x_;
		double y_;
		
	public : 
		
		//    ATTENTION !!!!!! QUESTION POUR ASSISTANT !!!!!!!
		
		static int nbCells;	
		
		//    ATTENTION !!!!!! QUESTION POUR ASSISTANT !!!!!!!
		
		Obstacle();
		Obstacle(int l, int c);
		
		void ligne(int l);   //changer de ligne
		int ligne();         //obtenir la ligne
		
		void colonne(int c);  //changer colonne
		int colonne();        //obtenir colonne
		
		void x(double x);
		double x();
		
		void y(double y);
		double y();
		
		bool collide_with(Player p, double marge);
		
		bool collide_with(Ball b, double marge);
	
		bool collide_with(Obstacle o, double marge);
		
		bool collide_with(Obstacle o);

};
		

#endif

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
		Point coin_sup_;
		
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
		
		void coin_sup(Point p);
		Point coin_sup();
		
		bool collide_with(Player p, double marge);
		
		bool collide_with(Ball b, double marge);
	
		bool collide_with(Obstacle o, double marge);
		
		bool collide_with(Obstacle o);

};
		

#endif

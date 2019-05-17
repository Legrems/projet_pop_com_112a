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
		int nbCells_;
		Point coin_sup_;
		
	public : 
	
		
		Obstacle();
		Obstacle(int l, int c, int n);
		
		void ligne(int l);   //changer de ligne
		int ligne();         //obtenir la ligne
		
		void colonne(int c);  //changer colonne
		int colonne();        //obtenir colonne
		
		void coin_sup(Point p);
		Point coin_sup();
		
		void nbCells(int n);
		int nbCells();
		
		bool collide_with(Player p, double marge);
		
		bool collide_with(Ball b, double marge);
	
		bool collide_with(Obstacle o, double marge);
		
		bool collide_with(Obstacle o);

		Rectangle rectangle_();
		Rectangle rectangle_cell();
		
		bool collide_with(std::vector<Ball> &Balls);
};
		

#endif

#ifndef PLAYER_H
#define PLAYER_H

#include "define.h"
#include "tools.h"
#include "ball.h"
#include "obstacle.h"

class Ball;
class Obstacle;

class Player{
	
	private:
	
		Point centre_;   //coordonnée du centre
		int nbT_;        //nombre de touche restante
		double count_;   //compteur avant prochain tir
		
	public:
	
		Player()
		: nbT_(0)
		{}
		
		Player(Point c, int n, double co)
		: centre_(c),nbT_(n),count_(co)
		{}
	
		void centre(Point c);   //changer le centre
		Point centre();         //obtenir le centre
		void nbT(int n);        //changer le nombre de touche
		int nbT();              //obtenir le nombre de touche
		void count(double c);   //changer le compteur
		double count();         //obtenir le compteur
		
		bool collide_with(Player p, double marge);
		
		bool collide_with(Ball b, double marge);
	
		bool collide_with(Obstacle o, double marge);
	
};
		

#endif 

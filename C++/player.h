#ifndef PLAYER_H
#define PLAYER_H

#include "define.h"
#include "tools.h"
#include "ball.h"
#include "obstacle.h"
#include <vector>

class Ball;
class Obstacle;

class Player{
	
	private:
		
		int nbCells_;
		int nbT_;        //nombre de touche restante
		double count_;   //compteur avant prochain tir
		Point centre_;   //coordonnée du centre
		Point c_dessin_; //centre dans gtkmm
		
	public:
	
		Player();
		
		Player(Point c, int n, double co, int nc);
	
		void centre(Point c);   //changer le centre
		Point centre();         //obtenir le centre
		void nbT(int n);        //changer le nombre de touche
		int nbT();              //obtenir le nombre de touche
		void count(double c);   //changer le compteur
		double count();         //obtenir le compteur
		void c_dessin(Point c);
		Point c_dessin();
		void nbCells(int n);
		int nbCells();
		
		bool collide_with(Player p, double marge);
		
		bool collide_with(Ball b, double marge);
	
		bool collide_with(Obstacle o, double marge);
		
		Rond rond();
		
		int target(std::vector<Player> &liste_joueur);
		
		bool contact(Player p);
		
		void add_count();
		
		bool collide_with(std::vector<Ball> &Balls);
	
};
		

#endif 

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
		int nb_cells_;
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
		void nb_cells(int n);
		int nb_cells();
		
		bool collide_with(Player p, double marge);
		
		bool collide_with(Ball b, double marge);
	
		bool collide_with(Obstacle o, double marge);
		
		Rond rond();
		
		int target(std::vector<Player> &liste_joueur);
		
		bool contact(Player p);
		bool contact_shot(Player p);
		
		void add_count();
		
		bool collide_with(std::vector<Ball> &Balls);
		
		void shot(Player p, std::vector<Ball> &Balls);

		void move(double move_x, double move_y);
		void move(Point vector);
	
};
		

#endif 

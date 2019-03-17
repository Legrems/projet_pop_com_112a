#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "define.h"
#include "tools.h"

class Obstacle {
	
	private :
	
		int ligne_;     //ligne de l'obstacle 
		int colonne_;   //colonne de l'obstacle
		
	public : 
	
		Obstacle()
		: ligne_(0),colonne_(0)
		{}
		
		Obstacle(int l, int c)
		: ligne_(l), colonne_(c)
		{}
		
		void ligne(int l);   //changer de ligne
		int ligne();         //obtenir la ligne
		
		void colonne(int c);  //changer colonne
		int colonne();        //obtenir ligne

};
		

#endif

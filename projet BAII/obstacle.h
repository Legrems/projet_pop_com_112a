#include "tools.h"

class Obstacle {
	
	private :
	
		int ligne_;
		int colonne_;
		
	public : 
	
		Obstacle()
		: ligne_(0),colonne_(0)
		{}
		
		Obstacle(int l, int c)
		: ligne_(l), colonne_(c)
		{}
		
		void ligne(int l);
		int ligne();
		
		void colonne(int c);
		int colonne();

};
		

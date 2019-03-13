#include "tools.h"

class Player{
	
	private:
	
		Point centre_;
		int nbT_;
		double count_;
		
	public:
	
		Player()
		: nbT_(0)
		{}
		
		Player(Point c, int n, double co)
		: centre_(c),nbT_(n),count_(co)
		{}
	
		void centre(Point c);
		Point centre();
		void nbT(int n);
		int nbT();
		void count(double c);
		double count();
	
	
};
		

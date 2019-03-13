#include "tools.h"


class Ball {
	
	
	private :
		Point centre_;
		double angle_;
		
	public :
	
		Ball(Point c, double a)
		: centre_(c), angle_(a)
		{}
		
		Ball()
		: angle_(0)
		{}
	 
		void centre(Point c);
		Point centre();
		
		void angle(double a);
		double angle();
		


};

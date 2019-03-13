#ifndef TOOLS_H
#define TOOLS_H
class Point{
	private:
		int x_;
		int y_;
		
	public:
	
		Point()
		: x_(0),y_(0)
		{}
	
		Point (int x, int y)
		  : x_(x), y_(y)
		{}
		
		void x(int new_x);
		void y(int new_y);
		int x();
		int y();
		
};

#endif

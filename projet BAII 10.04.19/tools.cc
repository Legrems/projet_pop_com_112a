#include "tools.h"
#include <cmath>
#include <algorithm>
using namespace std;

Point::Point()
		: x_(0),y_(0)
		{}
Point::Point (double x, double y)
		  : x_(x), y_(y)
		{}
	

void Point::x(double new_x){x_ = new_x;}

void Point::y(double new_y){y_ = new_y;}

double Point::x(){return x_;}
double Point::y(){return y_;}		



Rectangle::Rectangle ()
		: p1_(0,0)
		{}
		
Rectangle::Rectangle (Point a, Point b)
		: p1_(a), p2_(a.x(),b.y()),p3_(b),p4_(a.y(),b.x())
		{}
		
Rectangle::Rectangle (Point a, Point b, Point c, Point d)
		: p1_(a), p2_(b), p3_(c), p4_(d)
		{}
		

Point Rectangle::c1(){return p1_;}
Point Rectangle::c2(){return p2_;}
Point Rectangle::c3(){return p3_;}
Point Rectangle::c4(){return p4_;}

bool Rectangle::appartient(Point a)
{
	double x[5] = {p1_.x(),p2_.x(),p3_.x(),p4_.x(),a.x()};
	double y[5] = {p1_.y(),p2_.y(),p3_.y(),p4_.y(),a.y()};
	
	sort(x,x+5);
	sort(y,y+5);
		
	if ((x[2]==a.x())&&(y[2]==a.y())){return true;}
	else {return false;}
}
		
	
		
double ecart(Point a, Point b){
	double d(0);
	double d_x = a.x()-b.x();
	double d_y = a.y()-b.y();
	
	d = sqrt((d_x*d_x)+(d_y*d_y));
	return d;
}

#ifndef TOOLS_H
#define TOOLS_H

#include "define.h"


class Point
{
	private:
		double x_;
		double y_;
		
	public:
	
		Point()
		: x_(0),y_(0)
		{}
	
		Point (double x, double y)
		  : x_(x), y_(y)
		{}
		
		void x(double new_x);
		void y(double new_y);
		double x();
		double y();
		
};

class Rectangle
{
	private:
		Point p1_;   //coordonnées des 4 coins du rectangle
		Point p2_;
		Point p3_;
		Point p4_;
		
	public:
		Rectangle ()
		: p1_(0,0)
		{}
		
		Rectangle (Point a, Point b)
		: p1_(a), p2_(a.x(),b.y()),p3_(b),p4_(a.y(),b.x())
		{}
		
		Rectangle (Point a, Point b, Point c, Point d)
		: p1_(a), p2_(b), p3_(c), p4_(d)
		{}
		
		Point c1();   //donne les coordonnée des 4 coins
		Point c2();
		Point c3();
		Point c4();
		
		bool appartient(Point a);   //renvoie true si le point est dans 
};                                  //le rectangle
		
		


double ecart(Point a,Point b);    //donne la distance entre 2 point

#endif

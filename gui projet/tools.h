#ifndef TOOLS_H
#define TOOLS_H

#include "define.h"


class Point
{
	private:
		double x_;
		double y_;
		
	public:
	
		Point();
		Point (double x, double y);
		
		
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
		Rectangle ();
		
		Rectangle (Point a, Point b);
		
		Rectangle (Point a, Point b, Point c, Point d);
		
		Point c1();   //donne les coordonnée des 4 coins
		Point c2();
		Point c3();
		Point c4();
		
		bool appartient(Point a);   //renvoie true si le point est dans 
};                                  //le rectangle
		
		


double ecart(Point a,Point b);    //donne la distance entre 2 point

#endif

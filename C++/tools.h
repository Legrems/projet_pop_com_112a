#ifndef TOOLS_H
#define TOOLS_H

#include "define.h"

bool est_entre(double a, double b, double c);

class Couleur
{
	protected:
		double red_;
		double green_;
		double blue_;
		
	public:
		Couleur (double r, double g, double b);
		
		void red(double r);
		double red();
		
		void green(double g);
		double green();
		
		void blue(double b);
		double blue();
		
};
		
class Rectangle;		
		
class Point
{
	protected:
		double x_;
		double y_;
		
	public:
	
		Point();
		Point (double x, double y);
		
		
		void x(double new_x);
		void y(double new_y);
		double x();
		double y();
		
		Rectangle rect(Point p2, double largeur);

};

class Droite
{
	protected: 
		Point p1_, p2_;
		bool vertical_;
		double pente_;
		double hauteur_;
		
	public:
	
		Droite();
		Droite(Point p1, Point p2);
	
		Point p1();
		Point p2();
		void p1(Point p);
		void p2(Point p);
		bool vertical();
		double pente();
		double hauteur();
		
		void set_equation();
		
		bool collide_with(Droite d);
		
		
};


class Form
{
	protected:
		Couleur couleur_;
		
	public:
		Form();
		Form(Couleur c);
		
		void couleur(Couleur c);
		Couleur couleur();
};

		

class Rectangle : public Form
{
	protected:
		Point c1_;   //coordonnées des 4 coins du rectangle
		Point c2_;
		Point c3_;
		Point c4_;
		double hauteur_;
		double largeur_;
		
	public:
		Rectangle ();
		
		Rectangle (Point a, Point b);
		
		Rectangle (Point a, Point b, Point c, Point d);
		
		Rectangle (Point a, double h, double l, Couleur c);
		
		Point c1();   //donne les coordonnée des 4 coins
		Point c2();
		Point c3();
		Point c4();
		double largeur();
		double hauteur();
		
		
		bool appartient(Point a);   //renvoie true si le point est dans 
	                                //le rectangle
		bool collide_with(Droite d);
		bool collide_with(Rectangle rect);//renvoie true si les deux 
                                          //rectangles sont en collision
};
		
class Rond : public Form
{
	protected:
		Point centre_;
		double rayon_;
		double fraction_;
		
		
	public:
		Rond(Point p, double r, Couleur c);
		Rond(Point p, double r, Couleur c,double f);
		
		void centre(Point p);
		Point centre();
		
		void rayon(double r);
		double rayon();
		
		void fraction(double f);
		double fraction();
};
		
		

double ecart(Point a,Point b);    //donne la distance entre 2 point

#endif

#include "ball.h"

using namespace std;


Ball::Ball(Point c, double a, int n)
		: centre_(c), angle_(a), nbCells_(n), 
		 c_dessin_(c.x()+DIM_MAX,DIM_MAX-c.y())
		{}

Ball::Ball()
		: angle_(0)
		{}

void Ball::nbCells(int n){nbCells_ = n;}
int Ball::nbCells(){return nbCells_;}

void Ball::centre(Point c){centre_ = c;}
Point Ball::centre(){return centre_;}

void Ball::angle(double a){angle_ = a;}
double Ball::angle(){return angle_;}

void Ball::c_dessin(Point c){c_dessin_ = c;}
Point Ball::c_dessin(){return c_dessin_;}

bool Ball::collide_with(Player p, double marge){
	double dist = COEF_RAYON_JOUEUR + COEF_RAYON_BALLE + marge;
	
	if (ecart(p.centre(),centre_) <= dist){return true;}
	
	else{return false;}
}

bool Ball::collide_with(Ball b, double marge){
	double dist = marge + 2 * COEF_RAYON_BALLE;
	
	if (ecart(b.centre(),centre_) <= dist){return true;}
	
	else{return false;}
	
}

bool Ball::collide_with(Obstacle o, double marge){
	
	marge += COEF_RAYON_BALLE;
	Point p1(o.colonne() - marge, o.ligne() - marge);
	Point p3(o.colonne() + marge + 1, o.ligne() + marge + 1);
	
	Rectangle r_ext(p1,p3);
	
	if (!(r_ext.appartient(centre_))){return false;}
	
	p1.x(o.colonne() - marge);
	p1.y(o.ligne());
	p3.x(o.colonne() + 1 + marge);
	p3.y(o.ligne() + 1);
		
	Rectangle r_marge_vert (p1,p3);  //rectangle contenant l'obstacle et 
		                             //les marges verticales
	p1.x(o.colonne());
	p1.y(o.ligne() - marge);
	p3.x(o.colonne() + 1);
	p3.y(o.ligne() + 1 + marge);
		
	Rectangle r_marge_horiz (p1, p3);//rectangle contenant l'obstacle et 
		                             //les marges horizontales
		
	if (r_marge_vert.appartient(centre_)){return true;}
	if (r_marge_horiz.appartient(centre_)){return true;}
		
	Point coin1(o.colonne(),o.ligne());       //4 coins de l'obstacle
	Point coin2(o.colonne(), o.ligne() + 1);
	Point coin3(o.colonne() + 1,o.ligne());
	Point coin4(o.colonne() + 1,o.ligne() + 1);
		
	if ((ecart(coin1, centre_))<(marge)){return true;}
	if ((ecart(coin2, centre_))<(marge)){return true;}
	if ((ecart(coin3, centre_))<(marge)){return true;}
	if ((ecart(coin4, centre_))<(marge)){return true;}	
	
	return false;
}

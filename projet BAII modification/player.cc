#include "player.h"

using namespace std;


Player::Player()
		: nbT_(0)
		{}
Player::Player(Point c, int n, double co)
		: centre_(c),nbT_(n),count_(co)
		{}		

void Player::centre(Point c) {centre_ = c;}
Point Player::centre() {return centre_;}

void Player::nbT(int n) {nbT_ = n;}
int Player::nbT() {return nbT_;}

void Player::count(double c) {count_ = c;}
double Player::count() {return count_;}


bool Player::collide_with(Player p, double marge) {
	
	double cell = SIDE/nbCells;
	double dist = (2 * COEF_RAYON_JOUEUR + marge)*cell;
	
	if (ecart(p.centre(), centre_) <= dist) {return true;}
	
	else{return false;}
	
}

bool Player::collide_with(Ball b, double marge) {
	
	double cell = SIDE/nbCells;
	double dist = (COEF_RAYON_JOUEUR + marge + COEF_RAYON_BALLE)*cell;
	
	if (ecart(b.centre(), centre_) <= dist) {return true;}
	
	else{return false;}
	
}

bool Player::collide_with(Obstacle o, double marge) {
	
	double cell = SIDE/nbCells;
	marge = (marge + COEF_RAYON_JOUEUR)*cell;
	Point p1(o.x() - marge, o.y() + marge);
	Point p3(o.x() + marge + cell, o.y() - marge - cell);
	
	Rectangle r_ext(p1, p3);
	
	if (!(r_ext.appartient(centre_))) {return false;}
	
	p1.x(o.x() - marge);
	p1.y(o.y());
	p3.x(o.x() + cell + marge);
	p3.y(o.y() - cell);
		
	Rectangle r_marge_vert (p1, p3); //rectangle contenant l'obstacle et 
		                             //les marges verticales
	p1.x(o.x());
	p1.y(o.y() + marge);
	p3.x(o.x() + cell);
	p3.y(o.y() - cell - marge);
		
	Rectangle r_marge_horiz (p1, p3);//rectangle contenant l'obstacle et 
		                             //les marges horizontales
		
	if (r_marge_vert.appartient(centre_)) {return true;}
	if (r_marge_horiz.appartient(centre_)) {return true;}
		
	Point coin1(o.x(), o.y());       //4 coins de l'obstacle
	Point coin2(o.x(), o.y() - cell);
	Point coin3(o.x() + cell, o.y());
	Point coin4(o.x() + cell, o.y() - cell);
		
	if ((ecart(coin1, centre_)) < (marge)) {return true;}
	if ((ecart(coin2, centre_)) < (marge)) {return true;}
	if ((ecart(coin3, centre_)) < (marge)) {return true;}
	if ((ecart(coin4, centre_)) < (marge)) {return true;}	
	
	return false;
}


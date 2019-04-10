#include "player.h"

using namespace std;


Player::Player()
		: nbT_(0)
		{}
Player::Player(Point c, int n, double co, int nc)
		: centre_(c),nbT_(n),count_(co),nbCells_(nc),
		c_dessin_(c.x()+DIM_MAX,DIM_MAX-c.y())
		{}		

void Player::centre(Point c) {centre_ = c;}
Point Player::centre() {return centre_;}

void Player::nbT(int n) {nbT_ = n;}
int Player::nbT() {return nbT_;}

void Player::count(double c) {count_ = c;}
double Player::count() {return count_;}

void Player::c_dessin(Point c){c_dessin_ = c;}
Point Player::c_dessin(){return c_dessin_;}

void Player::nbCells(int n){nbCells_ = n;}
int Player::nbCells(){return nbCells_;}


bool Player::collide_with(Player p, double marge) {
	double dist = 2 * COEF_RAYON_JOUEUR + marge;
	
	if (ecart(p.centre(), centre_) <= dist) {return true;}
	
	else{return false;}
	
}

bool Player::collide_with(Ball b, double marge) {
	double dist = COEF_RAYON_JOUEUR + marge + COEF_RAYON_BALLE;
	
	if (ecart(b.centre(), centre_) <= dist) {return true;}
	
	else{return false;}
	
}

bool Player::collide_with(Obstacle o, double marge) {
	
	marge += COEF_RAYON_JOUEUR;
	Point p1(o.colonne() - marge, o.ligne() - marge);
	Point p3(o.colonne() + marge + 1, o.ligne() + marge + 1);
	
	
	Rectangle r_ext(p1, p3);
	
	if (!(r_ext.appartient(centre_))) {return false;}
	
	p1.x(o.colonne() - marge);
	p1.y(o.ligne());
	p3.x(o.colonne() + 1 + marge);
	p3.y(o.ligne() + 1);
		
	Rectangle r_marge_vert (p1, p3); //rectangle contenant l'obstacle et 
		                             //les marges verticales
	p1.x(o.colonne());
	p1.y(o.ligne() - marge);
	p3.x(o.colonne() + 1);
	p3.y(o.ligne() + 1 + marge);
		
	Rectangle r_marge_horiz (p1, p3);//rectangle contenant l'obstacle et 
		                             //les marges horizontales
		
	if (r_marge_vert.appartient(centre_)) {return true;}
	if (r_marge_horiz.appartient(centre_)) {return true;}
		
	Point coin1(o.colonne(), o.ligne());       //4 coins de l'obstacle
	Point coin2(o.colonne(), o.ligne() + 1);
	Point coin3(o.colonne() + 1, o.ligne());
	Point coin4(o.colonne() + 1, o.ligne() + 1);
		
	if ((ecart(coin1, centre_)) < (marge)) {return true;}
	if ((ecart(coin2, centre_)) < (marge)) {return true;}
	if ((ecart(coin3, centre_)) < (marge)) {return true;}
	if ((ecart(coin4, centre_)) < (marge)) {return true;}	
	
	return false;
}


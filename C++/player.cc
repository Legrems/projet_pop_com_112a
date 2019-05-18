#include "player.h"
#include <vector>

using namespace std;


Player::Player()
		: nbT_(0)
		{}
Player::Player(Point c, int n, double co, int nc)
		: centre_(c), nbT_(n), count_(co), nb_cells_(nc),
		c_dessin_(c.x() * SIDE / nc - DIM_MAX,
		 		 -(DIM_MAX - c.y() * SIDE / nc))
		{}		

void Player::centre(Point c) {centre_ = c;}
Point Player::centre() {return centre_;}

void Player::nbT(int n) {nbT_ = n;}
int Player::nbT() {return nbT_;}

void Player::count(double c) {count_ = c;}
double Player::count() {return count_;}

void Player::c_dessin(Point c){c_dessin_ = c;}
Point Player::c_dessin(){return c_dessin_;}

void Player::nb_cells(int n){nb_cells_ = n;}
int Player::nb_cells(){return nb_cells_;}


bool Player::collide_with(Player p, double marge) {
	double dist = 2 * COEF_RAYON_JOUEUR + marge;
	
	if (ecart(p.centre(), centre_) < dist) {return true;}
	
	else{return false;}
	
}

bool Player::collide_with(Ball b, double marge) {
	double dist = COEF_RAYON_JOUEUR + marge + COEF_RAYON_BALLE;

	if (ecart(b.centre(), centre_) < dist) {return true;}
	
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

void Player::move(double move_x, double move_y)
{
	double cell = SIDE / nb_cells_;
	centre_.move(move_x / cell, - move_y / cell);
	c_dessin_.move(move_x, - move_y);
}

Rond Player::rond()
{
	Couleur couleur1(0, 0, 0), couleur2(1, 0, 0), couleur3(1, 0.5, 0);
	Couleur couleur4(1, 1, 0), couleur5(0, 1, 0);
	Couleur couleur[5] = {couleur1, couleur2, couleur3, couleur4, 
		                  couleur5};
	double cell = SIDE / nb_cells_;
	double frac = count_ / MAX_COUNT;
	
	Rond r(c_dessin_, COEF_RAYON_JOUEUR * cell, couleur[nbT_], frac);
	return r;
}
		                  
int Player::target(vector<Player> &liste_joueur){
	int target = 0;
	double dist_to_target = 3 * DIM_MAX;
	
	for (uint i(0); i < liste_joueur.size(); i++)
	{
		double distance = ecart(centre_, liste_joueur[i].centre());
		
		if (distance > COEF_MARGE_JEU)
		{
			if (distance < dist_to_target)
			{
				target = i;
				dist_to_target = ecart(centre_, liste_joueur[i].centre());
				//dist_to_target = distance;
			}
			
		}
	}
	
	return target;
		
}
	
	
bool Player::contact(Player p){
	double dist = ecart(centre_, p.centre());
	double cell = SIDE / nb_cells_;
	if (dist == (2*COEF_RAYON_JOUEUR+COEF_MARGE_JEU)*cell)
	{
		return true;
	}
	return false;
}
	
void Player::add_count(){	
	count_++;
}
	
bool Player::collide_with(std::vector<Ball> &Balls)
{
	double marge = COEF_MARGE_JEU;
	for (uint i(0); i < Balls.size(); i++)
	{
		if (this->collide_with(Balls[i],marge)){return true;}
	}
	return false;
}
	
	
void Player::shot(Player p, vector<Ball> &Balls)
{
	double vect_x, vect_y, norm_vect, angle, x, y;
	
	vect_x = p.centre().x() - centre_.x();
	vect_y = p.centre().y() - centre_.y();
	norm_vect = sqrt((vect_x * vect_x) + (vect_y * vect_y));
	
	vect_x /= norm_vect;
	vect_y /= norm_vect;
	
	x = centre_.x();
	x += vect_x * (COEF_MARGE_JEU+COEF_RAYON_BALLE+COEF_RAYON_JOUEUR);
	y = centre_.y();
	y += vect_y * (COEF_MARGE_JEU+COEF_RAYON_BALLE+COEF_RAYON_JOUEUR);
	
	if(vect_x == 0)
	{
		if(vect_y < 0){ angle =  M_PI / 2;}
		if(vect_y >0){angle = 3 * M_PI / 2;}
	}
	else
	{
		angle = -atan(vect_y/vect_x);
		if (vect_x < 0){angle += M_PI;}
	}
	Point c(x,y);
	Ball b(c,angle,nb_cells_);
	Balls.push_back(b);
}
		
		
		
		
		

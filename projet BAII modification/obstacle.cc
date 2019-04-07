#include "obstacle.h"

using namespace std;


Obstacle::Obstacle()
		: ligne_(0),colonne_(0)
		{}
Obstacle::Obstacle(int l, int c)
		: ligne_(l), colonne_(c),x_((c-(nbCells/2))*SIDE/nbCells),
		y_((nbCells/2-l)*SIDE/nbCells)
		{}		
		
void Obstacle::ligne(int l){ligne_ = l;}
int Obstacle::ligne(){return ligne_;}

void Obstacle::colonne(int c){colonne_ = c;}
int Obstacle::colonne(){return colonne_;}

double Obstacle::x(){return x_;}
void Obstacle::x(double x){x_ = x;}

double Obstacle::y(){return y_;}
void Obstacle::y(double y){y_ = y;}

bool Obstacle::collide_with(Player p, double marge){
	
	double cell = SIDE/nbCells;
	marge =(marge+COEF_RAYON_JOUEUR)*cell;
	Point p1(x_-marge,y_+marge);
	Point p3(x_+marge+cell,y_-marge-cell);
	
	Rectangle r_ext(p1,p3);
	
	if (!(r_ext.appartient(p.centre()))){return false;}
	
	p1.x(x_-marge);
	p1.y(y_);
	p3.x(x_+cell+marge);
	p3.y(y_-cell);
		
	Rectangle r_marge_vert (p1,p3);//rectangle contenant l'obstacle et 
		                            //les marges verticales
	p1.x(x_);
	p1.y(y_+marge);
	p3.x(x_+cell);
	p3.y(y_-cell-marge);
		
	Rectangle r_marge_horiz (p1,p3); //rectangle contenant l'obstacle et 
		                             //les marges horizontales
		
	if (r_marge_vert.appartient(p.centre())){return true;}
	if (r_marge_horiz.appartient(p.centre())){return true;}
		
	Point coin1(x_,y_);  //4 coins de mon obstacles
	Point coin2(x_,y_-cell);
	Point coin3(x_+cell,y_);
	Point coin4(x_+cell,y_-cell);
		
	if ((ecart(coin1, p.centre()))<(marge)){return true;}
	if ((ecart(coin2, p.centre()))<(marge)){return true;}
	if ((ecart(coin3, p.centre()))<(marge)){return true;}
	if ((ecart(coin4, p.centre()))<(marge)){return true;}	
	
	return false;
}


		
bool Obstacle::collide_with(Ball p, double marge){
	
	double cell = SIDE/nbCells;
	marge =(marge+COEF_RAYON_BALLE)*cell;
	Point p1(x_-marge,y_+marge);
	Point p3(x_+marge+cell,y_-marge-cell);
	
	Rectangle r_ext(p1,p3);
	
	if (!(r_ext.appartient(p.centre()))){return false;}
	
	p1.x(x_-marge);
	p1.y(y_);
	p3.x(x_+cell+marge);
	p3.y(y_-cell);
		
	Rectangle r_marge_vert (p1,p3);//rectangle contenant l'obstacle et 
		                            //les marges verticales
	p1.x(x_);
	p1.y(y_+marge);
	p3.x(x_+cell);
	p3.y(y_-cell-marge);
		
	Rectangle r_marge_horiz (p1,p3); //rectangle contenant l'obstacle et 
		                             //les marges horizontales
		
	if (r_marge_vert.appartient(p.centre())){return true;}
	if (r_marge_horiz.appartient(p.centre())){return true;}
		
	Point coin1(x_,y_);  //4 coins de mon obstacles
	Point coin2(x_,y_-cell);
	Point coin3(x_+cell,y_);
	Point coin4(x_+cell,y_-cell);
		
	if ((ecart(coin1, p.centre()))<(marge)){return true;}
	if ((ecart(coin2, p.centre()))<(marge)){return true;}
	if ((ecart(coin3, p.centre()))<(marge)){return true;}
	if ((ecart(coin4, p.centre()))<(marge)){return true;}	
	
	return false;
}

	
bool Obstacle::collide_with(Obstacle o, double marge){
	if ((ligne_ == o.ligne())&&(colonne_ == o.colonne())){
		return true;
	}
	return false;
}

bool Obstacle::collide_with(Obstacle o){
	if ((ligne_ == o.ligne())&&(colonne_ == o.colonne())){
		return true;
	}
	return false;
}



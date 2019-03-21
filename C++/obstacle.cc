#include "obstacle.h"

using namespace std;

void Obstacle::ligne(int l){ligne_ = l;}
int Obstacle::ligne(){return ligne_;}

void Obstacle::colonne(int c){colonne_ = c;}
int Obstacle::colonne(){return colonne_;}

bool Obstacle::collide_with(Player p, double marge){
	
	marge +=COEF_RAYON_JOUEUR;
	Point p1(colonne_-marge,ligne_-marge);
	Point p3(colonne_+marge+1,ligne_+marge+1);
	
	Rectangle r_ext(p1,p3);
	
	if (!(r_ext.appartient(p.centre()))){return false;}
	
	p1.x(colonne_-marge);
	p1.y(ligne_);
	p3.x(colonne_+1+marge);
	p3.y(ligne_+1);
		
	Rectangle r_marge_vert (p1,p3); //rectangle contenant l'obstacle et 
		                            //les marges verticales
	p1.x(colonne_);
	p1.y(ligne_-marge);
	p3.x(colonne_+1);
	p3.y(ligne_+1+marge);
		
	Rectangle r_marge_horiz (p1,p3); //rectangle contenant l'obstacle et 
		                             //les marges horizontales
		                             
	if (r_marge_vert.appartient(p.centre())){return true;}
	if (r_marge_horiz.appartient(p.centre())){return true;}
		
	Point coin1(colonne_,ligne_);   //4 coins de mon obstacles
	Point coin2(colonne_,ligne_+1);
	Point coin3(colonne_+1,ligne_);
	Point coin4(colonne_+1,ligne_+1);
		
	if ((ecart(coin1, p.centre()))<(marge)){return true;}
	if ((ecart(coin2, p.centre()))<(marge)){return true;}
	if ((ecart(coin3, p.centre()))<(marge)){return true;}
	if ((ecart(coin4, p.centre()))<(marge)){return true;}	
	
	return false;
}


		
bool Obstacle::collide_with(Ball p, double marge){
	marge +=COEF_RAYON_BALLE;
	Point p1(colonne_-marge,ligne_-marge);
	Point p3(colonne_+marge+1,ligne_+marge+1);
	
	Rectangle r_ext(p1,p3);
	
	if (!(r_ext.appartient(p.centre()))){return false;}
	
	p1.x(colonne_-marge);
	p1.y(ligne_);
	p3.x(colonne_+1+marge);
	p3.y(ligne_+1);
		
	Rectangle r_marge_vert (p1,p3);//rectangle contenant l'obstacle et 
		                            //les marges verticales
	p1.x(colonne_);
	p1.y(ligne_-marge);
	p3.x(colonne_+1);
	p3.y(ligne_+1+marge);
		
	Rectangle r_marge_horiz (p1,p3); //rectangle contenant l'obstacle et 
		                             //les marges horizontales
		
	if (r_marge_vert.appartient(p.centre())){return true;}
	if (r_marge_horiz.appartient(p.centre())){return true;}
		
	Point coin1(colonne_,ligne_);  //4 coins de mon obstacles
	Point coin2(colonne_,ligne_+1);
	Point coin3(colonne_+1,ligne_);
	Point coin4(colonne_+1,ligne_+1);
		
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



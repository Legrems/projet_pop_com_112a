#include "tools.h"
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

bool est_entre(double a, double b, double c)
{
	double list[3] = {a, b, c};
	sort(list, list+3);
	if (list[1] == a){return true;}
	return false;
}
		
		
		
Couleur::Couleur (double r, double g, double b)
		: red_(r), green_(g), blue_(b)
		{}
		
void Couleur::red(double r){red_ = r;}
double Couleur::red(){return red_;}
		
void Couleur::green(double g){green_ = g;}
double Couleur::green(){return green_;}
		
void Couleur::blue(double b){blue_ = b;}
double Couleur::blue(){return blue_;}


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

void Point::move(double new_x, double new_y){
	x_ += new_x;
	y_ += new_y;
}


Rectangle::Rectangle(Point p1,Point p2, double largeur)
		:c1_(0,0),c2_(0,0),c3_(0,0),c4_(0,0)
{
	
	double a = p2.x()-p1.x();  //vecteur qui relier les 2 points
	double b = p2.y()-p1.y();  
	
	double norme_vect_perp = sqrt((b*b)+(a*a));
	
	double vect_perp_x = b/norme_vect_perp;
	double vect_perp_y = -a/norme_vect_perp;
	
	vect_perp_x *= largeur/2;
	vect_perp_y *= largeur/2;
	
	Point c1(p1.x()-vect_perp_x,p1.y()-vect_perp_y);
	Point c2(p1.x()+vect_perp_x,p1.y()+vect_perp_y);
	Point c3(p2.x()-vect_perp_x,p2.y()-vect_perp_y);
	Point c4(p2.x()+vect_perp_x,p2.y()+vect_perp_y);
	
	c1_ = c1; c2_ = c2; c3_ = c3; c4_ = c4;
	
	
}

Droite::Droite()
		:p1_(0,0), p2_(0,0)
		{}
		
Droite::Droite(Point p1, Point p2)
		:p1_(p1),p2_(p2)
		{}
		
		
Point Droite::p1(){return p1_;}
Point Droite::p2(){return p2_;}
bool Droite::vertical(){return vertical_;}
double Droite::pente(){return pente_;}
double Droite::hauteur(){return hauteur_;}


void Droite::p1(Point p){p1_ = p;}
void Droite::p2(Point p){p2_ = p;}
		
void Droite::set_equation()
{
	double x = p2_.x() - p1_.x();
	double y = p2_.y() - p1_.y();
	
	if (x == 0)
	{
		vertical_ = true;
		return;
	}
	
	vertical_ = false;
	pente_ = y/x;
	hauteur_ = p1_.y() - pente_ * p1_.x();
	return;
}

bool Droite::collide_with(Droite d)
{	
	d.set_equation();
	set_equation();
	
	double d1_x1 = p1_.x(), d1_x2 = p2_.x(), d2_x1 = d.p1().x();
	double d2_x2 = d.p2().x(), d1_y1 = p1_.y(), d1_y2 = p2_.y();
	double  d2_y1 = d.p1().y(), d2_y2 = d.p2().y();
	
	if (vertical_){
		if (est_entre(d1_x1,d2_x1,d2_x2)){
			if (d.vertical()){
				if ((est_entre(d1_y1,d2_y1,d2_y2))||
				   (est_entre(d1_y2,d2_y1,d2_y2))){return true;}
				else{return false;}}
			double y = d.pente()*d1_x1+d.hauteur();
			if ((est_entre(y,d1_y1,d1_y2))&&(est_entre(y,d2_y1,d2_y2))){
				return true;}
				else{ return false;}}}
		
	if(d.vertical()){
		if (est_entre(d2_x1,d1_x1,d1_x2)){
			double y = pente_*d2_x1+hauteur_;
			if ((est_entre(y,d2_y1,d2_y2))&&(est_entre(y,d1_y1,d1_y2))){
				return true;}}
		else{return false;}}
		
	if (d.pente()==pente_){
		if((hauteur_ == d.hauteur())&&((est_entre(d1_y1,d2_y1,d2_y2))||
		  (est_entre(d1_y2,d2_y1,d2_y2)))){return true;}
		else {return false;}}
		
	double x = (d.hauteur()-hauteur_)/(pente_-d.pente());
	
	if ((est_entre(x,d1_x1,d1_x2))&&(est_entre(x,d2_x1,d2_x2))){
		return true;}
		else {return false;}
	return false;
}




Form::Form()
		:couleur_(0,0,0)
		{}
Form::Form(Couleur c)
		:couleur_(c)
		{}
		
		
void Form::couleur(Couleur c){couleur_ = c;}
Couleur Form::couleur(){return couleur_;}



Rectangle::Rectangle ()
		: Form(), c1_(0,0)
		{}
		
Rectangle::Rectangle (Point a, Point b)
		: Form(), c1_(a), c2_(a.x(),b.y()),c3_(b),c4_(a.y(),b.x())
		{}
		
Rectangle::Rectangle (Point a, Point b, Point c, Point d)
		: Form(), c1_(a), c2_(b), c3_(c), c4_(d)
		{}
		
Rectangle::Rectangle (Point a, double h, double l, Couleur c)
		: Form(c), c1_(a), c2_(a.x()+l,a.y()), c3_(a.x(),a.y()+h),
		  c4_(a.x()+l,a.y()+h),  hauteur_(h), largeur_(l)
		{}
		

Point Rectangle::c1(){return c1_;}
Point Rectangle::c2(){return c2_;}
Point Rectangle::c3(){return c3_;}
Point Rectangle::c4(){return c4_;}
double Rectangle::largeur(){return largeur_;}
double Rectangle::hauteur(){return hauteur_;}


bool Rectangle::appartient(Point a)
{
	double x[5] = {c1_.x(),c2_.x(),c3_.x(),c4_.x(),a.x()};
	double y[5] = {c1_.y(),c2_.y(),c3_.y(),c4_.y(),a.y()};
	
	sort(x,x+5);
	sort(y,y+5);
		
	if ((x[2]==a.x())&&(y[2]==a.y())){return true;}
	else {return false;}
}

bool Rectangle::collide_with(Droite d)
{
	Droite d2(c1_,c2_), d3(c1_,c3_), d4(c1_,c4_), d5(c2_,c3_);
	Droite d6(c2_,c4_),d7(c3_,c4_);
	if (d.collide_with(d2)){return true;}
	if (d.collide_with(d3)){return true;}
	if (d.collide_with(d4)){return true;}
	if (d.collide_with(d5)){return true;}
	if (d.collide_with(d6)){return true;}
	if (d.collide_with(d7)){return true;}
	return false;
}
	
	


bool Rectangle::collide_with(Rectangle rect)
{
	Droite d1(c1_,c2_), d2(c1_,c3_), d3(c1_,c4_), d4(c2_,c3_);
	Droite d5(c2_,c4_),d6(c3_,c4_);
	
	if (rect.collide_with(d1)){return true;}
	if (rect.collide_with(d2)){return true;}
	if (rect.collide_with(d3)){return true;}
	if (rect.collide_with(d4)){return true;}
	if (rect.collide_with(d5)){return true;}
	if (rect.collide_with(d6)){return true;}
	
	return false;
	
}
				
	
		
Rond::Rond(Point p, double r, Couleur c)
		: Form(c), centre_(p), rayon_(r), fraction_(0)
		{}
		
Rond::Rond(Point p, double r, Couleur c,double f)
		: Form(c), centre_(p), rayon_(r), fraction_(f)
		{}
		
void Rond::centre(Point p){centre_ = p;}
Point Rond::centre(){return centre_;}

void Rond::rayon(double r){rayon_ = r;}
double Rond::rayon(){return rayon_;}

void Rond::fraction(double f){fraction_ = f;}
double Rond::fraction(){return fraction_;}


		
double ecart(Point a, Point b){
	double d(0);
	double d_x = a.x()-b.x();
	double d_y = a.y()-b.y();
	
	d = sqrt((d_x*d_x)+(d_y*d_y));
	return d;
}

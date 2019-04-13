#include "tools.h"
#include <cmath>
#include <algorithm>
using namespace std;

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

Form::Form()
		:couleur_(0,0,0)
		{}
Form::Form(Couleur c)
		:couleur_(c)
		{}
		
		
void Form::couleur(Couleur c){couleur_ = c;}
Couleur Form::couleur(){return couleur_;}



Rectangle::Rectangle ()
		: Form(), p1_(0,0)
		{}
		
Rectangle::Rectangle (Point a, Point b)
		: Form(), p1_(a), p2_(a.x(),b.y()),p3_(b),p4_(a.y(),b.x())
		{}
		
Rectangle::Rectangle (Point a, Point b, Point c, Point d)
		: Form(), p1_(a), p2_(b), p3_(c), p4_(d)
		{}
		
Rectangle::Rectangle (Point a, double h, double l, Couleur c)
		: Form(c), p1_(a), hauteur_(h), largeur_(l)
		{}
		

Point Rectangle::c1(){return p1_;}
Point Rectangle::c2(){return p2_;}
Point Rectangle::c3(){return p3_;}
Point Rectangle::c4(){return p4_;}
double Rectangle::largeur(){return largeur_;}
double Rectangle::hauteur(){return hauteur_;}


bool Rectangle::appartient(Point a)
{
	double x[5] = {p1_.x(),p2_.x(),p3_.x(),p4_.x(),a.x()};
	double y[5] = {p1_.y(),p2_.y(),p3_.y(),p4_.y(),a.y()};
	
	sort(x,x+5);
	sort(y,y+5);
		
	if ((x[2]==a.x())&&(y[2]==a.y())){return true;}
	else {return false;}
}
		
Rond::Rond(Point p, double r, Couleur c)
		: Form(c), centre_(p), rayon_(r)
		{}
		
void Rond::centre(Point p){centre_ = p;}
Point Rond::centre(){return centre_;}

void Rond::rayon(double r){rayon_ = r;}
double Rond::rayon(){return rayon_;}


Arc::Arc(double r_ext, double r_int, double f, Couleur c)
		: Form(c), rayon_ext_(r_ext), rayon_int_(r_int), fraction_(f)
		{}
		
void Arc::rayon_ext(double r){rayon_ext_ = r;}
double Arc::rayon_ext(){return rayon_ext_;}

void Arc::rayon_int(double r){rayon_int_ = r;}
double Arc::rayon_int(){return rayon_int_;}

void Arc::fraction(double f){fraction_ = f;}
double Arc::fraction(){return fraction_;}



		
double ecart(Point a, Point b){
	double d(0);
	double d_x = a.x()-b.x();
	double d_y = a.y()-b.y();
	
	d = sqrt((d_x*d_x)+(d_y*d_y));
	return d;
}

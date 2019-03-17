#include "player.h"
#include "tools.h"
#include "ball.h"
#include <iostream>
using namespace std;

int main(){
	Point c(3,4);
	
	
	Player p(c,1.0,5);
	
	
	Point a = p.centre();
	
	Ball b(c,0.25);
	
	
	Point d =b.centre();
	
	cout<<a.x()<<endl;
	cout<<d.y()<<endl;
	
	Point p1(0,0);
	Point p3(3,4);
	Point p2(0,4);
	Point p4(3,0);
	
	Rectangle r(p1,p2,p3,p4);
	
	Point t1(0,0);
	Point t2(10,10);
	Point t3(1,1);
	
	if (r.appartient(t1)){cout<<"t1 est dans r"<<endl;};
	if (r.appartient(t2)){cout<<"t2 est dans r"<<endl;};
	if (r.appartient(t3)){cout<<"t3 est dans r"<<endl;};
	
	
	
	return 0;
}

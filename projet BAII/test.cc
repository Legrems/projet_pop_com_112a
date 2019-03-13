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
	return 0;
}

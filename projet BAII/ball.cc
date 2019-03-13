#include "ball.h"

using namespace std;

void Ball::centre(Point c){centre_ = c;}
Point Ball::centre(){return centre_;}

void Ball::angle(double a){angle_ = a;}
double Ball::angle(){return angle_;}

#include "player.h"

using namespace std;

void Player::centre(Point c){centre_ = c;}
Point Player::centre(){return centre_;}

void Player::nbT(int n){nbT_ = n;}
int Player::nbT(){return nbT_;}

void Player::count(double c){count_ = c;}
double Player::count(){return count_;}

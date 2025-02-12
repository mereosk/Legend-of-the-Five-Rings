#ifndef FOLLOWER_H
#define FOLLOWER_H

#include "Card.hpp"

class Follower: public GreenCard{
public:
  Follower(string inpName,int enu);
  ~Follower();
  void print();
  int getType();
  friend ostream &operator<<(ostream &left,const Follower &right);
private:
};

#endif

#ifndef ITEM_H
#define ITEM_H

#include "Card.hpp"

class Item: public GreenCard{
public:
  Item(string inpName,int enu);
  ~Item();
  void print();
  int getType();
  friend ostream &operator<<(ostream &left,const Item &right);
private:
  int durability;
};

#endif

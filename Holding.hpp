#ifndef HOLDING_H
#define HOLDING_H

#include "Card.hpp"

class Holding: public BlackCard{
public:
  Holding(string inpName,int enu);
  ~Holding();
  void print();
  void setInitialDefence(int id);
  int getType();
  virtual int getHarvestValue();
  void sethV(int x);
  void setuH();
  void setsH();
  int getsH();
  int gethV();
  int getuH();
  friend ostream &operator<<(ostream &left,const Holding &right);
protected:
  int harvestValue;
  bool upperHolding;
  bool subHolding;
};

class Stronghold: public Holding{
public:
  Stronghold(string inpNam,int enu);
  ~Stronghold();
  void print();
  int getHonour()const;
  int getMoney()const;
  int getInitialDefense()const;
  friend ostream &operator<<(ostream &left,const Stronghold &right);
private:
  int honour;
  int money;
  int initialDefense;
};

#endif

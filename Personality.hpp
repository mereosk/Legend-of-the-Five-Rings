#ifndef PERSONALITY_H
#define PERSONALITY_H

#include <list>
#include "Card.hpp"

class Personality: public BlackCard{
public:
  Personality(string inpName,int enu);
  ~Personality();
  void print();
  void setInitialDefence(int id);
  int getLimit()const;
  int getAttack()const;
  int getDefence()const;
  int getFollAndItemsSize();
  int getType();
  void changeTap();
  bool equip(GreenCard *card);
  void upgradeStats(int val);
  void dishonour();
  bool checkForSeppuku();
  void dead();
  friend ostream &operator<<(ostream &left,const Personality &right);
private:
  int attack;
  int defence;
  int honour;
  bool isDead;
  list<GreenCard *>* follAndItems;
  int limit;
};

#endif

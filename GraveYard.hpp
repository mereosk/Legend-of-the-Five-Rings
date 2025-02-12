#ifndef GRAVEYARD_H
#define GRAVEYARD_H

#include <list>
#include "Card.hpp"
#include "TypeConverter.hpp"

class GraveYard{
public:
  GraveYard();
  ~GraveYard();
  void printGreenDead();
  void printBlackDead();
  void buryGreenCard(GreenCard *gc);
  void buryBlackCard(BlackCard *bc);
  list<GreenCard *>*  getGreenDead()const;
  list<BlackCard *>*  getBlackDead()const;
private:
  list<GreenCard *>* greenDead;
  list<BlackCard *>* blackDead;
};

#endif

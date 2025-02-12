#ifndef CARDS_H
#define CARDS_H

#include <string>

using namespace std;

enum Personalities{DEFENDER, ATTACKER, SHOGUN, CHANCELLOR, CHAMPION};

enum Holdings{SOLO, PLAIN, FARMS, MINE, GOLD_MINE, CRYSTAL_MINE, STRONGHOLD};

enum Followers{FOOTSOLDIER, ARCHER, SIEGER, CAVALRY, NAVAL, BUSHIDO};

enum Items{KATANA, BOW, SPEAR, NINJATO, WAKIZASHI};

enum components{PERSONALITY = 1, HOLDING, FOLLOWER, ITEM};

class Card{
public:
  Card(string inpName);
  ~Card();
  bool getIsTapped();
  virtual void changeTap();
  string getName();
  int getCost()const;
protected:
  string name;
  int cost;
  bool isTapped;
};

class GreenCard: public Card{
public:
  GreenCard(string inpName);
  virtual ~GreenCard();
  virtual void print() = 0;
  virtual int getType() = 0;
  int getMinimumHonour()const;
  int getAttackBonus()const;
  int getDefenseBonus()const;
  int getEffectBonus()const;
  int getEffectCost()const;
  void upgrade();
protected:
  int attackBonus;
  int defenceBonus;
  int minimumHonour;
  string cardText;
  int effectBonus;
  int effectCost;
};

class BlackCard: public Card{
public:
  BlackCard(string inpName);
  virtual ~BlackCard();
  virtual void print() = 0;
  virtual int getType() = 0;
  int getInitialDefense()const;
  bool getIsRevealed()const;
  virtual void setInitialDefence(int id);
  void changeReveal();
  void reveal();
protected:
  int initialDefense;
  bool isRevealed;
};

#endif

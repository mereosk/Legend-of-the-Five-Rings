#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <list>
#include <vector>
#include <string>
#include <iostream>

#include "Card.hpp"
#include "Holding.hpp"
#include "Personality.hpp"
#include "DeckBuilder.hpp"
#include "GraveYard.hpp"

using namespace std;

const int maxHand = 6;

class Player{
public:
  Player(string inName);
  ~Player();
  int getHonour()const;
  int getMoney()const;
  string getName()const;
  int getNumberOfProvinces()const;
  int getNumberOfHand()const;
  BlackCard * getProvinces(int pos)const;
  GraveYard * getGraveYard()const;
  void printHand();
  void revealProvinces();
  void printProvinces();
  void printArmy();
  void printArena();
  void printHoldings();
  void untapEverything();
  void drawFateCard();
  void discardFateCards();
  void discardFateCards(int pos);
  void pushArmyReplaceProvince(int pos);
  void pushHoldingReplaceProvince(int pos);
  int getArmySize();
  int getHoldinSize();
  Holding *getHoldingFigure(int pos);
  Personality *getArmyFigure(int pos);
  GreenCard *getHandFigure(int pos);
  void buyGreenCard(GreenCard *gc,int position);
  void tapHoldingsForBuy(int value);
  bool checkUpgrade(GreenCard *gc);
  void passToArena(Personality *per,int pos);
  int collectAttackPoints();
  int collectDefencePoints();
  int collectDefencePoints(int posOfProv);  //Plus initial defense
  int destroyProvince(int posOfProv);
  void destroyAllArena();
  void destroyPartArena(int debt);
  void returnToArmy(bool checkWin);
  void makechain(Holding* mk);

private:
  GreenDeckBuilder fateDeck;
  BlackDeckBuilder dynastyDeck;
  vector<BlackCard *> provinces;
  int numberOfProvinces;
  vector<GreenCard *> hand;
  int numberOfHand;
  vector<Holding *> holdings;
  vector<Personality *> army;
  list<Personality *>* arena;
  Stronghold *strongHold;
  GraveYard *graveyard;
  int honour;
  int money;
  string name;
};

#endif

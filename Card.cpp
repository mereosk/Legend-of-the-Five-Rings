#include <iostream>

#include "Card.hpp"

using namespace std;

Card::Card(string inpName):
  name(inpName){
    isTapped=false;
    //cout<<"A card "<<name<<" constructed!"<<endl;
}

Card::~Card(){
  //cout<<"A card is destructed!"<<endl;
}

bool Card::getIsTapped(){
  return isTapped;
}

void Card::changeTap(){
  if(isTapped==true)
    isTapped=false;
  else
    isTapped=true;
}

string Card::getName(){
  return name;
}

int Card::getCost()const{
  return cost;
}


GreenCard::GreenCard(string inpName):
  Card(inpName){
  //cout<<"A GREEN card is constructed~"<<endl;
}


GreenCard::~GreenCard(){
  //cout<<"A GREEN card is destroyed~"<<endl;
}

int GreenCard::getMinimumHonour()const{
  return minimumHonour;
}

int GreenCard::getAttackBonus()const{
  return attackBonus;
}

int GreenCard::getDefenseBonus()const{
  return defenceBonus;
}

int GreenCard::getEffectBonus()const{
  return effectBonus;
}

int GreenCard::getEffectCost()const{
  return effectCost;
}

void GreenCard::upgrade(){
  attackBonus += effectBonus;
  defenceBonus += effectBonus;
}


BlackCard::BlackCard(string inpName):
  Card(inpName){
  isRevealed = false;
//  cout<<"A BLACK card is constructed~"<<endl;
}

BlackCard::~BlackCard(){
  //cout<<"A BLACK card is destroyed"<<endl;
}

void BlackCard::setInitialDefence(int id){
  initialDefense = id;
}

int BlackCard::getInitialDefense()const{
  return initialDefense;
}

void BlackCard::changeReveal(){
  if(isRevealed==true)
    isRevealed=false;
  else
    isRevealed=true;
}

void BlackCard::reveal(){
  if(!this->isRevealed)   //isRevealed == false
    this->changeReveal();
}

bool BlackCard::getIsRevealed()const{
  return isRevealed;
}

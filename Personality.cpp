#include <iostream>
#include "Personality.hpp"

using namespace std;

Personality::Personality(string inpName,int enu):
  BlackCard(inpName){
  isDead = false;
  follAndItems = new list<GreenCard *>();
  switch (enu){
    case 0:             //ATTACKER
      cost = 5;
      attack = 3;
      defence = 2;
      honour = 2;
      limit = 1;
      break;
    case 1:             //DEFENDER
      cost = 5;
      attack = 2;
      defence = 3;
      honour = 2;
      limit = 1;
      break;
    case 2:             //SHOGUN
      cost = 15;
      attack = 10;
      defence = 5;
      honour = 8;
      limit = 2;
      break;
    case 3:             //CHANCELLOR
      cost = 15;
      attack = 5;
      defence = 10;
      honour = 8;
      limit = 2;
      break;
    case 4:             //CHAMPION
      cost = 30;
      attack = 20;
      defence = 20;
      honour = 12;
      limit = 3;
      break;
    default:
      cout<<"Wrong input!"<<endl;
  }
  //cout<<"A Personality is constructedQ"<<endl;
}

Personality::~Personality(){
  list<GreenCard *>::iterator it;
	for (it = follAndItems->begin(); it != follAndItems->end();)
	{
    delete *it;
		follAndItems->remove(*it);
		it = follAndItems->begin();
	}
	delete follAndItems;
  //cout<<"A Personality is destroyed!"<<name<<endl;
}

void Personality::print(){
  cout<<"----"<<name<<"----"<<endl;
  cout<<"Cost = "<<cost<<" Attack = "<<attack;
  cout<<" Defence = "<<defence<<" Honour = "<<honour<<endl;
  if(isDead)
    cout<<name<<" is dead"<<endl;
  else
    cout<<name<<" is alive"<<endl;

  if(isTapped)
    cout<<name<<" is tapped"<<endl;
  else
    cout<<name<<" is untapped"<<endl;

  if(isRevealed)
    cout<<name<<" is revealed"<<endl;
  else
    cout<<name<<" is hidden"<<endl;

  list<GreenCard*>::iterator it;

  if(follAndItems->size()!=0){
    cout<<"His followers and items!"<<endl;
    for(it = follAndItems->begin() ; it != follAndItems->end() ; it++)
      (*it)->print();
    cout<<endl;
  }
  else
    cout<<"He does not have followers nor items!"<<endl;
}

void Personality::setInitialDefence(int id){
  initialDefense = id;
}

int Personality::getLimit()const{
  return limit;
}

int Personality::getAttack()const{
  return attack;
}

int Personality::getDefence()const{
  return defence;
}

int Personality::getFollAndItemsSize(){
  return follAndItems->size();
}

int Personality::getType(){
  return PERSONALITY;
}

void Personality::changeTap(){
  list<GreenCard*>::iterator it;

  if(isTapped==true)
    isTapped=false;
  else
    isTapped=true;

  for(it = follAndItems->begin() ; it != follAndItems->end() ; it++)
    (*it)->changeTap();
}

bool Personality::equip(GreenCard *card){
  if(follAndItems->size()==limit){
    cout<<"Reached the limit of followers and items"<<endl;
    return false;
  }
  if(honour<card->getMinimumHonour()){
    cout<<"Not enough honour"<<endl;
    return false;
  }

  attack += card->getAttackBonus();
  defence += card->getDefenseBonus();
  follAndItems->push_back(card);

  this->print();
  return true;
}

void Personality::upgradeStats(int val){
  attack += val;
  defence += val;
}

void Personality::dishonour(){
  honour--;
}

bool Personality::checkForSeppuku(){
  if(!honour){
    cout<<name<<" will now perform seppuku in order to save the honour of his family!"<<endl;
    return true;
  }
  return false;
}

void Personality::dead(){
  isDead = true;
}

ostream &operator<<(ostream &left,const Personality &right){
  left<<"----"<<right.name<<"----"<<endl;
  left<<"Cost = "<<right.cost<<" Attack = "<<right.attack;
  left<<" Defence = "<<right.defence<<" Honour = "<<right.honour<<endl;
  if(right.isDead)
    left<<right.name<<" is dead"<<endl;
  else
    left<<right.name<<" is alive"<<endl;

  return left;
}

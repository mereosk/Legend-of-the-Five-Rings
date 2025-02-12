#include <iostream>
#include "Holding.hpp"

using namespace std;

Holding::Holding(string inpName,int enu):
  BlackCard(inpName){
  switch (enu){
    case 0:             //SOLO
      cost = 2;
      harvestValue = 2;
      break;
    case 1:             //PLAIN
      cost = 2;
      harvestValue = 2;
      break;
    case 2:             //FARMS
      cost = 3;
      harvestValue = 4;
      break;
    case 3:             //MINE
      cost = 5;
      harvestValue = 3;
      break;
    case 4:             //GOLD_MINE
      cost = 7;
      harvestValue = 5;
      break;
    case 5:             //CRYSTAL_MINE
      cost = 12;
      harvestValue = 6;
      break;
    case 6:
      cost = 0;
      harvestValue = 5; //STRONGHOLD
      break;
    default:
      cout<<"Wrong input!"<<endl;
  }
  //cout<<"A Holding is constructed"<<endl;
}

Holding::~Holding(){
  //cout<<"A Holding is being destroyed"<<name<<endl;
}

void Holding::print(){
  cout<<"----"<<name<<"----"<<endl;
  cout<<"Cost = "<<cost<<" ";
  cout<<"Harvest value = "<<harvestValue<<endl;
  if(isTapped)
    cout<<name<<" is tapped"<<endl;
  else
    cout<<name<<" is untapped"<<endl;

  if(isRevealed==true)
    cout<<name<<" is revealed"<<endl;
  else
    cout<<name<<" is hidden"<<endl;
}

void Holding::setInitialDefence(int id){
  initialDefense = id;
}

int Holding::getType(){
  return HOLDING;
}

int Holding::getHarvestValue(){
  return harvestValue;
}

int Holding::getuH(){
	return upperHolding;
}

int Holding::getsH(){
	return subHolding;
}

void Holding::sethV(int x){
	this->harvestValue+=x;
}

void Holding::setuH(){
	this->upperHolding=1;
}

void Holding::setsH(){
	this->subHolding=1;
}

int Holding::gethV(){
	return this->harvestValue;
}

ostream &operator<<(ostream &left,const Holding &right){
  left<<"----"<<right.name<<"----"<<endl;
  left<<"Harvest value = "<<right.harvestValue<<endl;

  return left;
}


Stronghold::Stronghold(string inpName,int enu):
  Holding(inpName,enu){
  honour = 5;
  money = 5;
  initialDefense = 5;

  changeReveal();
  //cout<<"Stronghold is constructed!"<<endl;
}

Stronghold::~Stronghold(){
  //cout<<"Stronghold is destroyed!"<<endl;
}

void Stronghold::print(){
  cout<<"----"<<name<<"----"<<endl;
  cout<<"  (STRONGHOLD)"<<endl;
  cout<<"Harvest value = "<<harvestValue<<" Honour of player = "<<honour;
  cout<<" Initial defense = "<<initialDefense;
  cout<<" Money of player = "<<money<<endl;
  if(isTapped)
    cout<<name<<" is tapped"<<endl;
  else
    cout<<name<<" is untapped"<<endl;

  if(isRevealed)
    cout<<name<<" is revealed"<<endl;
  else
    cout<<name<<" is hidden"<<endl;
}

int Stronghold::getHonour()const{
  return honour;
}

int Stronghold::getMoney()const{
  return money;
}

int Stronghold::getInitialDefense()const{
  return initialDefense;
}

// ostream &operator<<(ostream &left,const Stronghold &right){
//   left<<"----"<<right.name<<"----"<<endl;
//   left<<"Initial honour = "<<right.honour<<" Harvest = "<<right.money;
//   left<<" and Initial defence = "<<right.initialDefense<<endl;
//
//   return left;
// }

#include <iostream>
#include "Follower.hpp"

using namespace std;

Follower::Follower(string inpName,int enu):
  GreenCard(inpName){
  switch (enu){
    case 0:             //FOOTSOLDIER
      cost = 0;
      attackBonus = 2;
      defenceBonus = 0;
      minimumHonour = 1;
      effectBonus = 1;
      effectCost = 2;
      break;
    case 1:             //ARCHER
      cost = 0;
      attackBonus = 0;
      defenceBonus = 2;
      minimumHonour = 1;
      effectBonus = 1;
      effectCost = 2;
      break;
    case 2:             //SIEGER
      cost = 5;
      attackBonus = 3;
      defenceBonus = 3;
      minimumHonour = 2;
      effectBonus = 2;
      effectCost = 3;
      break;
    case 3:             //CAVALRY
      cost = 3;
      attackBonus = 4;
      defenceBonus = 2;
      minimumHonour = 3;
      effectBonus = 3;
      effectCost = 4;
      break;
    case 4:             //NAVAL
      cost = 3;
      attackBonus = 2;
      defenceBonus = 4;
      minimumHonour = 3;
      effectBonus = 3;
      effectCost = 4;
      break;
    case 5:             //BUSHIDO
      cost = 8;
      attackBonus = 8;
      defenceBonus = 8;
      minimumHonour = 6;
      effectBonus = 3;
      effectCost = 8;
      break;
    default:
      cout<<"Wrong input!"<<endl;
  }
  //cout<<"A Follower is constructed"<<endl;
}

Follower::~Follower(){
  //cout<<"A Follower is destroyed!"<<name<<endl;
}

void Follower::print(){
  cout<<"----"<<name<<"----"<<endl;
  cout<<"Cost = "<<cost<<" Bonus attack = "<<attackBonus;
  cout<<" Bonus defence = "<<defenceBonus<<" Minimum honour = ";
  cout<<minimumHonour<<" Bonus effect = "<<effectBonus;
  cout<<" Cost effect = "<<effectCost<<endl;
}

int Follower::getType(){
  return FOLLOWER;
}

ostream &operator<<(ostream &left,const Follower &right){
  left<<"----"<<right.name<<"----"<<endl;
  left<<"Cost = "<<right.cost<<" Bonus attack = "<<right.attackBonus;
  left<<" Bonus defence = "<<right.defenceBonus<<" Minimum honour = ";
  left<<right.minimumHonour<<" Bonus effect = "<<right.effectBonus;
  left<<" Cost effect = "<<right.effectCost<<endl;

  return left;
}

#include <iostream>
#include "Item.hpp"

using namespace std;

Item::Item(string inpName,int enu):
  GreenCard(inpName){
  switch (enu){
    case 0:             //KATANA
      cost = 0;
      attackBonus = 2;
      defenceBonus = 0;
      minimumHonour = 1;
      effectBonus = 1;
      effectCost = 2;
      durability = 3;
      break;
    case 1:             //SPEAR
      cost = 0;
      attackBonus = 0;
      defenceBonus = 2;
      minimumHonour = 1;
      effectBonus = 1;
      effectCost = 2;
      durability = 3;
      break;
    case 2:             //BOW
      cost = 2;
      attackBonus = 2;
      defenceBonus = 2;
      minimumHonour = 2;
      effectBonus = 3;
      effectCost = 4;
      durability = 5;
      break;
    case 3:             //NINJATO
      cost = 4;
      attackBonus = 3;
      defenceBonus = 3;
      minimumHonour = 3;
      effectBonus = 2;
      effectCost = 2;
      durability = 4;
      break;
    case 4:             //WAKIZASHI
      cost = 8;
      attackBonus = 5;
      defenceBonus = 5;
      minimumHonour = 3;
      effectBonus = 3;
      effectCost = 3;
      durability = 8;
      break;
    default:
      cout<<"Wrong input!"<<endl;
  }
  //cout<<"A Item is constructed"<<endl;
}

Item::~Item(){
  //cout<<"An Item is being destroyed!"<<name<<endl;
}

void Item::print(){
  cout<<"----"<<name<<"----"<<endl;
  cout<<"Cost = "<<cost<<" Bonus attack = "<<attackBonus;
  cout<<" Bonus defence = "<<defenceBonus<<" Minimum honour = ";
  cout<<minimumHonour<<" Bonus effect = "<<effectBonus;
  cout<<" Cost effect = "<<effectCost<<endl;
  cout<<" Durability = "<<durability<<endl;
}

int Item::getType(){
  return ITEM;
}

ostream &operator<<(ostream &left,const Item &right){
  left<<"----"<<right.name<<"----"<<endl;
  left<<"Cost = "<<right.cost<<" Bonus attack = "<<right.attackBonus;
  left<<" Bonus defence = "<<right.defenceBonus<<" Minimum honour = ";
  left<<right.minimumHonour<<" Bonus effect = "<<right.effectBonus;
  left<<" Cost effect = "<<right.effectCost<<endl;
  left<<" Durability = "<<right.durability<<endl;

  return left;
}

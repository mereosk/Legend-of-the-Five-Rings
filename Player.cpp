#include <iostream>
#include "Player.hpp"

using namespace std;

Player::Player(string inName):
  name(inName){
  arena = new list<Personality *>();

  int i;
  strongHold = new Stronghold("Takeshi",6);
  holdings.push_back(strongHold);

  money = strongHold->getMoney();           //Starting money
  honour = strongHold->getHonour();         //Starting honour

  fateDeck.createFateDeck();
  dynastyDeck.createDynastyDeck();

  numberOfProvinces = 4;
  for(i=0 ; i<numberOfProvinces ; i++){
    provinces.push_back(dynastyDeck.getBlack()->back());
    dynastyDeck.getBlack()->pop_back();
    provinces[i]->setInitialDefence(strongHold->getInitialDefense());
  }

  numberOfHand = 3;
  for(i=0 ; i<numberOfHand ; i++){
    hand.push_back(fateDeck.getGreen()->back());
    fateDeck.getGreen()->pop_back();
  }

  graveyard = new GraveYard();

  //cout<<"Player is created"<<endl;
}

Player::~Player(){
  int i;

  delete graveyard;

  for(i=0 ; i<army.size() ; i++)
    delete army[i];

  for(i=0 ; i<numberOfHand ; i++)
    delete hand[i];

  for(i=0 ; i<numberOfProvinces ; i++)
    delete provinces[i];

  delete strongHold;

  list<Personality *>::iterator it;

	for (it = arena->begin(); it != arena->end();)
	{
		delete *it;
		arena->remove(*it);
		it = arena->begin();
	}
	delete arena;
  //cout<<"Player is destroyed"<<endl;
}

int Player::getHonour()const{
  return honour;
}

int Player::getMoney()const{
  int mon=0;

  for(int i=0 ; i<holdings.size() ; i++)
    if(holdings[i]->getIsTapped() == false)
      mon += holdings[i]->getHarvestValue();

  return mon;
}

string Player::getName()const{
  return name;
}

int Player::getNumberOfProvinces()const{
  return numberOfProvinces;
}

int Player::getNumberOfHand()const{
  return numberOfHand;
}

BlackCard * Player::getProvinces(int pos)const{
  if(pos<0 || pos>=numberOfProvinces){
    cout<<"Wrong index"<<endl;
    return NULL;
  } //else
  return provinces[pos];
}

void Player::printHand(){
  cout<<endl<<name<<"'s hand:"<<endl;

  if(numberOfHand>0){
    for(int i=0 ; i<numberOfHand ; i++)
    hand[i]->print();
  }
  else
    cout<<"There are no cards in hand"<<endl;
}

GraveYard *Player::getGraveYard()const{
  return graveyard;
}

void Player::printProvinces(){
  cout<<endl<<name<<"'s provinces:"<<endl<<endl;

  for(int i=0 ; i<numberOfProvinces ; i++){
    provinces[i]->print();
    cout<<endl;
  }
}

void Player::printArmy(){
  cout<<endl<<name<<"'s army:"<<endl;

  if(army.size()!=0)
    for(int i=0 ; i<army.size() ; i++){
      army[i]->print();
      cout<<endl;
    }
  else
    cout<<"There is no army yet!"<<endl<<endl;
}

void Player::printArena(){
  cout<<endl<<name<<"'s arena:"<<endl;

  list<Personality *>::iterator it;

  if(arena->size()!=0){
    for(it = arena->begin() ; it != arena->end() ; it++)
      (*it)->print();
  }
  else{
    cout<<"There is no arena yet!"<<endl;
  }
}

void Player::revealProvinces(){
  for(int i=0 ; i<numberOfProvinces ; i++)
    provinces[i]->reveal();
}

void Player::printHoldings(){
  cout<<endl<<name<<"'s holdings:"<<endl;

  for(int i=0 ; i<holdings.size() ; i++)
    holdings[i]->print();
}

void Player::untapEverything(){
  int i;

  for(int i=0 ; i<army.size() ; i++)    //First untap the army
    if(army[i]->getIsTapped()==true)
      army[i]->changeTap();                //isTapped=false

  for(int i=0 ; i<holdings.size() ; i++)    //The the holdings
    if(holdings[i]->getIsTapped()==true)
      holdings[i]->changeTap();            //isTapped=false
}

void Player::drawFateCard(){
  if(numberOfHand<maxHand){
    hand.push_back(fateDeck.getGreen()->back());
    fateDeck.getGreen()->pop_back();
    numberOfHand++;
  }
  else      //Player have reached the limit of cards in his hand
    discardFateCards();
}

void Player::discardFateCards(){
  swap(hand[rand()%hand.size()],hand.back());
  printHand();
  delete hand.back();
  hand.pop_back();
  numberOfHand--;
}

void Player::discardFateCards(int pos){
  swap(hand[pos],hand.back());
  hand.pop_back();
  numberOfHand--;
}

void Player::pushArmyReplaceProvince(int pos){
  TypeConverter t;
  army.push_back(t.getPersonality(provinces[pos]));
  swap(provinces[pos],provinces.back());
  provinces.pop_back();
  provinces.push_back(dynastyDeck.getBlack()->back());
  dynastyDeck.getBlack()->pop_back();
}

void Player::pushHoldingReplaceProvince(int pos){
  TypeConverter t;
  holdings.push_back(t.getHolding(provinces[pos]));
  int n = holdings.size();
  makechain(holdings[n-1]);    //Check for chain in the last element
  swap(provinces[pos],provinces.back());
  provinces.pop_back();
  provinces.push_back(dynastyDeck.getBlack()->back());
  dynastyDeck.getBlack()->pop_back();
}

int Player::getArmySize(){
  return army.size();
}

int Player::getHoldinSize(){
  return holdings.size();
}

Holding *Player::getHoldingFigure(int pos){
  return holdings[pos];
}

Personality *Player::getArmyFigure(int pos){
  return army[pos];
}

GreenCard *Player::getHandFigure(int pos){
  return hand[pos];
}

void Player::buyGreenCard(GreenCard *gc,int position){
  tapHoldingsForBuy(gc->getCost());
  printHoldings();
  discardFateCards(position);
}

void Player::tapHoldingsForBuy(int value){
  int i,j,k,temp1,temp2,temp3;

  for(k=0 ; k<holdings.size() ; k++){
    temp1 = 0;
    j = 0;

    if(k > 0){
      temp1 = holdings[k]->getHarvestValue();
      j = k+1;
    }
    for( ; j<holdings.size() ; j++){
      temp2 = 0;

      i = 0;
      if(j>0){
        temp2 = holdings[j]->getHarvestValue();
        i = j+1;
      }
      for(; i<holdings.size() ; i++){
        temp3 = holdings[i]->getHarvestValue() + temp1 + temp2;

        if(temp3 >= value){
          holdings[i]->changeTap();
          money -= holdings[i]->getHarvestValue();
          if(temp2 != 0){
            holdings[j]->changeTap();
            money -= holdings[j]->getHarvestValue();
          }
          if(temp1 != 0){
            holdings[k]->changeTap();
            money -= holdings[k]->getHarvestValue();
          }
          return;
        }
      }
    }
  }

  temp1 = 0;
  for(i=0 ; i<holdings.size() ; i++){
    temp1 += holdings[i]->getHarvestValue();
    holdings[i]->changeTap();
    money -= holdings[i]->getHarvestValue();
    if(temp1 >= value)
      return;
  }

  printProvinces();
}

bool Player::checkUpgrade(GreenCard *gc){
  int choice;
  do{
    cout<<"Would you like to upgrade the stats of ";
    cout<<gc->getName()<<"?: ";
    cout<<"(Yes 1,No 0): ";
    cin>>choice;
  }while(choice!=0 && choice!=1);
  if(choice==1){
    if(gc->getEffectCost() > money){
      cout<<"You don't have the money to upgrade it!"<<endl;
      return false;
    }
    else{
      tapHoldingsForBuy(gc->getEffectCost());
      gc->upgrade();
      return true;
    }
  }
  return false;
}

void Player::passToArena(Personality *per,int pos){
  arena->push_back(per);
  army.erase(army.begin()+pos);
}

int Player::collectAttackPoints(){
  int attackPoints=0;

  list<Personality *>::iterator it;

  for(it = arena->begin() ; it != arena->end() ; it++)
    attackPoints += (*it)->getAttack();

  return attackPoints;
}

int Player::collectDefencePoints(){
  int defencePoints=0;

  list<Personality *>::iterator it;

  for(it = arena->begin() ; it != arena->end() ; it++)
    defencePoints += (*it)->getDefence();

  return defencePoints;
}

int Player::collectDefencePoints(int posOfProv){
  int defencePoints=0;

  list<Personality *>::iterator it;

  for(it = arena->begin() ; it != arena->end() ; it++)
    defencePoints += (*it)->getDefence();

  return defencePoints + provinces[posOfProv]->getInitialDefense();
}

int Player::destroyProvince(int posOfProv){
  graveyard->buryBlackCard(provinces[posOfProv]);
  provinces.erase(provinces.begin()+posOfProv);
  numberOfProvinces--;
}

void Player::returnToArmy(bool checkWin){
  list<Personality *>::iterator it;
  int i;

  if(checkWin){
    for(it = arena->begin(); it != arena->end() ;){
      (*it)->changeTap();
      army.push_back(*it);
      arena->remove(*it);
      it = arena->begin();
    }
  }
  else{   //if checkWin is false
    for(it = arena->begin(); it != arena->end() ;){
      (*it)->changeTap();
      (*it)->dishonour();
      if((*it)->checkForSeppuku()==true){
        graveyard->buryBlackCard(*it);
      }
      else{
        army.push_back(*it);
        arena->remove(*it);
        it = arena->begin();
      }
    }
  }
  printArmy();
  graveyard->printBlackDead();
}

void Player::destroyAllArena(){
  list<Personality *>::iterator it;

  for(it = arena->begin() ; it!=arena->end() ;){
    graveyard->buryBlackCard(*it);
    arena->remove(*it);
    it = arena->begin();
  }
  graveyard->printBlackDead();
}

void Player::destroyPartArena(int debt){
  while(debt>0){
    cout<<"Debt is "<<debt<<endl;
    cout<<"Your arena is: "<<endl;
    printArena();
    int choice;
    do{
      cout<<endl<<"Who would you like to sacrifice? (Choose by position): "<<endl;
      cin>>choice;
    }while(choice<=0 || choice>arena->size());


  }
  //Δεν τέλειωσε δυστυχώς
}

void Player::makechain(Holding* mk){				//mk is to be added,
	vector<Holding*>::iterator it;
	int t=0;
	Holding* h;
	it=holdings.begin();

	if(it==holdings.end()){							//empty
		return;
	}else{
		if(mk->getType()==3 && mk->getuH()==0){						//its a Mine, make chain with a Gold mine
			//need to find a Gold Mine
			while(it!=holdings.end() && t==0){
				h=*it;
				if(h->getType()==4 && h->getsH()==0){				//found Gold Mine
					mk->sethV(2);					//add value of Mine
					mk->setuH();					//has upperHolding
					h->setsH();						//Gold Mine has now a sub
					h->sethV(4);
					t=1;							//break while
				}
				it++;
			}
		}else if(mk->getType()==4){
			int t2=0;
			while(it!=holdings.end() && t==0 && t2==0){
				h=*it;
				if(h->getuH()==0 && h->getType()==3 && t==0){					//is Mine AND has no upperH
					mk->setsH();
					h->sethV(2);
					h->setuH();
					t=1;
				}
				if(h->getsH()==0 && h->getType()==5 && t2==0){					//same for Crystal
					mk->setuH();
					h->setsH();
					//h->sethV(2);
					t2=1;
				}
				it++;
			}
			if(t==1 && t2==0){					//only chained with Mine
				mk->sethV(4);
			}else if(t==0 && t2==1){			//w Crystal
				mk->sethV(5);
			}else if(t==1 && t2==1){			//both,to be doubled
				mk->sethV(2*mk->gethV());
			}
		}else if(mk->getType()==5){
			while(it!=holdings.end() && t==0){
				h=*it;
				if(h->getType()==4 && h->getuH()==0){	//GoldM is available for chain
					h->setuH();
					mk->setsH();
					t=1;
				}else
					it++;
			}
			if(t==1){
				if(h->getuH()==1 && h->getsH()==1){
					h->sethV(2*h->gethV());
				}else{
					h->sethV(5);
				}
				if(h->getsH()==1){						//full chain completed
					mk->sethV(3*h->gethV());
				}
			}
		}
	}
}

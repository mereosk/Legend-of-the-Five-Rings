#include <iostream>

#include "GraveYard.hpp"

using namespace std;

GraveYard::GraveYard(){
  greenDead = new list<GreenCard *>();
  blackDead = new list<BlackCard *>();
}

GraveYard::~GraveYard(){
  list<GreenCard *>::iterator it;
  list<BlackCard *>::iterator it1;

	for (it = greenDead->begin(); it != greenDead->end();)
	{
		delete *it;
		greenDead->remove(*it);
		it = greenDead->begin();
	}
	delete greenDead;

  for (it1 = blackDead->begin(); it1 != blackDead->end();)
	{
		delete *it1;
		blackDead->remove(*it1);
		it1 = blackDead->begin();
	}
	delete blackDead;
}

void GraveYard::printGreenDead(){
  list<GreenCard *>::iterator it;

  cout<<endl<<"Printing the green card graveyard"<<endl;

  if(greenDead->size() != 0)
    for(it = greenDead->begin() ; it!= greenDead->end() ; it++)
      (*it)->print();
  else
    cout<<"There are not dead green cards!"<<endl;
}

void GraveYard::printBlackDead(){
  list<BlackCard *>::iterator it;

  cout<<endl<<"Printing the black card graveyard"<<endl;

  if(blackDead->size() != 0)
    for(it = blackDead->begin() ; it!= blackDead->end() ; it++)
      (*it)->print();
  else
    cout<<"There are not dead black cards!"<<endl;
}

void GraveYard::buryGreenCard(GreenCard *gc){
  greenDead->push_back(gc);
}

void GraveYard::buryBlackCard(BlackCard *bc){
  TypeConverter tc;
  Personality *per;
  Holding *h;

  tc.getCorrectType(bc,&per,&h);
  if(h==NULL)
    per->dead();

  blackDead->push_back(bc);
}

list<GreenCard *>*  GraveYard::getGreenDead()const{
  return greenDead;
}

list<BlackCard *>*  GraveYard::getBlackDead()const{
  return blackDead;
}

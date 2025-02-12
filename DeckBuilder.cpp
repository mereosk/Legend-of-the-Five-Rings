#include "DeckBuilder.hpp"

using namespace std;

GreenDeckBuilder::GreenDeckBuilder()
{
	green = new list<GreenCard *>();
}

GreenDeckBuilder::~GreenDeckBuilder()
{
	list<GreenCard *>::iterator it;

	for (it = green->begin(); it != green->end();)
	{
		delete *it;
		green->remove(*it);
		it = green->begin();
	}
	delete green;
}

list<GreenCard*>* GreenDeckBuilder::getGreen()const{
	return green;
}

list<GreenCard *> *GreenDeckBuilder::createFateDeck()
{
	int i;
	list<GreenCard *>::iterator it;
	for (i = 0; i < NO_FOOTSOLDIER; i++)
		green->push_back(new Follower("Peasants",0));
	for (i = 0; i < NO_ARCHER; i++)
		green->push_back(new Follower("Elite Troops",1));
	for (i = 0; i < NO_SIEGER; i++)
		green->push_back(new Follower("Immortal Bushi",2));
	for (i = 0; i < NO_CAVALRY; i++)
		green->push_back(new Follower("Unicorn Horses",3));
	for (i = 0; i < NO_NAVAL; i++)
		green->push_back(new Follower("Yomi Ships",4));
	for (i = 0; i < NO_BUSHIDO; i++)
		green->push_back(new Follower("7 Samurai",5));

	// cout<<endl<<endl<<endl<<"NOW THE LIST"<<endl<<endl<<endl;
	// for(it=green->begin() ; it!=green->end() ; it++){
	// 	cout<<"followers"<<*it<<endl;
	// 	// (*it)->print();
	// }
	// cout<<endl;

	for (i = 0; i < NO_KATANA; i++)
		green->push_back(new Item("Daijtso",0));
	for (i = 0; i < NO_BOW; i++)
		green->push_back(new Item("Yumi",1));
	for (i = 0; i < NO_SPEAR; i++)
		green->push_back(new Item("Kama",2));
	for (i = 0; i < NO_NINJATO; i++)
		green->push_back(new Item("Butterfly Dagger",3));
	for (i = 0; i < NO_WAKIZASHI; i++)
		green->push_back(new Item("Kusanagi",4));

		// for(it=green->begin() ; it!=green->end() ; it++){
		// 	cout<<"items"<<*it<<endl;
		// 	// (*it)->print();
		// }

	deckShuffler(green);

	return green;
}

void GreenDeckBuilder::deckShuffler(list<GreenCard *> *green)
{
	vector<GreenCard *> vect;
	list<GreenCard *>::iterator it;
	for (it = green->begin(); it != green->end(); it++)
	vect.push_back((*it));

	random_shuffle(vect.begin(), vect.end());

	green->clear();

	vector<GreenCard *>::iterator it2;
	for (it2 = vect.begin(); it2 != vect.end(); it2++)
	green->push_back((*it2));
}

BlackDeckBuilder::BlackDeckBuilder()
{
	black = new list<BlackCard *>();
}

BlackDeckBuilder::~BlackDeckBuilder()
{
	list<BlackCard *>::iterator it;
	for (it = black->begin(); it != black->end();)
	{
		delete *it;
		black->remove(*it);
		it = black->begin();
	}
	delete black;
}

list<BlackCard*>* BlackDeckBuilder::getBlack()const{
	return black;
}

list<BlackCard *> *BlackDeckBuilder::createDynastyDeck()
{
	int i;
	list<BlackCard *>::iterator it;
	//Create Personalities
	//NO_DEFENSIVE 10
	for (i = 0; i < NO_DEFENSIVE; i++)
		black->push_back(new Personality("Footsoldiers",0));
	//NO_ATTACKING 10
	for (i = 0; i < NO_ATTACKING; i++)
		black->push_back(new Personality("Steadfast bushi",1));
	//NO_SHOGUN	2
	black->push_back(new Personality("Akodo Kaneka",2));
	black->push_back(new Personality("Isawa Shi en",2));
	//NO_CHANCELLOR 2
	black->push_back(new Personality("Hida Shozen",3));
	black->push_back(new Personality("Mirimuto Enishi",3));
	//NO_CHAMPION 1
	black->push_back(new Personality("Hida Kisada",4));
	//Create holdings

	// for(it=black->begin() ; it!=black->end() ; it++){
	// 	cout<<"Personality"<<*it<<endl;
	// 	// (*it)->print();
	// }

	for (i = 0; i < NO_SOLO; i++)
		black->push_back(new Holding("Gifts and Favors",0));
	for (i = 0; i < NO_PLAIN; i++)
		black->push_back(new Holding("Rice Fields",1));
	for (i = 0; i < NO_FARMS; i++)
		black->push_back(new Holding("Fish Farms",2));
	for (i = 0; i < NO_MINE; i++)
		black->push_back(new Holding("Ashio Copper Mine",3));
	for (i = 0; i < NO_GOLD_MINE; i++)
		black->push_back(new Holding("Konomai Gold Mine",4));
	for (i = 0; i < NO_CRYSTAL_MINE; i++)
		black->push_back(new Holding("Ichinokawa Crystal Mine",5));

		// for(it=black->begin() ; it!=black->end() ; it++){
		// 	cout<<"Holding"<<*it<<endl;
		// 	// (*it)->print();
		// }

	deckShuffler(black);

	return black;
}

void BlackDeckBuilder::deckShuffler(list<BlackCard *> *black)
{
	vector<BlackCard *> vect;
	list<BlackCard *>::iterator it;
	for (it = black->begin(); it != black->end(); it++)
		vect.push_back((*it));

	random_shuffle(vect.begin(), vect.end());

	black->clear();

	vector<BlackCard *>::iterator it2;
	for (it2 = vect.begin(); it2 != vect.end(); it2++)
		black->push_back((*it2));
}

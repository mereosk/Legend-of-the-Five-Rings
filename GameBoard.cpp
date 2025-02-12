#include <iostream>
#include "GameBoard.hpp"

using namespace std;

GameBoard::GameBoard(){
  int i;
  string name;

  numberOfPlayers = rand()%2+2;
  cout<<"NUMBERS OF PLAYERS IS "<<numberOfPlayers<<endl;

  for(i=0 ; i<numberOfPlayers ; i++){
    cout<<"Player "<<i+1<<" enter your name: ";
    cin>>name;
    players.push_back(new Player(name));
  }
  printGameStatistics();

  //cout<<"GameBoard just created!"<<endl;
}

GameBoard::~GameBoard(){
  int i;

  for(i=0 ; i<numberOfPlayers ; i++)
    delete players[i];

  //cout<<"GameBoard is destroyed!"<<endl;
}

void GameBoard::printGameStatistics(){
  int i;
  int life = 0;

  cout<<"-------------------GAME STATISTICS-------------------"<<endl;
  for(i=0 ; i<numberOfPlayers ; i++){
    cout<<"Player "<<i+1<<" "<<players[i]->getName()<<": "<<endl;
    cout<<"Money = "<<players[i]->getMoney()<<endl;
    cout<<"Honor = "<<players[i]->getHonour()<<endl;
    if(players[i]->getNumberOfProvinces() == 4)
      cout<<"Has all 4 provinces!"<<endl;
    else
      cout<<"Has "<<players[i]->getNumberOfProvinces()<<" provinces!"<<endl;

    cout<<"Life = ";
    life = 0;
    for(int j=0 ; j<players[i]->getNumberOfProvinces() ; j++)
      life += players[i]->getProvinces(j)->getInitialDefense();
    cout<<life<<endl;
    cout<<endl;
  }
}

void GameBoard::printArena(){
  cout<<"Printing the arena!"<<endl;
  for(int i=0 ; i<numberOfPlayers ; i++){
    cout<<endl;
    players[i]->printArena();
  }
}

Player *GameBoard::getPlayer(int pos){
  return players[pos];
}

bool GameBoard::checkWinningCondition(){
  int i,j;

  for(i=0 ; i<numberOfPlayers ; i++)
    if(!players[i]->getNumberOfProvinces()){
      cout<<players[i]->getName()<<" has lost the game!"<<endl;
      delete players[i];
      players.erase(players.begin()+i);
      if(--numberOfPlayers==1)  //Check if game ended
        return true;
    }
  return false;
}

void GameBoard::startingPhase(){
  cout<<"--------------------------STARTING PHASE--------------------------"<<endl;
  for(int i=0 ; i<numberOfPlayers ; i++){
    players[i]->untapEverything();
    players[i]->drawFateCard();
    players[i]->revealProvinces();
    players[i]->printHand();
    players[i]->printProvinces();
  }
}

void GameBoard::equipPhase(){
  int choice,j,k;
  bool flag[numberOfPlayers],helpVar;    //Array helping us stop the repetition

  cout<<"--------------------------EQUIP PHASE--------------------------"<<endl;
  while(1){
    helpVar = true;
    for(k=0 ; k<numberOfPlayers ; k++)      //Initialization of the array
      flag[k] = true;
    for(int i=0,j=0; i<numberOfPlayers ; i++,j++){
      if(players[i]->getArmySize()==0){
        cout<<players[i]->getName()<<" can't enter equip phase. There is no army!"<<endl;
        flag[j] = false;
      }
      else{
        players[i]->printHand();
        players[i]->printArmy();
        do{
          cout<<endl;
          cout<<players[i]->getName()<<" would you like to equip your personalities?";
          cout<<"(1 yes,0 no): ";
          cin>>choice;
        }while(choice!=0 && choice!=1);

        switch (choice) {
          case 0:
            flag[j] = false;
            cout<<"Lets continue!"<<endl;
            break;
          case 1:
            do{
              cout<<"Who would you like to equip?";
              cout<<"(Enter the personality's position): ";
              cin>>choice;
            }while(choice<=0 || choice>players[i]->getArmySize());
            cout<<"You chose "<<players[i]->getArmyFigure(choice-1)->getName()<<endl;
            //Check if you've reached the limit of folls and items
            if(players[i]->getArmyFigure(choice-1)->getFollAndItemsSize() ==
            players[i]->getArmyFigure(choice-1)->getLimit()){
              cout<<players[i]->getArmyFigure(choice-1)->getName();
              cout<<" have reached the limit. Can't equip it."<<endl;
            }
            else{
              int newChoice;
              do{
                cout<<"With which green card would you like to equip ";
                cout<<players[i]->getArmyFigure(choice-1)->getName();
                cout<<"(Enter the position of the card in your hand): ";
                cin>>newChoice;
              }while(newChoice<=0 || newChoice>players[i]->getNumberOfHand());
              cout<<"You chose "<<players[i]->getHandFigure(newChoice-1)->getName()<<endl;
              if(players[i]->getHandFigure(newChoice-1)->getCost() > players[i]->getMoney()){
                cout<<"You dont have the money to buy ";
                cout<<players[i]->getHandFigure(newChoice-1)->getName()<<endl;
              }
              else{

                Follower *fol;
                Item *item;
                TypeConverter tp;
                tp.getCorrectType(players[i]->getHandFigure(newChoice-1),&fol,&item);
                if(item==NULL){
                  if(players[i]->getArmyFigure(choice-1)->equip(fol)){      //If it is true
                    players[i]->buyGreenCard(fol,newChoice-1);
                    if(players[i]->checkUpgrade(fol)){
                      players[i]->getArmyFigure(choice-1)->upgradeStats(fol->getEffectBonus());
                      players[i]->getArmyFigure(choice-1)->print();
                      cout<<"The upgrade is done!"<<endl;
                    }
                  }
                }
                else{
                  if(players[i]->getArmyFigure(choice-1)->equip(item)){     //If it is true
                    players[i]->buyGreenCard(item,newChoice-1);
                    if(players[i]->checkUpgrade(item)){
                      players[i]->getArmyFigure(choice-1)->upgradeStats(item->getEffectBonus());
                      players[i]->getArmyFigure(choice-1)->print();
                      cout<<"The upgrade is done!"<<endl;
                    }
                  }
                }
              }
            }
            break;
          default:
            break;
        }
        printGameStatistics();
      }
    }
  for(j=0 ; j<numberOfPlayers ; j++){
    if(flag[j] == true){
      helpVar = false;
      break;
    }
  }
  if(!helpVar)     //==false
    continue;
  break;
  }
  cout<<endl<<"End of equip phase"<<endl;
}

void GameBoard::actionPhase(Player *attacker,Player *defender){
  int i,j,v,choice,helpVar,helpVar1;
  Player *playerArray[2] = {attacker,defender};
  bool flagArray[2];

  while(1){
    for(int k=0 ; k<2 ; k++)      //Initialization of the flag array
      flagArray[k]=true;

      helpVar1 = true;
    for(i=0,v=0; i<2 ; i++,v++){
      helpVar = true;

      playerArray[i]->printArmy();
      for(j=0 ; j<playerArray[i]->getArmySize() ; j++){             //Check if all personalities are tapped
        if(!playerArray[i]->getArmyFigure(j)->getIsTapped()){
          break;
        }
        helpVar = false;
      }
      if(!helpVar){                                              //Check if you have any personalities
        cout<<"You cannot add a personality to your arena cause ";
        cout<<"they are all tapped!"<<endl;
        flagArray[v] = false;
        continue;
      }
      if(!playerArray[i]->getArmySize()){
        cout<<"You cannot add a personality to your arena cause you have non"<<endl;
        flagArray[v] = false;
      }
      else{
        do{
          cout<<playerArray[i]->getName();
          cout<<" which untapped personality whould you like to add to your arena?";
          cout<<"(choose position or 0 if you dont want to take action): ";
          cin>>choice;

          if(!choice)
            break;
        }while(choice<=0 || choice>playerArray[i]->getArmySize() || playerArray[i]->getArmyFigure(choice-1)->getIsTapped()==true);
        if(!choice){
          cout<<"You dont want to make a move. Next player.."<<endl;
          flagArray[v] = false;
        }
        else{
          cout<<"You chose "<<playerArray[i]->getArmyFigure(choice-1)->getName()<<endl;
          playerArray[i]->passToArena(playerArray[i]->getArmyFigure(choice-1),choice-1);
          playerArray[i]->printArena();
        }
      }
    }
    for(j=0 ; j<2 ; j++){
      if(flagArray[j]==true){
        helpVar1=false;
        break;
      }
    }
    if(!helpVar1)
      continue;
    break;
  }
}

void GameBoard::battle(Player *attacker,Player *defender,int posOfProv){
  bool checkWin;

  cout<<endl<<attacker->collectAttackPoints();
  cout<<"-"<<defender->collectDefencePoints(posOfProv)<<"=";
  cout<<attacker->collectAttackPoints()-defender->collectDefencePoints(posOfProv)<<endl;

  if((attacker->collectAttackPoints()-defender->collectDefencePoints(posOfProv))>defender->getProvinces(posOfProv)->getInitialDefense()){
    cout<<attacker->getName()<<" won the battle!!"<<endl;
    checkWin=true;
    defender->destroyProvince(posOfProv);
    defender->destroyAllArena();
    attacker->returnToArmy(checkWin);
    defender->printArena();
  }
  else if((attacker->collectAttackPoints()>defender->collectDefencePoints(posOfProv))){
    cout<<attacker->getName()<<" could not destroy the province!"<<endl;
    checkWin=false;
    defender->destroyAllArena();
    //attacker->destroyPartArena(attacker->collectAttackPoints()-defender->collectDefencePoints());
    attacker->returnToArmy(checkWin);
  }
  else if(attacker->collectAttackPoints()==defender->collectDefencePoints(posOfProv)){
    cout<<"It is a tie"<<endl;
    defender->destroyAllArena();
    attacker->destroyAllArena();
  }
  else{
    cout<<"Defender won!!"<<endl;
    checkWin=true;
    attacker->destroyAllArena();
    //defender->destroyPartArena(defender->collectDefencePoints()-attacker->collectAttackPoints());
    defender->returnToArmy(checkWin);
  }
}

void GameBoard::battlePhase(){
  bool inCharge=true;
  int i=0,j,choice,choice1;
  cout<<"--------------------------BATTLE PHASE--------------------------"<<endl;
  while(i<battleRounds){
    cout<<endl<<endl<<i+1<<"ST ROUND"<<endl<<endl;
    for(j=0 ; j<numberOfPlayers ; j++){
      do{
        cout<<players[j]->getName()<<" who would you like to challenge?";
        cout<<"(enter the number of player or 0 to pass): ";
        cin>>choice;
      }while(choice<0 || choice>numberOfPlayers || choice==j+1);
      if(!choice){
        cout<<"You have passed!"<<endl;
        continue;
      }
      cout<<"You chose "<<players[choice-1]->getName();

      actionPhase(players[j],players[choice-1]);

      players[choice-1]->printProvinces();
      do{
        cout<<players[j]->getName();
        cout<<" choose a province to attack(Choose by position): ";
        cin>>choice1;
      }while(choice1<=0 || choice1>players[choice-1]->getNumberOfProvinces());
      cout<<"You chose to attack at "<<players[choice-1]->getProvinces(choice1-1)->getName();

      battle(players[j],players[choice-1],choice1-1);
    }
    i++;
  }
}

void GameBoard::economyPhase(){
  int choice,j,k;
  bool flag[numberOfPlayers],helpVar;    //Array helping us stop the repetition

  cout<<"--------------------------ECONOMY PHASE--------------------------"<<endl;
  while(1){
    helpVar = true;
    for(k=0 ; k<numberOfPlayers ; k++)      //Initialization of the array
      flag[k] = true;
    for(int i=0,j=0; i<numberOfPlayers ; i++,j++){
      players[i]->printProvinces();
      players[i]->printHoldings();

      bool temp = false;
      for(int f=0 ; f<players[i]->getHoldinSize() ; f++){
        if(players[i]->getHoldingFigure(f)->getIsTapped() == false)   //If only one untapped exist cont
          temp = true;
      }

      if(temp == false){
        cout<<players[i]->getName();
        cout<<" all your holdings are tapped! You can't buy"<<endl;
        flag[i] = false;
        continue;
      }

      do{
        cout<<endl;
        cout<<players[i]->getName()<<" would you like to buy anything?";
        cout<<"(1 yes,0 no): ";
        cin>>choice;
      }while(choice!=0 && choice!=1);

      switch (choice) {
        case 0:
          flag[j] = false;
          cout<<"Lets continue!"<<endl;
          break;
        case 1:
          do{
            cout<<"What province would you like to buy? ";
            cout<<"(Enter the province's position): ";
            cin>>choice;
          }while(choice<=0 || choice>players[i]->getNumberOfProvinces());

          if(players[i]->getProvinces(choice-1)->getCost() > players[i]->getMoney()){
            cout<<"You dont have the money to buy ";
            cout<<players[i]->getHandFigure(choice-1)->getName()<<endl;
            flag[j] = false;
            break;
          }

          players[i]->tapHoldingsForBuy(players[i]->getProvinces(choice-1)->getCost());

          Personality *per;
          Holding *hol;
          TypeConverter tp;
          tp.getCorrectType(players[i]->getProvinces(choice-1),&per,&hol);
          if(hol==NULL){
            players[i]->pushArmyReplaceProvince(choice-1);
          }
          else{
            players[i]->pushHoldingReplaceProvince(choice-1);
          }
          break;
      }
    }
  for(j=0 ; j<numberOfPlayers ; j++){
    if(flag[j] == true){
      helpVar = false;
      break;
    }
  }
  if(!helpVar)     //==false
    continue;
  break;
  }
  cout<<endl<<"End of economy phase"<<endl;
}

#include <iostream>
#include "Card.hpp"
#include "Personality.hpp"
#include "Holding.hpp"
#include "Follower.hpp"
#include "Item.hpp"
#include "DeckBuilder.hpp"
#include "Player.hpp"
#include "GameBoard.hpp"

using namespace std;

int main(){
  srand(unsigned(time(NULL)));
  GameBoard L5R;
  bool game = true;

  while(game){
    L5R.startingPhase();
    L5R.equipPhase();
    L5R.battlePhase();
    L5R.economyPhase();

    cout<<L5R.getPlayer(0)->getName()<<" WON THE GAME"<<endl;

    if(L5R.checkWinningCondition()==true){
      cout<<L5R.getPlayer(0)->getName()<<" WON THE GAME"<<endl;
      game = false;
    }
    // break;
  }
  cout<<endl<<"End of main"<<endl;
  return 0;
}

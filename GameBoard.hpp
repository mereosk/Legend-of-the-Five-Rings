#include <vector>
#include <ctime>
#include <cstdlib>
#include "Player.hpp"
#include "TypeConverter.hpp"

const int battleRounds = 2;

class GameBoard{
public:
  GameBoard();
  ~GameBoard();
  void printGameStatistics();
  void printArena();
  bool checkWinningCondition();
  void startingPhase();
  void equipPhase();
  void actionPhase(Player *attacker,Player *defender);
  void battle(Player *attacker,Player *defender,int posOfProv);
  void battlePhase();
  void economyPhase();
  Player *getPlayer(int pos);
private:
  vector<Player *> players;
  int numberOfPlayers;
};


#include "eniesLobby.h"

using namespace std;

int main()
{
	
string inputFile = "test1";
EniesLobbyBattle battle(inputFile);
battle.runBattle();
cout << battle.getResult() << endl;
}
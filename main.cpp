
#include "eniesLobby.h"

using namespace std;

int main(int argc, const char * argv[]) {

    cout << "=== BAT DAU TEST ===" << endl;
    
    // Test 1: Tao Luffy
    cout << "\n--- Test 1: Tao Luffy ---" << endl;
    Luffy* luffy = new Luffy("Luffy", 120, 35, 20, 25, 50, 150000000);
    
    // Test 2: Kiem tra cac gia tri
    cout << "\n--- Test 2: Kiem tra gia tri ---" << endl;
    cout << "Name: " << luffy->getName() << endl;
    cout << "HP: " << luffy->getHP() << endl;
    cout << "Energy: " << luffy->getEnergy() << endl;
    cout << "Is alive: " << (luffy->isAlive() ? "true" : "false") << endl;
    
    // Test 3: Thu receiveDamage
    cout << "\n--- Test 3: Thu receiveDamage ---" << endl;
    cout << "HP truoc damage: " << luffy->getHP() << endl;
    luffy->receiveDamage(30);
    cout << "HP sau damage 30: " << luffy->getHP() << endl;
    luffy->receiveDamage(200);
    cout << "HP sau damage 200: " << luffy->getHP() << endl;
    cout << "Is alive: " << (luffy->isAlive() ? "true" : "false") << endl;
    
    // Test 4: Tao Zoro
    cout << "\n--- Test 4: Tao Zoro ---" << endl;
    Zoro* zoro = new Zoro("Zoro", 110, 40, 15, 22, 30, 60000000);
    cout << "Name: " << zoro->getName() << endl;
    cout << "HP: " << zoro->getHP() << endl;
    cout << "Energy: " << zoro->getEnergy() << endl;
    
    // Test 5: Tao Lucci (CP9)
    cout << "\n--- Test 5: Tao Lucci (CP9) ---" << endl;
    Lucci* lucci = new Lucci("Lucci", 150, 40, 25, 30, 60, 4000);
    cout << "Name: " << lucci->getName() << endl;
    cout << "HP: " << lucci->getHP() << endl;
    cout << "Energy: " << lucci->getEnergy() << endl;
    
    // Giai phong bo nho
    cout << "\n--- Giai phong bo nho ---" << endl;
    delete luffy;
    delete zoro;
    delete lucci;
    
    cout << "\n=== KET THUC TEST ===" << endl;
    return 0;
}

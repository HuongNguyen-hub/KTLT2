
#include "eniesLobby.h"

using namespace std;

void debugPrintCharacter(Character* c, string prefix = "") {
    if (c == nullptr) {
        cout << prefix << "nullptr" << endl;
        return;
    }
    cout << prefix << "Name: " << c->getName() 
         << ", HP: " << c->getHP() 
         << "/" << c->getmaxHp()
         << ", Energy: " << c->getEnergy()
         << ", Alive: " << (c->isAlive() ? "Yes" : "No")
         << ", Type: " << (c->isStrawHat() ? "StrawHat" : "CP9")
         << endl;
}

// Hàm debug in context
void debugPrintContext(BattleContext& context, string title = "CONTEXT") {
    cout << "\n=== " << title << " ===" << endl;
    cout << "turnCount: " << context.turnCount << endl;
    cout << "morale: " << context.morale << "/100" << endl;
    cout << "alarmLevel: " << context.alarmLevel << "/100" << endl;
    cout << "rescueProgress: " << context.rescueProgress << "/100" << endl;
    cout << "escapeProgress: " << context.escapeProgress << "/100" << endl;
    cout << "busterCallTimer: " << context.busterCallTimer << endl;
    cout << "mainGateDestroyed: " << (context.mainGateDestroyed ? "true" : "false") << endl;
    cout << "robinRescued: " << (context.robinRescued ? "true" : "false") << endl;
    cout << "battleEnded: " << (context.battleEnded ? "true" : "false") << endl;
    cout << "resultCode: " << context.resultCode << endl;
    cout << "==================" << endl;
}

// Hàm debug in danh sách nhân vật
void debugPrintCharacters(Character** chars, int count, string title) {
    cout << "\n=== " << title << " (" << count << " members) ===" << endl;
    for (int i = 0; i < count; i++) {
        if (chars[i] != nullptr) {
            cout << "  [" << i << "] ";
            debugPrintCharacter(chars[i], "");
        }
    }
}

// Hàm debug in turnOrder
void debugPrintTurnOrder(TurnNode* turnOrder) {
    cout << "\n=== TURN ORDER ===" << endl;
    TurnNode* cur = turnOrder;
    int pos = 0;
    while (cur != nullptr) {
        if (cur->data != nullptr) {
            cout << "  [" << pos << "] " << cur->data->getName() 
                 << " (" << (cur->data->isStrawHat() ? "StrawHat" : "CP9") << ")" << endl;
        }
        cur = cur->next;
        pos++;
    }
    cout << "==================" << endl;
}

// Hàm test riêng từng nhân vật
void testLuffy() {
    cout << "\n========== TEST LUFFY ==========" << endl;
    BattleContext context;
    context.morale = 50;
    
    Luffy luffy("Luffy", 120, 35, 20, 25, 50, 150000000);
    Lucci lucci("Lucci", 150, 40, 25, 30, 60, 4000);
    
    cout << "Before attack:" << endl;
    debugPrintCharacter(&luffy, "Luffy: ");
    debugPrintCharacter(&lucci, "Lucci: ");
    
    // Test attack
    cout << "\n--- Luffy attacks Lucci ---" << endl;
    int damage = luffy.attack(&lucci, context);
    cout << "Damage: " << damage << endl;
    debugPrintCharacter(&lucci, "Lucci after: ");
    
    // Test specialSkill
    cout << "\n--- Luffy uses Gear Second ---" << endl;
    damage = luffy.specialSkill(&lucci, context);
    cout << "Damage: " << damage << endl;
    debugPrintCharacter(&luffy, "Luffy after: ");
    debugPrintCharacter(&lucci, "Lucci after: ");
    
    // Test endTurn
    luffy.endTurn(context);
    cout << "After endTurn, Luffy energy: " << luffy.getEnergy() << endl;
}

void testZoro() {
    cout << "\n========== TEST ZORO ==========" << endl;
    BattleContext context;
    Zoro zoro("Zoro", 110, 38, 18, 24, 45, 120000000);
    Lucci lucci("Lucci", 150, 40, 25, 30, 60, 4000);
    
    debugPrintCharacter(&zoro, "Zoro: ");
    debugPrintCharacter(&lucci, "Lucci: ");
    
    int damage = zoro.attack(&lucci, context);
    cout << "Attack damage: " << damage << endl;
    debugPrintCharacter(&lucci, "Lucci after: ");
}

void testSanji() {
    cout << "\n========== TEST SANJI ==========" << endl;
    BattleContext context;
    Sanji sanji("Sanji", 105, 36, 19, 26, 48, 103000000);
    Jabra jabra("Jabra", 125, 37, 24, 26, 50, 2180);
    
    debugPrintCharacter(&sanji, "Sanji: ");
    debugPrintCharacter(&jabra, "Jabra: ");
    
    int damage = sanji.specialSkill(&jabra, context);
    cout << "SpecialSkill damage: " << damage << endl;
    cout << "Jabra defense after: " << jabra.getdef() << endl;
}

void testNami() {
    cout << "\n========== TEST NAMI ==========" << endl;
    BattleContext context;
    Nami nami("Nami", 80, 25, 15, 30, 60, 66000000);
    Kaku kaku("Kaku", 130, 38, 22, 28, 55, 2200);
    
    debugPrintCharacter(&nami, "Nami: ");
    debugPrintCharacter(&kaku, "Kaku: ");
    
    int damage = nami.specialSkill(&kaku, context);
    cout << "SpecialSkill damage: " << damage << endl;
    cout << "Kaku speed after: " << kaku.getspeed() << endl;
    cout << "busterCallTimer: " << context.busterCallTimer << endl;
    cout << "alarmLevel: " << context.alarmLevel << endl;
}

void testChopper() {
    cout << "\n========== TEST CHOPPER ==========" << endl;
    BattleContext context;
    Chopper chopper("Chopper", 70, 22, 20, 20, 55, 50000000);
    Luffy luffy("Luffy", 120, 35, 20, 25, 50, 150000000);
    
    // Hạ Luffy xuống 30 HP
    luffy.receiveDamage(90);
    
    cout << "Before heal:" << endl;
    debugPrintCharacter(&luffy, "Luffy: ");
    debugPrintCharacter(&chopper, "Chopper: ");
    
    int heal = chopper.specialSkill(&luffy, context);
    cout << "Heal amount: " << heal << endl;
    debugPrintCharacter(&luffy, "Luffy after: ");
}

void testFranky() {
    cout << "\n========== TEST FRANKY ==========" << endl;
    BattleContext context;
    Franky franky("Franky", 130, 40, 30, 20, 45, 94000000);
    Lucci lucci("Lucci", 150, 40, 25, 30, 60, 4000);
    
    debugPrintCharacter(&franky, "Franky: ");
    debugPrintCharacter(&lucci, "Lucci: ");
    
    // Test Strong Right
    int damage = franky.specialSkill(&lucci, context);
    cout << "Strong Right damage: " << damage << endl;
    cout << "Lucci speed after: " << lucci.getspeed() << endl;
}

int main() {
    cout << "==========================================" << endl;
    cout << "     DEBUG MODE - TEST STRAW HAT 3.2" << endl;
    cout << "==========================================" << endl;
    
    // Test từng nhân vật
    testLuffy();
    testZoro();
    testSanji();
    testNami();
    testChopper();
    testFranky();
    
    // Test full battle với file
    cout << "\n========== FULL BATTLE TEST ==========" << endl;
    cout << "Reading file: test.txt" << endl;
    
    EniesLobbyBattle battle("test1");
    battle.runBattle();
    
    cout << "\n========== FINAL RESULT ==========" << endl;
    cout << battle.getResult() << endl;
    
    return 0;
}
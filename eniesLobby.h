#ifndef ENIES_LOBBY_H
#define ENIES_LOBBY_H

#include "main.h"

class BattleContext;
class Building;
class Character;
struct TurnNode;

/*
 * Character
 */
class Character {
protected:
    string name; //tên nhân vật
    int hp; // lượng máu hiện tại
    int maxHp;//lượng máu tối đa 
    int atk;//chỉ số tấn công cơ bản
    int def;//chỉ số phòng thủ
    int speed;//tốc độ hành động của nhân vật
    int energy;//năng lượng hiện tại dùng để thi triển kĩ năng
    bool alive;//trạng thái còn khả năng chiến đấu của nhân vật

public:
    Character();
    Character(string name, int hp, int atk, int def, int speed, int energy);
    virtual ~Character();

    virtual int attack(Character* target, BattleContext& context) = 0;
    virtual int specialSkill(Character* target, BattleContext& context) = 0;

    virtual int attack(Building* target, BattleContext& context);
    virtual int specialSkill(Building* target, BattleContext& context);

    virtual void endTurn(BattleContext& context);

    void receiveDamage(int damage);
   
    bool isAlive() const;
    string getName() const;
    int getHP() const;
    int getmaxHp()const ;
    int getdef() const;
    int getspeed() const;
    void setspeed(int newspeed);
    void setdef(int newDef) ;
    void sethp (int newhp);
    int getEnergy() const;

    virtual bool isStrawHat() const;
    virtual bool isCP9() const;

    virtual string str() const = 0;
    virtual int getSpecialSkillCost() const = 0;
};

/*
 * StrawHat
 */
class StrawHat : public Character {
protected:
    long long bounty; //tiền truy nã

public:
    StrawHat();
    StrawHat(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty);

    virtual bool isStrawHat() const;
    virtual string str() const;
};

/*
 * Straw Hat members
 */
class Luffy : public StrawHat {
private : bool ktra_xem_luffy_co_ha_guc_ai_khong;
public:
    Luffy(string name, int hp, int atk, int def,
          int speed, int energy, long long bounty);

    int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);

    int attack(Building* target, BattleContext& context);
    int specialSkill(Building* target, BattleContext& context);

    void endTurn(BattleContext& context);
    int getSpecialSkillCost() const { return 20; }
};

class Zoro : public StrawHat {
private: bool ktra_xem_zoro_ha_guc;
public:
    Zoro(string name, int hp, int atk, int def,
         int speed, int energy, long long bounty);

    int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);

    int attack(Building* target, BattleContext& context);
    int specialSkill(Building* target, BattleContext& context);

    void endTurn(BattleContext& context);
    int getSpecialSkillCost() const  {return 15;}
};

class Sanji : public StrawHat {
private: bool sanji_co_ha_duoc_dt;
public:
    Sanji(string name, int hp, int atk, int def,
          int speed, int energy, long long bounty);

    int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);

    int attack(Building* target, BattleContext& context);
    int specialSkill(Building* target, BattleContext& context);

    void endTurn(BattleContext& context);
    int getSpecialSkillCost() const  {return 18;}
};

class Nami : public StrawHat {
private: bool nami_co_win ;
public:
    Nami(string name, int hp, int atk, int def,
         int speed, int energy, long long bounty);

    int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);

    int attack(Building* target, BattleContext& context);
    int specialSkill(Building* target, BattleContext& context);

    void endTurn(BattleContext& context);
    int getSpecialSkillCost() const  {return 20;}
};

class Chopper : public StrawHat {
public:
    Chopper(string name, int hp, int atk, int def,
            int speed, int energy, long long bounty);

    int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);

    int attack(Building* target, BattleContext& context);

    void endTurn(BattleContext& context);
    int getSpecialSkillCost() const { return 15; }
};

class Usopp : public StrawHat {
public:
    Usopp(string name, int hp, int atk, int def,
          int speed, int energy, long long bounty);

    int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);

    int attack(Building* target, BattleContext& context);
    int specialSkill(Building* target, BattleContext& context);

    void endTurn(BattleContext& context);
    int getSpecialSkillCost() const { return 16; }

};

class Franky : public StrawHat {
private : 
bool check_over_70 ;
bool check_under_30;

public:
    Franky(string name, int hp, int atk, int def,
           int speed, int energy, long long bounty);

    int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);

    int attack(Building* target, BattleContext& context);
    int specialSkill(Building* target, BattleContext& context);

    void endTurn(BattleContext& context);
    int getSpecialSkillCost() const { return 20; }  
};


/*
 * CP9Agent
 */
class CP9Agent : public Character {
protected:
    int doriki;

public:
    CP9Agent();
    CP9Agent(string name, int hp, int atk, int def,
             int speed, int energy, int doriki);

    virtual bool isCP9() const;
    virtual string str() const;
};

/*
 * CP9 members
 */
class Lucci : public CP9Agent {
public:
    Lucci(string name, int hp, int atk, int def,
          int speed, int energy, int doriki);

    int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);
    void endTurn(BattleContext& context);
    int getSpecialSkillCost() const { return 25; }

};

class Kaku : public CP9Agent {
public:
    Kaku(string name, int hp, int atk, int def,
         int speed, int energy, int doriki);

    int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);
    void endTurn(BattleContext& context);
    int getSpecialSkillCost() const { return 20; }

};

class Jabra : public CP9Agent {
public:
    Jabra(string name, int hp, int atk, int def,
          int speed, int energy, int doriki);

    int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);
    void endTurn(BattleContext& context);
    int getSpecialSkillCost() const { return 18; }

};

class Blueno : public CP9Agent {
public:
    Blueno(string name, int hp, int atk, int def,
           int speed, int energy, int doriki);

    int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);
    void endTurn(BattleContext& context);
    int getSpecialSkillCost() const { return 15; }

};

class Kalifa : public CP9Agent {
public:
    Kalifa(string name, int hp, int atk, int def,
           int speed, int energy, int doriki);

    int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);
    void endTurn(BattleContext& context);
    int getSpecialSkillCost() const { return 18; }

};

class Kumadori : public CP9Agent {
public:
    Kumadori(string name, int hp, int atk, int def,
             int speed, int energy, int doriki);

    int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);
    void endTurn(BattleContext& context);
    int getSpecialSkillCost() const { return 16; }

};

class Fukurou : public CP9Agent {
public:
    Fukurou(string name, int hp, int atk, int def,
            int speed, int energy, int doriki);

    int attack(Character* target, BattleContext& context);
    int specialSkill(Character* target, BattleContext& context);
    void endTurn(BattleContext& context);
    int getSpecialSkillCost() const { return 14; }

};

/*
 * BattleContext
 */
class BattleContext {
public:
    int turnCount; //số lượt diện ra
    int morale; //tinh thần phe mũ rơm <100
    int alarmLevel; //mức báo động tại Enies Lobby<100
    int rescueProgress; //tiến độ giải cứu Robin<100
    int escapeProgress;//tiến độ rút lui khởi enies lobby<100
    int busterCallTimer; //số lượt còn lại trước khi buster xảy ra>9
    bool mainGateDestroyed;//cổng chính đã bị phá hay chưa , mặc định false
    bool robinRescued;//xác định robin đã đc cứu hay chưa , mặc định false
    bool bridgeOpened;//xác định cầu thoát hiểu được mở hay ch , md false
    bool battleEnded;//xác định trận đấu kt hay chưa , false
    string resultCode; //kết quả cuối cùng
    int lowestStrawHatHP ;

public:
    BattleContext();
    void nextTurn();
};

/*
 * Building
 */
class Building {
protected:
    string name; //tên công trình
    int hp; //độ bền hiện tại
    int maxHP; //độ bền tối đa
    bool destroyed; //xác định công trình đã bị phá hay chưa

public:
    Building(string name, int hp);
    virtual ~Building();
    int gethp()const;
    int getmaxHP()const;

    void receiveDamage(int damage);
    bool isDestroyed() const;

    virtual void applyEffect(BattleContext& context) = 0;
    virtual void onDestroyed(BattleContext& context);

    virtual string str () const;
    //them method
    string getname() const;

};

/*
 * Building subclasses
 */
class MainGate : public Building {
public:
    MainGate(string name, int hp);

    void applyEffect(BattleContext& context);
    void onDestroyed(BattleContext& context);
};

class Courthouse : public Building {
public:
    Courthouse(string name, int hp);

    void applyEffect(BattleContext& context);
    void onDestroyed(BattleContext& context);
};

class TowerOfJustice : public Building {
public:
    TowerOfJustice(string name, int hp);

    void applyEffect(BattleContext& context);
};

class BridgeOfHesitation : public Building {
public:
    BridgeOfHesitation(string name, int hp);

    void applyEffect(BattleContext& context);
};

class BusterCallShip : public Building {
public:
    BusterCallShip(string name, int hp);

    void applyEffect(BattleContext& context);
    void onDestroyed(BattleContext& context);
};

/*
 * TurnNode to create Linked List turn order
 */
struct TurnNode
{
    Character* data;
    TurnNode* next;
};

/*
 * EniesLobbyBattle
 */
class EniesLobbyBattle {
private:
    Character** strawHats; //mảng động lưu các nhân vật bằng mũ rơm
    int strawHatCount; //số lượng mũ rơm hiện có

    Character** cp9Agents; //lưu các đặc vụ cp9
    int cp9Count; //số lượng đặc vụ cp9 hiện có

    Building** buildings; //lưu các công trình trên chiến trường ko quá 5
    int buildingCount;//số lượng công trình hiện có

    TurnNode* turnOrder; //(LINKED LIST)danh sách liên kết đơn quản lí thứ tự hành động các nhân vật
    BattleContext context;//trạng thái hiện tại của trận đánh
    int maxTurns;//số lượt tối đa của trận đánh
    
    


public:
    EniesLobbyBattle(const string& filename);
    ~EniesLobbyBattle();

    void loadFromFile(const string& filename);

    void addStrawHat(Character* character);
    void addCP9Agent(Character* character);
    void addBuilding(Building* building);

    void buildTurnOrder();

    void runBattle();
    void processTurn(Character* character);
    void processBuildings();
    void checkEndCondition();

    string getResult() const;
    //them ham
    void assign_minHP_Murom (Character *StrawHat);
    TurnNode *delete_all_node (TurnNode *head);
    /*-----------------------------------------*/
    /*tạo một hàm để kiểm tra xem ai mang số hp min ở team mũ rơm.
    Tuy nhiên vấn đề là  mảng của tên nhân vật mũ rơm là character 
    mảng 2 chiều , nên muốn truy xuất từng tên thì từng tên đó sẽ là con
    trỏ 1 chiều . Nên là kết quả trả về sẽ là lượng máu hp min thôi*/
    int findLowestHp();

};

#endif

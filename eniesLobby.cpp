#include "eniesLobby.h"

/*
 * BattleContext
 */
BattleContext::BattleContext()
{
    turnCount = 0;
    morale = 0;
    alarmLevel = 0;
    rescueProgress = 0;
    escapeProgress = 0;
    busterCallTimer = 0;
    mainGateDestroyed = false;
    robinRescued = false;
    bridgeOpened = false;
    battleEnded = false;
    resultCode = "";
}

void BattleContext::nextTurn()
{
    // TODO: implement
}

/*
 * Character
 */
Character::Character()
{
    name = "";
    hp = 0;        // lượng máu hiện tại
    maxHp = 0;     // lượng máu tối đa
    atk = 0;       // chỉ số tấn công cơ bản
    def = 0;       // chỉ số phòng thủ
    speed = 0;     // tốc độ hành động
    energy = 0;    // năng lượng hiện tại dùng để thi triển kĩ năng
    alive = false; // trạng thái còn khả năng chiến đấu
}
// 1
Character::Character(string name, int hp, int atk, int def, int speed, int energy)
{
    this->name = name; // dùng con trỏ this để phân biệt các biến
    this->hp = hp;
    this->maxHp = hp;
    this->atk = atk;
    this->def = def;
    this->speed = speed;
    this->energy = energy;
    if (hp > 0)
        this->alive = true;
    else
        this->alive = false;
}

Character::~Character() {} // do character là lớp ảo nên cần tạo destructor

int Character::attack(Building *target, BattleContext &context)
{
    return 0;
}

int Character::specialSkill(Building *target, BattleContext &context)
{
    return 0;
}

void Character::endTurn(BattleContext &context)
{
    return;
}

void Character::receiveDamage(int damage)
{
    // TODO: implement
    int sat_thuong_thuc_te = damage - this->def; // ko can dung this do damage va def chi co 1
    if (sat_thuong_thuc_te < 0)
        sat_thuong_thuc_te = 0;
    hp = hp - sat_thuong_thuc_te; // cap nhat lai luong mau
    if (hp <= 0)
    {
        hp = 0;
        alive = false;
    }
}

bool Character::isAlive() const
{
    return alive; // thuc hien xong nvu la tra ve kha nang chien dau
}

string Character::getName() const
{
    return name;
}

int Character::getHP() const
{
    return hp;
}
//them ham nay vao dac ta
int Character::getmaxHp() const
{
    return maxHp;
}

int Character::getEnergy() const
{
    return energy;
}

bool Character::isStrawHat() const
{
    return false; // mac dinh cua ng ta
}

bool Character::isCP9() const
{
    return false; // tam thoi de check
}

/*
 * StrawHat
 */
StrawHat::StrawHat() : Character()
{
    bounty = 0;
}

StrawHat::StrawHat(string name, int hp, int atk, int def,
                   int speed, int energy, long long bounty)
    : Character(name, hp, atk, def, speed, energy)
// do nhan tham so giong lp character nen tien hanh goi lớp cha là character
{
    this->bounty = bounty;
}

bool StrawHat::isStrawHat() const
{
    return true;
    // do đây là trong lớp StrawHat : lớp mũ rơn
    // nếu ở lớp khác thì return false
    //  TODO: implement
}

string StrawHat::str() const
{
    // TODO: implement
    stringstream ss;
    ss << "StrawHat [ name =" << this->name << ", hp =" << this->hp
       << " , atk =" << atk << " , def" << def << ", speed =" << speed
       << " ,energy = " << energy << ", bounty =" << bounty << "]";
    return ss.str(); // chuyen ve chuoi
}

/*
 * Luffy
 */
Luffy::Luffy(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty)
    : StrawHat(name, hp, atk, def, speed, energy, bounty) // do thua ke tu StrawHat
{
    // TODO: implement-->ko can lm gi
}

int Luffy::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    double damage_temp;
    if (hp > 0.5 * maxHp)
        damage_temp = atk;
    else if (hp > 0.3 * maxHp)
        damage_temp = 1.15 * atk;
    else if (hp >= 0 && hp < 0.3 * maxHp)
        damage_temp = 1.3 * atk;
    // lm tron len
    int damage = ceil(damage_temp);
    // dua vao ham recieve damage ktra xem con song khong
    target->receiveDamage(damage); // goi ham de tinh alive
    if (!target->isAlive()&&target->isCP9())
        context.morale += 5; // public

    return damage; // trả về lượng sát thương thực tế được tạo ra
}

int Luffy::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (energy < 20 || hp < (int)ceil(0.15 * maxHp))
        return 0;

    this->energy -= 20; // ton 20 nang luong cho gear second
    // do luffy sd kĩ năng gear second nên đã gây sát thương cho đối thủ
    int enemy_damage = (int)ceil(2.0 * atk);
    target->receiveDamage(enemy_damage); // cap nhat mau doi thu
    this->atk += 15;
    this->speed += 15; // speed of luffy
    context.alarmLevel += 10;
    // cap nhat hp thuc te of luffy
    int luffy_damage = (int)ceil(0.08 * maxHp); // luong giam la luong sat thuong
    this->receiveDamage(luffy_damage);
    if (!target->isAlive()&&target->isCP9()) 
    {
        context.morale +=5;
        ktra_xem_luffy_co_ha_guc_ai_khong =1;
    }
    //luffy còn sống chưa chắc mục tiêu bị hạ gục -->ktra target
    return enemy_damage ;
}

int Luffy::attack(Building *target, BattleContext &context)
{
    // TODO: implement
    double temp_damage ;
    if (this->hp > (int) ceil (0.5 *maxHp)) temp_damage = atk ;
    else if (this->hp > (int) ceil (0.3 *maxHp)) temp_damage = 1.15 * atk;
    else if (this->hp >=0) temp_damage = 1.3 *atk;
    int damage_building = ceil(temp_damage);
    //cap nhat damage thuc te
    target->receiveDamage(damage_building);
    return damage_building; 
    //do đây là tấn công công trình nên ko có mục tiêu ->bỏ qua 
    //nv hạ gục mục tiêu
}

int Luffy::specialSkill(Building *target, BattleContext &context)
{
    // TODO: implement
    if(this->energy <20||this->hp<(int) ceil(0.15*maxHp)) return 0;
    this->energy -=20 ;
    int buiding_damage = (int) ceil (2.0 *atk); 
    //cap nhat hp of building
    target->receiveDamage(buiding_damage);
    this->speed +=15;
    this->atk +=15;
    context.alarmLevel +=10;
    int hp_loss = (int) ceil (0.08*maxHp);
    this->receiveDamage(hp_loss);
    return buiding_damage;
}

void Luffy::endTurn(BattleContext &context)
{
    // TODO: implement
    if(hp < (int) ceil(0.3 * maxHp)) context.morale +=3;
    if(ktra_xem_luffy_co_ha_guc_ai_khong) 
    {
        this->energy +=5;
        ktra_xem_luffy_co_ha_guc_ai_khong =false ; //reset cho luot sau
    }
}

/*
 * Zoro
 */
Zoro::Zoro(string name, int hp, int atk, int def,
           int speed, int energy, long long bounty)
    :StrawHat (name,hp,atk,def,speed,energy,bounty)
{
    //no need to do
}

int Zoro::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    int enemy_damage = (int) ceil (atk + 0.2*def) ;
    if(target->getHP() < (int) ceil(0.4* target->getmaxHp())) 
    enemy_damage = (int) ceil(1.15*enemy_damage);
    //cap nhat lai hp doi thu sau moi phuong thuc
    target->receiveDamage(enemy_damage);
    if (!target->isAlive()&&target->isCP9())
    {
        context.morale +=5;
    }
    return enemy_damage ;
}

int Zoro::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if(this->energy <15 ) return 0;
    this->energy -=15;
    double enemy_damage_temp =2.2*atk;
    if(target->getHP() < (int)ceil (0.5 * target->getmaxHp())) 
    enemy_damage_temp = 1.5 *enemy_damage_temp ;
    //lam tron den kq cuoi cung
    int enemy_damage = ceil (enemy_damage_temp);
    target->receiveDamage(enemy_damage);
    if(!target->isAlive()&&target->isCP9()) 
    {
        this->energy +=8;
        context.morale+=4;
        ktra_xem_zoro_ha_guc=true;
    }
    return enemy_damage;
}

int Zoro::attack(Building *target, BattleContext &context)
{
    // TODO: implement
    int building_damage = (int) ceil (atk + 0.2*def) ;
    if(target->gethp() < (int) ceil(0.4* target->getmaxHP())) 
    building_damage = (int) ceil(1.15*building_damage);
    //cap nhat lai hp doi thu sau moi phuong thuc
    target->receiveDamage(building_damage);
    return building_damage ;
}

int Zoro::specialSkill(Building *target, BattleContext &context)
{
    // TODO: implement
    if(this->energy <15 ) return 0;
    this->energy -=15;
    double building_damage_temp =2.2*atk;
    if(target->gethp() < (int)ceil (0.5 * target->getmaxHP())) 
    building_damage_temp = 1.5 *building_damage_temp ;
    //lam tron den kq cuoi cung
    int building_damage = ceil (building_damage_temp);
    target->receiveDamage(building_damage);
    return building_damage;
}

void Zoro::endTurn(BattleContext &context)
{
    // TODO: implement
    if(ktra_xem_zoro_ha_guc)
    {
        context.morale+=6;
        this->atk = ceil (1.05 * this->atk);
    }
}

/*
 * Sanji
 */
Sanji::Sanji(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty)
{
    // TODO: implement
}

int Sanji::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

int Sanji::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

int Sanji::attack(Building *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

int Sanji::specialSkill(Building *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

void Sanji::endTurn(BattleContext &context)
{
    // TODO: implement
}

/*
 * Nami
 */
Nami::Nami(string name, int hp, int atk, int def,
           int speed, int energy, long long bounty)
{
    // TODO: implement
}

int Nami::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

int Nami::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

int Nami::attack(Building *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

int Nami::specialSkill(Building *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

void Nami::endTurn(BattleContext &context)
{
    // TODO: implement
}

/*
 * Chopper
 */
Chopper::Chopper(string name, int hp, int atk, int def,
                 int speed, int energy, long long bounty)
{
    // TODO: implement
}

int Chopper::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

int Chopper::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

int Chopper::attack(Building *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

void Chopper::endTurn(BattleContext &context)
{
    // TODO: implement
}

/*
 * Usopp
 */
Usopp::Usopp(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty)
{
    // TODO: implement
}

int Usopp::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

int Usopp::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

int Usopp::attack(Building *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

int Usopp::specialSkill(Building *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

void Usopp::endTurn(BattleContext &context)
{
    // TODO: implement
}

/*
 * Franky
 */
Franky::Franky(string name, int hp, int atk, int def,
               int speed, int energy, long long bounty)
{
    // TODO: implement
}

int Franky::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

int Franky::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

int Franky::attack(Building *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

int Franky::specialSkill(Building *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

void Franky::endTurn(BattleContext &context)
{
    // TODO: implement
}

/*
 * CP9Agent
 */
CP9Agent::CP9Agent() : Character()
{
    doriki = 0; // đại diện cho sức mạng tổng thể của đặc vụ
}

CP9Agent::CP9Agent(string name, int hp, int atk, int def,
                   int speed, int energy, int doriki)
    : Character(name, hp, atk, def, speed, energy) // inherted from character
{
    this->doriki = doriki;
}

bool CP9Agent::isCP9() const
{
    return true; // do thuộc lớp CP9-->là CP9
    // TODO: implement
}

string CP9Agent::str() const
{
    stringstream ss;
    ss << "CP9 [ name =" << name << " , hp =" << hp << ", atk =" << atk << " , def ="
       << def << ", speed =" << speed << ", energy =" << energy << ", doriki =" << doriki << "]";
    return ss.str();
}

/*
 * Lucci
 */
Lucci::Lucci(string name, int hp, int atk, int def,
             int speed, int energy, int doriki)
{
    // TODO: implement
}

int Lucci::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

int Lucci::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

void Lucci::endTurn(BattleContext &context)
{
    // TODO: implement
}

/*
 * Kaku
 */
Kaku::Kaku(string name, int hp, int atk, int def,
           int speed, int energy, int doriki)
{
    // TODO: implement
}

int Kaku::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

int Kaku::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

void Kaku::endTurn(BattleContext &context)
{
    // TODO: implement
}

/*
 * Jabra
 */
Jabra::Jabra(string name, int hp, int atk, int def,
             int speed, int energy, int doriki)
{
    // TODO: implement
}

int Jabra::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

int Jabra::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

void Jabra::endTurn(BattleContext &context)
{
    // TODO: implement
}

/*
 * Blueno
 */
Blueno::Blueno(string name, int hp, int atk, int def,
               int speed, int energy, int doriki)
{
    // TODO: implement
}

int Blueno::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

int Blueno::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

void Blueno::endTurn(BattleContext &context)
{
    // TODO: implement
}

/*
 * Kalifa
 */
Kalifa::Kalifa(string name, int hp, int atk, int def,
               int speed, int energy, int doriki)
{
    // TODO: implement
}

int Kalifa::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

int Kalifa::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

void Kalifa::endTurn(BattleContext &context)
{
    // TODO: implement
}

/*
 * Kumadori
 */
Kumadori::Kumadori(string name, int hp, int atk, int def,
                   int speed, int energy, int doriki)
{
    // TODO: implement
}

int Kumadori::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

int Kumadori::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

void Kumadori::endTurn(BattleContext &context)
{
    // TODO: implement
}

/*
 * Fukurou
 */
Fukurou::Fukurou(string name, int hp, int atk, int def,
                 int speed, int energy, int doriki)
{
    // TODO: implement
}

int Fukurou::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

int Fukurou::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    return 0;
}

void Fukurou::endTurn(BattleContext &context)
{
    // TODO: implement
}

/*
 * Building
 */
Building::Building(string name, int hp)
{
    // TODO: implement
}

Building::~Building()
{
    // TODO: implement if needed
}

void Building::receiveDamage(int damage)
{
    // TODO: implement
}

bool Building::isDestroyed() const
{
    // TODO: implement
    return destroyed;
}

void Building::onDestroyed(BattleContext &context)
{
    return;
}

string Building::str() const
{
    // TODO: implement
    return "";
}

//them method
int Building::gethp() const
{
    return hp; //do ben hien tai
}
int Building::getmaxHP() const
{
    return maxHP;//do ben toi da
}
//
/*
 * MainGate
 */
MainGate::MainGate(string name, int hp) : Building(name, hp) {}

void MainGate::applyEffect(BattleContext &context)
{
    // TODO: implement
}

void MainGate::onDestroyed(BattleContext &context)
{
    // TODO: implement
}

/*
 * Courthouse
 */
Courthouse::Courthouse(string name, int hp) : Building(name, hp) {}

void Courthouse::applyEffect(BattleContext &context)
{
    // TODO: implement
}

void Courthouse::onDestroyed(BattleContext &context)
{
    // TODO: implement
}

/*
 * TowerOfJustice
 */
TowerOfJustice::TowerOfJustice(string name, int hp) : Building(name, hp) {}

void TowerOfJustice::applyEffect(BattleContext &context)
{
    // TODO: implement
}

/*
 * BridgeOfHesitation
 */
BridgeOfHesitation::BridgeOfHesitation(string name, int hp) : Building(name, hp) {}

void BridgeOfHesitation::applyEffect(BattleContext &context)
{
    // TODO: implement
}

/*
 * BusterCallShip
 */
BusterCallShip::BusterCallShip(string name, int hp) : Building(name, hp) {}

void BusterCallShip::applyEffect(BattleContext &context)
{
    // TODO: implement
}

void BusterCallShip::onDestroyed(BattleContext &context)
{
    // TODO: implement
}

/*
 * EniesLobbyBattle
 */
EniesLobbyBattle::EniesLobbyBattle(const string &filename)
{
    // TODO: implement
}

EniesLobbyBattle::~EniesLobbyBattle()
{
    // TODO: implement
}

void EniesLobbyBattle::loadFromFile(const string &filename)
{
    // TODO: implement
}

void EniesLobbyBattle::addStrawHat(Character *character)
{
    // TODO: implement
}

void EniesLobbyBattle::addCP9Agent(Character *character)
{
    // TODO: implement
}

void EniesLobbyBattle::addBuilding(Building *building)
{
    // TODO: implement
}

void EniesLobbyBattle::buildTurnOrder()
{
    // TODO: implement
}

void EniesLobbyBattle::runBattle()
{
    // TODO: implement
}

void EniesLobbyBattle::processTurn(Character *character)
{
    // TODO: implement
}

void EniesLobbyBattle::processBuildings()
{
    // TODO: implement
}

void EniesLobbyBattle::checkEndCondition()
{
    // TODO: implement
}

string EniesLobbyBattle::getResult() const
{
    // TODO: implement
    return "";
}
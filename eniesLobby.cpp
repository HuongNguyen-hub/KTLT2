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
    if (damage >= 0)
    {
        int sat_thuong_thuc_te = damage - this->def; // ko can dung this do damage va def chi co 1

        if (sat_thuong_thuc_te < 0)
        {
            sat_thuong_thuc_te = 0;
            damage = 0;
        }
        hp = hp - sat_thuong_thuc_te; // cap nhat lai luong mau
    }
    else // hoi mau
    {
        hp += (-damage);
    }

    if (hp > maxHp)
        hp = maxHp;
    if (hp <= 0)
    {
        hp = 0;
        alive = false;
    }
    else
        alive = true;
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

// them ham nay vao dac ta
int Character::getmaxHp() const
{
    return maxHp;
}
int Character::getdef() const
{
    return def;
}
void Character::setdef(int newDef)
{
    def = newDef;
}
int Character::getspeed() const
{
    return speed;
}
void Character::setspeed(int newspeed)
{
    speed = newspeed;
}
void Character::sethp(int newhp)
{
    hp = newhp;
}
//

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
    ss << "StrawHat[name=" << this->name << ", hp=" << this->hp
       << ", atk=" << atk << ", def=" << def << ", speed=" << speed
       << ", energy=" << energy << ", bounty=" << bounty << "]";
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
    int damage_temp;
    if (hp > 0.5 * maxHp)
        damage_temp = atk;
    else if (hp > 0.3 * maxHp)
        damage_temp = ceil( 1.15 * atk);
    else if (hp >= 0 && hp < 0.3 * maxHp)
        damage_temp = ceil( 1.3 * atk);
    // lm tron len
    int damage = damage_temp;
    // dua vao ham recieve damage ktra xem con song khong
    target->receiveDamage(damage); // goi ham de tinh alive
    if (!target->isAlive() && target->isCP9())
        context.morale += 5; // public
return damage-target->getdef();
     // trả về lượng sát thương thực tế được tạo ra
}

int Luffy::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (energy < 20 || hp < 0.15 * maxHp)
        return 0;

    this->energy -= 20; // ton 20 nang luong cho gear second
    // do luffy sd kĩ năng gear second nên đã gây sát thương cho đối thủ
    int enemy_damage = ceil(2.0 * atk);
    target->receiveDamage(enemy_damage); // cap nhat mau doi thu
    this->atk += 15;
    this->speed += 15; // speed of luffy
    context.alarmLevel += 10;
    // cap nhat hp thuc te of luffy
    int luffy_damage = ceil(0.08 * maxHp); // luong giam la luong sat thuong
    this->receiveDamage(luffy_damage);
    if (!target->isAlive() && target->isCP9())
    {
        ktra_xem_luffy_co_ha_guc_ai_khong = 1;
    }
    // luffy còn sống chưa chắc mục tiêu bị hạ gục -->ktra target
    return enemy_damage-target->getdef();
}

int Luffy::attack(Building *target, BattleContext &context)
{
    // TODO: implement
    double temp_damage;
    if (this->hp > (int)ceil(0.5 * maxHp))
        temp_damage = atk;
    else if (this->hp > (int)ceil(0.3 * maxHp))
        temp_damage = 1.15 * atk;
    else if (this->hp >= 0)
        temp_damage = 1.3 * atk;
    int damage_building = ceil(temp_damage);
    // cap nhat damage thuc te
    target->receiveDamage(damage_building);
    return damage_building;
    // do đây là tấn công công trình nên ko có mục tiêu ->bỏ qua
    // nv hạ gục mục tiêu
}

int Luffy::specialSkill(Building *target, BattleContext &context)
{
    // TODO: implement
    if (this->energy < 20 || this->hp < (int)ceil(0.15 * maxHp))
        return 0;
    this->energy -= 20;
    int buiding_damage = (int)ceil(2.0 * atk);
    // cap nhat hp of building
    target->receiveDamage(buiding_damage);
    this->speed += 15;
    this->atk += 15;
    context.alarmLevel += 10;
    int hp_loss = (int)ceil(0.08 * maxHp);
    this->receiveDamage(hp_loss);
    return buiding_damage;
}

void Luffy::endTurn(BattleContext &context)
{
    // TODO: implement
    if (hp < (int)ceil(0.3 * maxHp))
        context.morale += 3;
    if (ktra_xem_luffy_co_ha_guc_ai_khong)
    {
        this->energy += 5;
        ktra_xem_luffy_co_ha_guc_ai_khong = false; // reset cho luot sau
    }
}

/*
 * Zoro
 */
Zoro::Zoro(string name, int hp, int atk, int def,
           int speed, int energy, long long bounty)
    : StrawHat(name, hp, atk, def, speed, energy, bounty)
{
    // no need to do
}

int Zoro::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    int enemy_damage = (int)ceil(atk + 0.2 * def);
    if (target->getHP() < (int)ceil(0.4 * target->getmaxHp()))
        enemy_damage = (int)ceil(1.15 * enemy_damage);
    // cap nhat lai hp doi thu sau moi phuong thuc
    target->receiveDamage(enemy_damage);
    if (!target->isAlive() && target->isCP9())
    {
        context.morale += 5;
    }
    return enemy_damage;
}

int Zoro::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (this->energy < 15)
        return 0;
    this->energy -= 15;
    double enemy_damage_temp = 2.2 * atk;
    if (target->getHP() < (int)ceil(0.5 * target->getmaxHp()))
        enemy_damage_temp = 1.5 * enemy_damage_temp;
    // lam tron den kq cuoi cung
    int enemy_damage = ceil(enemy_damage_temp);
    target->receiveDamage(enemy_damage);
    if (!target->isAlive() && target->isCP9())
    {
        this->energy += 8;
        context.morale += 4;
        ktra_xem_zoro_ha_guc = true;
    }
    return enemy_damage;
}

int Zoro::attack(Building *target, BattleContext &context)
{
    // TODO: implement
    int building_damage = (int)ceil(atk + 0.2 * def);
    if (target->gethp() < (int)ceil(0.4 * target->getmaxHP()))
        building_damage = (int)ceil(1.15 * building_damage);
    // cap nhat lai hp doi thu sau moi phuong thuc
    target->receiveDamage(building_damage);
    return building_damage;
}

int Zoro::specialSkill(Building *target, BattleContext &context)
{
    // TODO: implement
    if (this->energy < 15)
        return 0;
    this->energy -= 15;
    double building_damage_temp = 2.2 * atk;
    if (target->gethp() < (int)ceil(0.5 * target->getmaxHP()))
        building_damage_temp = 1.5 * building_damage_temp;
    // lam tron den kq cuoi cung
    int building_damage = ceil(building_damage_temp);
    target->receiveDamage(building_damage);
    return building_damage;
}

void Zoro::endTurn(BattleContext &context)
{
    // TODO: implement
    if (ktra_xem_zoro_ha_guc)
    {
        context.morale += 6;
        this->atk = ceil(1.05 * this->atk);
        ktra_xem_zoro_ha_guc = false; // reset
    }
}

/*
 * Sanji
 */
Sanji::Sanji(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty)
    : StrawHat(name, hp, atk, def, speed, energy, bounty)
{
    // TODO: implement
    // no need to do
}

int Sanji::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    double enemy_temp = this->atk + 0.5 * this->speed;
    if (target->getdef() < this->def)
        enemy_temp = 1.1 * enemy_temp;
    int enemy_damage = ceil(enemy_temp);
    target->receiveDamage(enemy_damage);
    if (!target->isAlive() && target->isCP9())
        context.morale += 5;
    return enemy_damage;
}

int Sanji::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (this->energy < 18)
        return 0;
    this->energy -= 18;
    double enemy_temp = 2.1 * atk;
    int enemy_damage = ceil(enemy_temp);
    // cap nhat sau khi trung don
    target->receiveDamage(enemy_damage);
    int reduce_def = 8;
    if (target->getName() == "Jabra")
    {
        reduce_def = 12;
    }
    int newDef;
    newDef = target->getdef() - reduce_def;
    if (newDef < 0)
        newDef = 0;
    target->setdef(newDef);
    if (!target->isAlive() && target->isCP9())
    {
        context.morale += 5;
        sanji_co_ha_duoc_dt = true;
    }
    return enemy_damage;
}

int Sanji::attack(Building *target, BattleContext &context)
{
    // TODO: implement
    double building_temp = this->atk + 0.5 * this->speed;

    int building_damage = ceil(building_temp);
    target->receiveDamage(building_damage);
    return building_damage;
}

int Sanji::specialSkill(Building *target, BattleContext &context)
{
    // TODO: implement
    if (this->energy < 18)
        return 0;
    this->energy -= 18;
    int building_damage = ceil(2.1 * this->atk);
    target->receiveDamage(building_damage);
    return building_damage;
}

void Sanji::endTurn(BattleContext &context)
{
    // TODO: implement
    if (sanji_co_ha_duoc_dt)
    {
        context.morale += 8;
        this->atk = ceil(1.1 * this->atk);
        sanji_co_ha_duoc_dt = false; // reset
    }
}

/*
 * Nami
 */
Nami::Nami(string name, int hp, int atk, int def,
           int speed, int energy, long long bounty)
    : StrawHat(name, hp, atk, def, speed, energy, bounty)
{
    // TODO: implement
    // no need to do
}

int Nami::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    double enemy_damage_temp = this->atk + 0.3 * target->getdef();
    int enemy_damage = ceil(enemy_damage_temp);
    target->receiveDamage(enemy_damage); // cap nhat hp , isAlive
    if (!target->isAlive() && target->isCP9())
    {
        context.morale += 5;
        this->nami_co_win = true;
    }

    return enemy_damage;
}

int Nami::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (this->energy < 20)
        return 0;
    energy -= 20;
    int enemy_damage = this->atk + 40;
    int speed_actual = target->getspeed() - 10;
    if (speed_actual < 0)
        speed_actual = 0;
    // cap nhat lai speed of doi thu
    target->setspeed(speed_actual);
    target->receiveDamage(enemy_damage);
    context.busterCallTimer += 1;
    context.alarmLevel -= 5;
    if (context.alarmLevel < 0)
        context.alarmLevel = 0;
    if (!target->isAlive() && target->isCP9())
    {
        context.morale += 5;
        this->nami_co_win = true;
    }
    return enemy_damage;
}

int Nami::attack(Building *target, BattleContext &context)
{
    // TODO: implement
    int building_damage = ceil(0.5 * this->atk);
    target->receiveDamage(building_damage);
    return building_damage;
}

int Nami::specialSkill(Building *target, BattleContext &context)
{
    // TODO: implement
    if (this->energy < 20)
        return 0;
    this->energy -= 20;
    double damage_temp = this->atk + 40;
    int buidling_damage = ceil(1.5 * damage_temp);
    target->receiveDamage(buidling_damage);
    context.busterCallTimer += 1;
    context.alarmLevel -= 5;
    if (context.alarmLevel < 0)
        context.alarmLevel = 0;
    return buidling_damage;
}

void Nami::endTurn(BattleContext &context)
{
    // TODO: implement
    if (this->nami_co_win)
    {
        this->energy += 6;
        if (this->energy > 100)
            this->energy = 100;
        this->nami_co_win = false; // reset
    }
}

/*
 * Chopper
 */
Chopper::Chopper(string name, int hp, int atk, int def,
                 int speed, int energy, long long bounty)
    : StrawHat(name, hp, atk, def, speed, energy, bounty)
{
    // TODO: implement
    // no need to do
}

int Chopper::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    int enemy_damage = this->atk;
    target->receiveDamage(enemy_damage);
    if (!target->isAlive() && target->isCP9())
    {
        context.morale += 5;
    }
    return enemy_damage;
}
int Chopper::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (this->energy < 15)
        return 0;
    this->energy -= 15;
    /*Do tham số đầu vào ko truyền tất cả các thành viên nên là thành viên có máu hp
    thấp nhất sẽ do hàm phía sau chọn*/
    // CHÚ Ý CHOPPER
    int heal_hp = ceil(35 + 0.5 * this->atk);
    target->receiveDamage(-heal_hp); // hoi mau
    if (target->getName() == "Luffy")
    {
        context.morale += 5;
        if (context.morale > 100)
            context.morale = 100;
    }
    return 0;
    // do không có sát thương
}

int Chopper::attack(Building *target, BattleContext &context)
{
    // TODO: implement
    int building_damage = this->atk;
    target->receiveDamage(building_damage);
    return building_damage;
}

void Chopper::endTurn(BattleContext &context)
{
    // TODO: implement
    // no need to do
}

/*
 * Usopp
 */
Usopp::Usopp(string name, int hp, int atk, int def,
             int speed, int energy, long long bounty)
    : StrawHat(name, hp, atk, def, speed, energy, bounty)
{
    // TODO: implement
    // no need to do
}

int Usopp::attack(Character *target, BattleContext &context)

{
    // TODO: implement
    double temp_damage = this->atk;
    if (target->getspeed() < 50)
        temp_damage = ceil(1.2 * temp_damage);
    int enemy_damage = ceil(temp_damage);
    target->receiveDamage(enemy_damage);
    if (!target->isAlive() && target->isCP9())
    {
        context.morale += 5;
        if (context.morale > 100)
            context.morale = 100;
    }
    return enemy_damage;
}

int Usopp::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (this->energy < 16)
        return 0;
    this->energy -= 16;
    int enemy_damage = ceil(0.8 * this->atk);
    target->setspeed(target->getspeed() - 12);
    target->receiveDamage(enemy_damage);
    context.escapeProgress += 8;
    if (context.escapeProgress > 100)
        context.escapeProgress = 100;
    return enemy_damage;
}

int Usopp::attack(Building *target, BattleContext &context)
{
    // TODO: implement
    int building_damage = ceil(0.5 * this->atk);
    return building_damage;
}

int Usopp::specialSkill(Building *target, BattleContext &context)
{
    // TODO: implement
    if (this->energy < 16)
        return 0;
    this->energy -= 16;
    int building_damage = ceil(0.8 * this->atk);
    target->receiveDamage(building_damage);
    context.escapeProgress += 8;
    if (context.escapeProgress > 100)
        context.escapeProgress = 100;
    return building_damage;
}

void Usopp::endTurn(BattleContext &context)
{
    // TODO: implement
    context.morale += 10;
    if (context.morale > 100)
        context.morale = 100;
}

/*
 * Franky
 */
Franky::Franky(string name, int hp, int atk, int def,
               int speed, int energy, long long bounty)
    : StrawHat(name, hp, atk, def, speed, energy, bounty)
{
    // TODO: implement
    // no need to do
}

int Franky::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    int temp = ceil( this->atk + 0.3 * this->def);
    if (target->isCP9())
        temp = ceil(1.1 * temp);
    int enemy_damage = temp;
    target->receiveDamage(enemy_damage);
    if (target->isCP9() && !target->isAlive())
    {
        context.morale += 5;
        if (context.morale > 100)
            context.morale = 100;
    }
    if (this->hp < 0.7 * maxHp)
        check_over_70 = true;
    if (this->hp < 0.3 * maxHp)
        check_under_30 = true;
    return enemy_damage;
}

int Franky::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    // coup de vent
    if (this->energy >= 30)
    {

        this->energy -= 30;
        int enemy_damage = ceil(this->atk * 1.2);
        target->receiveDamage(enemy_damage);
        if (!target->isAlive() && target->isCP9())
        {
            context.morale += 5;
            if (context.morale > 100)
                context.morale = 100;
        }
        if (this->hp < 0.7 * maxHp)
            check_over_70 = true;
        return enemy_damage;
    }
    else if (this->energy >= 20)
    {
        this->energy -= 20;
        double temp = ceil(this->atk * 1.8);
        int new_speed = (target->getspeed() - 8);
        if (new_speed < 0)
            new_speed = 0;
        target->setspeed(new_speed);
        if (target->getName() == "Lucci")
            temp = 1.2 * temp;
        int enemy_damage = (int)ceil(temp);
        target->receiveDamage(enemy_damage);
        if (this->hp < 0.7 * maxHp)
            check_over_70 = true;
        if (!target->isAlive() && target->isCP9())
        {
            context.morale += 5;
            if (context.morale > 100)
                context.morale = 100;
        }
        return enemy_damage;
    }
    return 0;
}

int Franky::attack(Building *target, BattleContext &context)
{
    // TODO: implement
    double temp = this->atk + 0.3 * this->def;
    int building_damage = (int)ceil(temp);
    target->receiveDamage(building_damage);
    return building_damage;
}

int Franky::specialSkill(Building *target, BattleContext &context)
{
    // TODO: implement
    if (this->energy >= 30)
    {

        this->energy -= 30;
        int enemy_damage = (int)ceil(this->atk * 1.2);
        target->receiveDamage(INT_MAX);
        return INT_MAX; // DESTROYED
    }
    else if (this->energy >= 20)
    {
        this->energy -= 20;
        double building_damage = (int)ceil(this->atk * 1.8);
        target->receiveDamage(building_damage);
        return building_damage;
    }
    return 0;
}

void Franky::endTurn(BattleContext &context)
{
    // TODO: implement
    if (check_over_70)
    {
        this->def += 5;
        check_over_70 = false; // reset
    }
    if (check_under_30)
    {
        this->atk = ceil(1.1 * this->atk);
        check_under_30 = false;
    }
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
    ss << "CP9[name=" << name << ", hp=" << hp << ", atk=" << atk << ", def="
       << def << ", speed=" << speed << ", energy=" << energy << ", doriki=" << doriki << "]";
    return ss.str();
}

/*
 * Lucci
 */
Lucci::Lucci(string name, int hp, int atk, int def,
             int speed, int energy, int doriki)
    : CP9Agent(name, hp, atk, def, speed, energy, doriki)
{
    // TODO: implement
    // no need to do
}

int Lucci::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    int enemy_damage = ceil(this->atk + 0.05 * this->doriki);
    if (target->getHP() < 0.5 * target->getmaxHp())
    {
        enemy_damage = (int)ceil(1.2 * enemy_damage);
    }
    target->receiveDamage(enemy_damage);
    // ko cong morale do ko thman quy tac
    return enemy_damage;
}

int Lucci::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (this->energy < 25)
        return 0;
    this->energy -= 25;
    // Bỏ qua 50% phòng thủ
    int enemy_damage = (int)ceil(2.8 * atk);
    int passed = (int)ceil(enemy_damage + 0.5 * target->getdef());
    target->receiveDamage(passed);
    if (!target->isAlive() && target->isStrawHat())
        context.morale = context.morale - 10;
    return enemy_damage;
}

void Lucci::endTurn(BattleContext &context)
{
    // TODO: implement
    if (this->hp < 0.4 * this->maxHp)
        this->atk = ceil(1.05 * this->atk);
}

/*
 * Kaku
 */
Kaku::Kaku(string name, int hp, int atk, int def,
           int speed, int energy, int doriki)
    : CP9Agent(name, hp, atk, def, speed, energy, doriki)
{
    // TODO: implement
    // no need to do
}

int Kaku::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    int damage = (int)ceil(this->atk);
    target->receiveDamage(damage);
    if (!target->isAlive() && target->isStrawHat())
    {
        context.morale -= 5;
        if (context.morale < 0)
            context.morale = 0;
    }
    return damage;
}

int Kaku::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (this->energy < 20)
        return 0;
    this->energy -= 20;
    int damage1 = (int)ceil(1.2 * this->atk);
    int total_damage = damage1;
    target->receiveDamage(damage1);
    if (!target->isAlive() && target->isStrawHat())
    {
        context.morale -= 5;
        if (context.morale < 0)
            context.morale = 0;

        return damage1;
    }

    int damage2 = (int)ceil(this->atk);
    target->receiveDamage(damage2);
    total_damage += damage2;
    if (!target->isAlive() && target->isStrawHat())
    {
        context.morale -= 5;
        if (context.morale < 0)
            context.morale = 0;

        return total_damage;
    }

    int damage3 = (int)ceil(0.8 * this->atk);

    target->receiveDamage(damage3);
    total_damage += damage3;
    if (!target->isAlive() && target->isStrawHat())
    {
        context.morale -= 5;
        if (context.morale < 0)
            context.morale = 0;
    }

    return total_damage;
}

void Kaku::endTurn(BattleContext &context)
{
    // TODO: implement
    // no ned to do
}

/*
 * Jabra
 */
Jabra::Jabra(string name, int hp, int atk, int def,
             int speed, int energy, int doriki)
    : CP9Agent(name, hp, atk, def, speed, energy, doriki)

{
    // TODO: implement
    // no need to do
}

int Jabra::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    int damage = this->atk;
    target->receiveDamage(damage);
    return damage; // ko morale do co quy dinh o special
}

int Jabra::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (this->energy < 18)
        return 0;
    this->energy -= 18;
    int damage = (int)ceil(1.5 * this->atk);
    if (this->hp < 0.3 * this->maxHp)
        damage = (int)ceil(1.25 * damage);
    target->receiveDamage(damage);
    if (!target->isAlive() && target->isStrawHat())
    {
        context.morale -= 5;
        if (context.morale < 0)
            context.morale = 0;
    }
    return damage;
}

void Jabra::endTurn(BattleContext &context)
{
    // TODO: implement
    // no need to do
}

/*
 * Blueno
 */
Blueno::Blueno(string name, int hp, int atk, int def,
               int speed, int energy, int doriki)
    : CP9Agent(name, hp, atk, def, speed, energy, doriki)
{
    // TODO: implement
}

int Blueno::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    int damage = this->atk;
    target->receiveDamage(damage);
    if (!target->isAlive() && target->isStrawHat())
    {
        context.morale -= 5;
        if (context.morale < 0)
            context.morale = 0;
    }
    return damage;
}

int Blueno::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (this->energy < 15)
        return 0;
    this->energy -= 15;
    int damage = (int)ceil(1.3 * this->atk);
    // cap nhat hp
    if (this->hp > 0.5 * this->maxHp)
        damage += 20;
    if (this->hp <= 0.5 * this->maxHp)
        damage += 40;
    target->receiveDamage(damage);
    if (!target->isAlive() && target->isStrawHat())
    {
        context.morale -= 5;
        if (context.morale < 0)
            context.morale = 0;
    }
    return damage;
}

void Blueno::endTurn(BattleContext &context)
{
    // TODO: implement
    // no need to do
}

/*
 * Kalifa
 */
Kalifa::Kalifa(string name, int hp, int atk, int def,
               int speed, int energy, int doriki)
    : CP9Agent(name, hp, atk, def, speed, energy, doriki)
{
    // TODO: implement
}

int Kalifa::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    int damage = this->atk;
    target->receiveDamage(damage);
    return damage;
}

int Kalifa::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (this->energy < 18)
        return 0;
    this->energy -= 18;
    int damage = (int)ceil(1.4 * this->atk);
    int morale;
    if (target->getName() == "Nami")
    {
        morale = 12;
        context.morale -= morale;
    }
    else
    {
        morale = 8;
        context.morale -= morale;
    }
    int new_speed = target->getspeed() - 6;
    if (new_speed < 0)
        new_speed = 0;
    target->setspeed(new_speed);

    target->receiveDamage(damage);
    if (context.morale < 0)
        context.morale = 0;
    return damage;
}

void Kalifa::endTurn(BattleContext &context)
{
    // TODO: implement
    // no need to do
}

/*
 * Kumadori
 */
Kumadori::Kumadori(string name, int hp, int atk, int def,
                   int speed, int energy, int doriki)
    : CP9Agent(name, hp, atk, def, speed, energy, doriki)
{
    // TODO: implement
}

int Kumadori::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    int damage = this->atk;
    target->receiveDamage(damage);
    if (!target->isAlive() && target->isStrawHat())
    {
        context.morale -= 5;
        if (context.morale < 0)
            context.morale = 0;
    }
    return damage;
}

int Kumadori::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (this->energy < 16)
        return 0;
    this->energy -= 16;
    int damage = (int)ceil(30 + 0.1 * this->doriki);
    if (this->hp < 0.4 * this->maxHp)
        damage += 25;
    if (!target->isAlive() && target->isStrawHat())
    {
        context.morale -= 5;
        if (context.morale < 0)
            context.morale = 0;
    }
    return damage;
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
    : CP9Agent(name, hp, atk, def, speed, energy, doriki)
{
    // TODO: implement
}

int Fukurou::attack(Character *target, BattleContext &context)
{
    // TODO: implement
    int damage = this->atk;
    target->receiveDamage(damage);
    return damage;
}

int Fukurou::specialSkill(Character *target, BattleContext &context)
{
    // TODO: implement
    if (this->energy < 14)
        return 0;
    this->energy -= 14;

    int damage = ceil(1.3 * this->atk);
    if (target->getHP() == context.lowestStrawHatHP)
        damage += 20;
    target->receiveDamage(damage);
    if (!target->isAlive() && target->isStrawHat())
    {
        context.morale -= 6;
        if (context.morale < 0)
            context.morale = 0;
    }
    return damage;
}

void Fukurou::endTurn(BattleContext &context)
{
    // TODO: implement
}

/*
 * Building
 */
// do có cú pháp classname::classname(parameter) --> ko co kiểu trả về
Building::Building(string name, int hp)
{
    // TODO: implement
    this->name = name;
    this->hp = hp;
    this->maxHP = hp;
    if (hp > 0)
        this->destroyed = false;
    else
        this->destroyed = true;
}

Building::~Building()
{
    // TODO: implement if needed
    // no need to do
}

void Building::receiveDamage(int damage)
{
    // TODO: implement

    this->hp -= damage;
    if (hp <= 0)
    {
        this->hp = 0;
        this->destroyed = true;
    }
}

bool Building::isDestroyed() const
{
    // TODO: implement
    return this->destroyed;
}

void Building::onDestroyed(BattleContext &context)
{
    return;
    // no need to do
}

string Building::str() const
{
    // TODO: implement
    stringstream ss;
    ss << "Building [name=" << this->name << ", hp=" << this->hp
       << ", maxHP=" << this->maxHP << ", destroyed=" << this->destroyed << "]";
    return ss.str();
}

// them method
int Building::gethp() const
{
    return hp; // do ben hien tai
}

int Building::getmaxHP() const
{
    return maxHP; // do ben toi da
}
string Building::getname() const
{
    return name;
}

//
/*
 * MainGate
 */
MainGate::MainGate(string name, int hp) : Building(name, hp) {}

void MainGate::applyEffect(BattleContext &context)
{
    // TODO: implement
    if (!this->isDestroyed())
        context.rescueProgress = context.rescueProgress;
}

void MainGate::onDestroyed(BattleContext &context)
{
    // TODO: implement
    if (this->isDestroyed())
    {
        context.mainGateDestroyed = true;
        context.rescueProgress += 20;
        context.morale += 5;
        if (context.morale > 100)
            context.morale = 100;
        if (context.rescueProgress > 100)
            context.rescueProgress = 100;
    }
}

/*
 * Courthouse
 */
Courthouse::Courthouse(string name, int hp) : Building(name, hp) {}

void Courthouse::applyEffect(BattleContext &context)
{
    // TODO: implement
    if (!this->isDestroyed())
    {
        context.alarmLevel += 5;
        if (context.alarmLevel > 100)
            context.alarmLevel = 100;
    }
}

void Courthouse::onDestroyed(BattleContext &context)
{
    // TODO: implement
    if (this->isDestroyed())
    {
        context.alarmLevel -= 20;
        if (context.alarmLevel < 0)
            context.alarmLevel = 0;
    }
}

/*
 * TowerOfJustice
 */
TowerOfJustice::TowerOfJustice(string name, int hp) : Building(name, hp) {}

void TowerOfJustice::applyEffect(BattleContext &context)
{
    // TODO: implement
    if (context.mainGateDestroyed && (!context.robinRescued))
    {
        context.rescueProgress += 5;
        if (context.rescueProgress >= 100)
        {

            context.robinRescued = true;
            context.morale += 10;
            context.rescueProgress = 100;
            if (context.morale > 100)
                context.morale = 100;
        }
    }
}

/*
 * BridgeOfHesitation
 */
BridgeOfHesitation::BridgeOfHesitation(string name, int hp) : Building(name, hp) {}

void BridgeOfHesitation::applyEffect(BattleContext &context)
{
    // TODO: implement
    if (context.robinRescued)
    {
        context.bridgeOpened = true;
        context.escapeProgress += 5;
        if (context.escapeProgress >= 100)
        {
            // end
            context.battleEnded = true;
            context.resultCode = "STRAW_HAT_WIN";
            context.escapeProgress = 100;
        }
    }
}

/*
 * BusterCallShip
 */
BusterCallShip::BusterCallShip(string name, int hp) : Building(name, hp) {}

void BusterCallShip::applyEffect(BattleContext &context)
{
    // TODO: implement
    if (!this->isDestroyed())
    {
        context.busterCallTimer -= 1;
        if (context.busterCallTimer <= 0)
        {
            context.battleEnded = true;
            context.resultCode = "BUSTER_CALL";
            context.busterCallTimer = 0;
        }
    }
}

void BusterCallShip::onDestroyed(BattleContext &context)
{
    // TODO: implement
    if (this->isDestroyed())
        context.busterCallTimer += 3;
}

/*
 * EniesLobbyBattle
 */
EniesLobbyBattle::EniesLobbyBattle(const string &filename)
{
    // TODO: implement
    // constructor
    this->strawHats = nullptr;
    this->strawHatCount = 0;
    this->cp9Agents = nullptr;
    this->cp9Count = 0;
    this->buildings = nullptr;
    this->buildingCount = 0;
    this->turnOrder = nullptr;
    this->maxTurns = 0;
    loadFromFile(filename);
    // bước này là bước khởi tạo các giá trị có thể khởi tạo để tránh giá trị rác
}

EniesLobbyBattle::~EniesLobbyBattle()
{
    // TODO: implement
    for (int i = 0; i < strawHatCount; i++)
    {
        delete strawHats[i];
        strawHats[i] = nullptr;
    }
    delete[] strawHats;
    strawHats = nullptr;

    for (int i = 0; i < cp9Count; i++)
    {
        delete cp9Agents[i];
        cp9Agents[i] = nullptr;
    }
    delete[] cp9Agents;

    for (int i = 0; i < buildingCount; i++)
    {
        delete buildings[i];
        buildings[i] = nullptr;
    }
    delete[] buildings;

    // đối với danh sách liên kết , ta xóa lần lượt từ đầu cho đến cuối
    turnOrder = delete_all_node(turnOrder);
}

void EniesLobbyBattle::loadFromFile(const string &filename)
{
    // TODO: implement
    ifstream myfile(filename);
    if (!myfile.is_open())
        return;
    string line;
    while (getline(myfile, line)) // doc cho den khi het
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        // tao ra dong ao
        string type;
        ss >> type;
        if (type == "CONTEXT")
        {
            int morale;          // tinh thần phe mũ rơm <100
            int alarmLevel;      // mức báo động tại Enies Lobby<100
            int rescueProgress;  // tiến độ giải cứu Robin<100
            int escapeProgress;  // tiến độ rút lui khởi enies lobby<100
            int busterCallTimer; // số lượt còn lại trước khi buster xảy ra>9
            int maxT;            // số lượt tối đa của trận đánh
            ss >> morale >> alarmLevel >> rescueProgress >> escapeProgress >> busterCallTimer >> maxT;
            context.morale = morale;
            context.alarmLevel = alarmLevel;
            context.rescueProgress = rescueProgress;
            context.escapeProgress = escapeProgress;
            context.busterCallTimer = busterCallTimer;
            maxTurns = maxT;
            // limit
            if (context.morale < 0)
                context.morale = 0;
            if (context.morale > 100)
                context.morale = 100;
            if (context.alarmLevel < 0)
                context.alarmLevel = 0;
            if (context.alarmLevel > 100)
                context.alarmLevel = 100;
            if (context.rescueProgress < 0)
                context.rescueProgress = 0;
            if (context.rescueProgress > 100)
                context.rescueProgress = 100;
            if (context.escapeProgress < 0)
                context.escapeProgress = 0;
            if (context.escapeProgress > 100)
                context.escapeProgress = 100;
            if (context.busterCallTimer < 0)
                context.busterCallTimer = 0;
        }
        else if (type == "STRAW_HAT")
        {
            string name;
            int hp, atk, def, speed, energy;
            long long bounty;

            ss >> name >> hp >> atk >> def >> speed >> energy >> bounty;
            Character *straw = nullptr;

            if (name == "Luffy")
            {
                straw = new Luffy(name, hp, atk, def, speed, energy, bounty);
                addStrawHat(straw);
            }
            else if (name == "Zoro")
            {
                straw = new Zoro(name, hp, atk, def, speed, energy, bounty);
                addStrawHat(straw);
            }
            else if (name == "Sanji")
            {
                straw = new Sanji(name, hp, atk, def, speed, energy, bounty);
                addStrawHat(straw);
            }
            else if (name == "Nami")
            {
                straw = new Nami(name, hp, atk, def, speed, energy, bounty);
                addStrawHat(straw);
            }
            else if (name == "Chopper")
            {
                straw = new Chopper(name, hp, atk, def, speed, energy, bounty);
                addStrawHat(straw);
            }
            else if (name == "Usopp")
            {
                straw = new Usopp(name, hp, atk, def, speed, energy, bounty);
                addStrawHat(straw);
            }
            else if (name == "Franky")
            {
                straw = new Franky(name, hp, atk, def, speed, energy, bounty);
                addStrawHat(straw);
            }

            if (straw != nullptr)
            {
                addStrawHat(straw); // add thêm nhân vật mới
            }
        }

        else if (type == "CP9")
        {
            string name;
            int hp, atk, def, speed, energy, doriki;

            ss >> name >> hp >> atk >> def >> speed >> energy >> doriki;

            Character *agent = nullptr;

            if (name == "Lucci")
            {
                agent = new Lucci(name, hp, atk, def, speed, energy, doriki);
                addCP9Agent(agent);
            }
            else if (name == "Kaku")
            {
                agent = new Kaku(name, hp, atk, def, speed, energy, doriki);
                addCP9Agent(agent);
            }
            else if (name == "Jabra")
            {
                agent = new Jabra(name, hp, atk, def, speed, energy, doriki);
                addCP9Agent(agent);
            }
            else if (name == "Blueno")
            {
                agent = new Blueno(name, hp, atk, def, speed, energy, doriki);
                addCP9Agent(agent);
            }
            else if (name == "Kalifa")
            {
                agent = new Kalifa(name, hp, atk, def, speed, energy, doriki);
                addCP9Agent(agent);
            }
            else if (name == "Kumadori")
            {
                agent = new Kumadori(name, hp, atk, def, speed, energy, doriki);
                addCP9Agent(agent);
            }
            else if (name == "Fukurou")
            {
                agent = new Fukurou(name, hp, atk, def, speed, energy, doriki);
                addCP9Agent(agent);
            }

            if (agent != nullptr)
            {
                addCP9Agent(agent);
            }
        }
        else if (type == "BUILDING")
        {
            string name;
            int hp;

            ss >> name >> hp;

            Building *building = nullptr;

            if (name == "MainGate")
            {
                building = new MainGate(name, hp);
                addBuilding(building);
            }
            else if (name == "Courthouse")
            {
                building = new Courthouse(name, hp);
                addBuilding(building);
            }
            else if (name == "TowerOfJustice")
            {
                building = new TowerOfJustice(name, hp);
                addBuilding(building);
            }
            else if (name == "BridgeOfHesitation")
            {
                building = new BridgeOfHesitation(name, hp);
                addBuilding(building);
            }
            else if (name == "BusterCallShip")
            {
                building = new BusterCallShip(name, hp);
                addBuilding(building);
            }

            if (building != nullptr)
            {
                addBuilding(building);
            }
        }
    }
    myfile.close(); // dong file
    // gọi phương thức turnOrder
    buildTurnOrder();
}

void EniesLobbyBattle::addStrawHat(Character *character)
{
    // TODO: implement
    // xin cpd mang strahats moiw
    Character **newStrawHats = new Character *[strawHatCount + 1];
    // đã new thì phải cập nhật lại các th.viên cũ
    for (int i = 0; i < strawHatCount; i++)
    {
        newStrawHats[i] = strawHats[i];
    }
    newStrawHats[strawHatCount] = character;
    // gp mang cu
    delete[] strawHats;
    strawHats = newStrawHats;
    strawHatCount++;
}

void EniesLobbyBattle::addCP9Agent(Character *character)
{
    // TODO: implement
    Character **newCP9 = new Character *[cp9Count + 1];
    // đã new thì phải cập nhật lại các th.viên cũ
    for (int i = 0; i < cp9Count; i++)
    {
        newCP9[i] = cp9Agents[i];
    }
    newCP9[cp9Count] = character;
    // gp mang cu
    delete[] cp9Agents;
    cp9Agents = newCP9;
    cp9Count++;
}

void EniesLobbyBattle::addBuilding(Building *building)
{
    // TODO: implement
    Building **newBuilding = new Building *[buildingCount + 1];
    // đã new thì phải cập nhật lại các th.viên cũ
    for (int i = 0; i < buildingCount; i++)
    {
        newBuilding[i] = buildings[i];
    }
    newBuilding[buildingCount] = building;
    // gp mang cu
    delete[] buildings;
    buildings = newBuilding;
    buildingCount++;
}

void EniesLobbyBattle::buildTurnOrder()
{
    // TODO: implement
    // thêm một nút vào đầu tiên
    // tạo ra 1 con trỏ mới kiểu turnOrder
    TurnNode *head = new TurnNode;
    TurnNode *cur = head;
    // ko có ghi là TurnNode *cur= new TurnNode ;
    //  cur= head ; là sai do cur được cp 1 địa chỉ -->gán vậy thì bộ nhớ bị rò rỉ
    // nói chung nếu cpd thì phải sd vùng nhớ đó chứ ko nên trỏ đi đâu tránh rò rỉ
    // gan head cho nv dau tien
    head->data = strawHats[0];
    head->next = nullptr;

    // add tất cả các nút tiếp theo vào
    // do head->next la nullptr nen ta lan luot add vao
    // Mũ rơm
    for (int i = 1; i < strawHatCount; i++)
    {
        TurnNode *newNode = new TurnNode;
        cur->next = newNode;
        newNode->data = strawHats[i];
        newNode->next = nullptr;

        cur = newNode; // ko ro ri do ko cpd
    }
    // CP9
    for (int i = 0; i < cp9Count; i++)
    {
        TurnNode *new_Node = new TurnNode;
        cur->next = new_Node;
        new_Node->data = cp9Agents[i];
        new_Node->next = nullptr;
        cur = new_Node;
    }
}

void EniesLobbyBattle::runBattle()
{
    // TO DO
    while (!context.battleEnded && context.turnCount < maxTurns)
    {
        if (turnOrder == nullptr)
            break;

        TurnNode *cur = turnOrder;
        TurnNode *head = turnOrder;
        Character *curChar = cur->data;
        if (curChar != nullptr && curChar->isAlive())
        {
            processTurn(curChar);
        }
        // timf pt cuoi
        while (true)
        {
            if (cur->next == nullptr)
            {
                break;
            }
            cur = cur->next; // cap nhat cur
        }
        // chuyển head
        turnOrder = turnOrder->next;
        // gan tail vao
        cur->next = head;
        head->next = nullptr;
        processBuildings();
        context.turnCount += 1;
        checkEndCondition();
        if (context.turnCount == maxTurns && !context.battleEnded)
        {
            context.battleEnded = true;
            context.resultCode = "TIME_OUT";
        }
    }
}

void EniesLobbyBattle::processTurn(Character *character)
{
    // TODO: implement
    if (character == nullptr || !character->isAlive())
        return;
    Character *char_target = nullptr;
    Building *build_target = nullptr;

    if (character->isStrawHat())
    {
        if (character->getName() == "Chopper" && character->getEnergy() >= 15)
        {
            // tìm minHp
            int minHp = INT_MAX;

            Character *lowestHp_inStraw = nullptr;
            for (int i = 0; i < strawHatCount; i++)
            {
                if (strawHats[i] != nullptr && strawHats[i]->isAlive())
                {
                    if (strawHats[i]->getHP() < minHp)
                    {
                        minHp = strawHats[i]->getHP();
                        lowestHp_inStraw = strawHats[i];
                    }
                }
            }
            if (lowestHp_inStraw != nullptr)
            {
                character->specialSkill(lowestHp_inStraw, context);
                character->endTurn(context);
                return; // thoát ko xét các mục tiêu khác do ưu tiên sô 1
            }
        }
        // nếu ko phải chopper thì xét tiếp đến các ưu tiên khác
        Building *temp_maingate = nullptr;
        Building *temp_court = nullptr;
        Building *temp_bus = nullptr;
        Building *temp_bridge = nullptr;
        bool maingate_destroyed = true;
        bool courthouse_destroyed = true;
        bool buster_ship_destroyed = true;
        bool bridge_destroyed = true;
        // lấy thông tin building
        for (int i = 0; i < buildingCount; i++)
        {
            if (buildings[i]->getname() == "Courthouse")
            {
                if (buildings[i]->isDestroyed())
                    courthouse_destroyed = true;
                else
                    courthouse_destroyed = false;
                temp_court = buildings[i];
            }

            if (buildings[i]->getname() == "BusterCallShip")
            {
                if (buildings[i]->isDestroyed())
                    buster_ship_destroyed = true;
                else
                    buster_ship_destroyed = false;
                temp_bus = buildings[i];
            }

            if (buildings[i]->getname() == "BridgeOfHesitation")
            {
                if (buildings[i]->isDestroyed())
                    bridge_destroyed = true;
                else
                    bridge_destroyed = false;
                temp_bridge = buildings[i];
            }

            if (buildings[i]->getname() == "MainGate")
            {
                if (buildings[i]->isDestroyed())
                    maingate_destroyed = true;
                else
                    maingate_destroyed = false;
                temp_maingate = buildings[i];
            }
        }

        // Quy tắc chọn mục tiêu
        if (!maingate_destroyed)
        {
            build_target = temp_maingate;
        }
        else if (maingate_destroyed && context.alarmLevel >= 50 && !courthouse_destroyed)
        {
            build_target = temp_court;
        }
        else if (context.busterCallTimer <= 5 && !buster_ship_destroyed)
        {
            build_target = temp_bus;
        }
        else if (!context.robinRescued)
        {
            for (int i = 0; i < cp9Count; i++)
            {
                if (cp9Agents[i]->isAlive())
                {
                    char_target = cp9Agents[i];
                    break;
                }
            }
        }
        else if (context.robinRescued)
        {
            if (!bridge_destroyed && temp_bridge != nullptr)
                build_target = temp_bridge;
            else if (bridge_destroyed || temp_bridge == nullptr)
            {
                for (int i = 0; i < cp9Count; i++)
                {
                    if (cp9Agents[i]->isAlive())
                    {
                        char_target = cp9Agents[i];
                        break;
                    }
                }
            }
        }
    }
    // CP9 ---------------------------------------------------------
    else if (character->isCP9())
    {
        for (int i = 0; i < strawHatCount; i++)
        {
            if (strawHats[i]->isAlive())
            {
                char_target = strawHats[i];
                break;
            }
        }
    }
    // Nếu mục tiêu là nhân vật -------------------------------
    // ktra xem còn đủ năng lựng ko
    if (char_target != nullptr)
    {
        if (character->getEnergy() >= character->getSpecialSkillCost())
        {
            character->specialSkill(char_target, context);
        }
        else
        {
            character->attack(char_target, context);
        }
    }
    if (build_target != nullptr)
    {
        if (character->getEnergy() >= character->getSpecialSkillCost())
        {
            character->specialSkill(build_target, context);
        }
        else
        {
            character->attack(build_target, context);
            if (build_target->isDestroyed())
                build_target->onDestroyed(context);
        }
    }
    character->endTurn(context);
}

void EniesLobbyBattle::processBuildings()
{
    // TODO: implement
    for (int i = 0; i < buildingCount; i++)
    {
        if (buildings[i] != nullptr && !buildings[i]->isDestroyed())
            buildings[i]->applyEffect(context);
    }
}

void EniesLobbyBattle::checkEndCondition()
{
    // TODO: implement
    if (context.robinRescued == true && context.escapeProgress >= 100)
    {
        context.battleEnded = true;
        context.resultCode = "STRAW_HAT_WIN";
        return;
    }
    else if (context.busterCallTimer <= 0)
    {
        context.battleEnded = true;
        context.resultCode = "BUSTER_CALL";
        return;
    }
    // Nếu mũ rơm bị hạ gục toàn bộ
    bool cp9_win = true;
    for (int i = 0; i < strawHatCount; i++)
    {
        if (strawHats[i]->isAlive())
        {
            cp9_win = false;
        }
    }
    if (cp9_win)
    {
        context.battleEnded = true;
        context.resultCode = "CP9_WIN";
        return;
    }
    // Nếu CP9 bị hạ gục toàn bộ
    bool str_win = true;
    for (int i = 0; i < cp9Count; i++)
    {
        if (cp9Agents[i]->isAlive())
        {
            str_win = false;
        }
    }
    if (str_win)
    {
        context.battleEnded = true;
        context.resultCode = "STRAW_HAT_WIN_BY_DEFEAT_CP9";
        return;
    }
    //----------------------
    else if (context.turnCount >= maxTurns)
    {
        context.battleEnded = true;
        context.resultCode = "TIME_OUT";
        return;
    }
}

string EniesLobbyBattle::getResult() const
{
    // TODO: implement
    stringstream ss;
    ss << context.resultCode << " " << context.turnCount << " " << context.morale
       << " " << context.alarmLevel << " " << context.rescueProgress << " " << context.escapeProgress
       << " " << context.busterCallTimer;
    return ss.str();
}
/*===================================*/
// add method for enieslobby battle
int EniesLobbyBattle::findLowestHp()
{
    int lowest = INT_MAX;
    for (int i = 0; i < strawHatCount; i++)
    {
        if (strawHats[i]->isAlive() && strawHats[i]->getHP() < lowest)
        {
            lowest = strawHats[i]->getHP();
        }
    }
    return lowest;
}
void EniesLobbyBattle::assign_minHP_Murom(Character *character)
{
    // tim mu rom con song
    if (!character->isAlive())
        return;
    // gan target cho doi thu bk ben team mu ron
    Character *target = nullptr;
    // find ng con song dau tien gan cho target
    for (int i = 0; i < strawHatCount; i++)
    {
        if (strawHats[i]->isAlive())
        {
            target = strawHats[i];
            break;
        }
    }
    if (target == nullptr)
        return;

    if (character->getName() == "Fukurou" && character->getEnergy() >= 14)
    {
        int lowestHp = findLowestHp();
        context.lowestStrawHatHP = lowestHp;
        // goi ham
        character->specialSkill(target, context);
    }
}

TurnNode *EniesLobbyBattle ::delete_all_node(TurnNode *head)
{
    if (head == nullptr)
        return nullptr;
    TurnNode *cur = head;
    TurnNode *del = nullptr;
    while (cur != nullptr)
    {
        del = cur;
        cur = cur->next;
        delete del;
    }
    return nullptr;
}
// the aim for fukurou
/*===================================*/
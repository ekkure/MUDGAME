#include"Player.h"


void Player::addexp(int e) {
    exp = exp + e;

    cout << "你获得 " << e << "exp" << endl;
    if (exp >= maxexp) {
        level += 1;
        cout << "Your lv up to :" << level << endl;
        strength += 10;
        maxHP += 30;
        currentHP += 30;
        agility += 10;
        maxmana += 40;
        currentmana += 40;  //各项属性增加
        exp = exp - maxexp;
        maxexp = maxexp + 100;
        for (auto it = Skill.begin(); it != Skill.end(); ++it)   //增加技能伤害
            it->second = it->second + 20;
    }
}

void Player::equipWeapon(Item& weapon) {                                // 装备武器
    if (weapon.gettype() == ItemType::WEAPON) {
        equippedWeapon = weapon;
        cout << "Equipped " << weapon.getname() << " as weapon" << endl;
        weapon.isused = 1;
    }
    else {
        cout << "Invalid item type for weapon!" << endl;
    }
}

void Player::equipArmor(Item& armor) {                  //装备护甲
    if (armor.gettype() == ItemType::ARMOR) {
        equippedArmor = armor;
        cout << "Equipped " << armor.getname() << " as armor" << endl;
        armor.isused = 1;
    }
    else {
        cout << "Invalid item type for armor!" << endl;
    }
}

void Player::drop(Item& item) {  //扔物品的函数
    int count = 0;
    for (auto e : inventory)
        if (e.getname() == item.getname())break;
        else count++;
    inventory.erase(inventory.begin() + count);  //从vector中erase掉
}

void Player::useItem(Item& item) {
    // 使用药包
    if (item.gettype() == ItemType::HEALING_ITEM) {
        currentHP += item.gethealing();
        currentmana += item.gethealing() / 2;
        if (currentHP > maxHP) {
            currentHP = maxHP;
        }
        if (currentmana > maxmana) {
            currentmana = maxmana;
        }
        cout << "使用 " << item.getname() << " 恢复了 " << item.gethealing() << " 点血量" << endl;
        drop(item);    //调用drop函数 使使用的药品消失
       
    }
    else {
        cout << "Invalid item type for use!" << endl;
    }
}

void Player::attackEnemy(Enemy& enemy, int choice) {//战斗函数
    string s[3];     //用于储存技能的名字 方便后续打印
    int nn = 0;
    for (auto it = Skill.begin(); it != Skill.end(); ++it) {
        s[nn] = it->first;   //使用迭代器遍历map容器
        nn++;
    }
    int damage;
    if (choice == 4)
        damage = strength + equippedWeapon.getattdamage();
    else {
        if (currentmana >= 10) {

            switch (choice) {
            case 1:damage = Skill["破灭虚妄"] + equippedWeapon.getattdamage(); currentmana -= 10; break;
            case 2:damage = Skill["日落孤枪"] + equippedWeapon.getattdamage(); currentmana -= 10; break;
            case 3:damage = Skill["背水一战"] + equippedWeapon.getattdamage(); currentmana -= 10; break;
            default: cout << "No such skill 自动平a" << endl; damage = strength + equippedWeapon.getattdamage();
            }
        }
        else {
            cout << "你没有足够的蓝量 自动普通攻击" << endl;
            damage = strength + equippedWeapon.getattdamage();
        }
    }

    int cur=enemy.getHp() - damage;
    enemy.setHp(cur);
    if (choice == 4)
        cout << "你攻击了敌人 " << enemy.getname() << " 造成 " << damage << "  伤害" << endl;
    else
    {
        cout<<"你使用 "<<s[choice-1]<<" 重创了敌人，造成 "<<damage << "  伤害" << endl;
    }
    //输出打印战斗信息
};

string Player::getname() {    //get set 方法
    return name;
}
void Player::setname(string name) {
    this->name = name;
}
int Player::getstrength() {
    return strength;
};
void Player::setstrength(int stren) {
    strength = stren;
}
int Player::getagility() {
    return agility;
}
void Player::setagility(int agili) {
    agility = agili;
}
int Player::getlevel() {
    return level;
}
void Player::setlevel(int lv) {
    level = lv;
}
int Player::getmoney() {
    return money;
}
void Player::setmoney(int mon) {
    money = mon;
}
int Player::getMaxHP() {
    return maxHP;
}
void Player::setMaxHP(int max) {
    maxHP = max;
}
int Player::getcurrentHP() {
    return currentHP;
}
void Player::setcurrent(int current) {
    currentHP = current;
}
int Player::getexp() {
    return exp;
}
void Player::setexp(int expp) {
    exp = expp;
}
int Player::getmaxexp() {
    return maxexp;
}
void Player::setmaxexp(int max) {
    maxexp = max;
}
int Player::getcurrmana() {
    return currentmana;
}
void Player::setcurrmana(int curr) {
    currentmana = curr;
}
int Player::getmaxmana() {
    return maxmana;
}
void Player::setmaxmana(int max) {
    maxmana = max;
}
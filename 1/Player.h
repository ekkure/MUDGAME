#ifndef PLAYER_H
#define PLAYER_H
#include"Item.h"
#include"Enemy.h"
#include<map>
#include<vector>
// 玩家类
class Player {
public:
    map<string, int> Skill = { {"破灭虚妄",20} ,{"日落孤枪",25} ,{"背水一战",30} };
    vector<Item> inventory;
    Item equippedWeapon;
    Item equippedArmor;
    string getname();
    void setname(string name);
    int getstrength();
    void setstrength(int stren);
    int getagility();
    void setagility(int agili);
    int getlevel();
    void setlevel(int lv);
    int getmoney();
    void setmoney(int mon);
    int getMaxHP();
    void setMaxHP(int max);
    int getcurrentHP();
    void setcurrent(int current);
    int getexp();
    void setexp(int expp);
    int getmaxexp();
    void setmaxexp(int max);
    int getcurrmana();
    void setcurrmana(int curr);
    int getmaxmana();
    void setmaxmana(int max);
    void addexp(int e);
    void equipWeapon(Item& weapon);
    void equipArmor(Item& armor);
    void drop(Item& item);
    void useItem(Item& item);
    void attackEnemy(Enemy& enemy, int choice);

private:
    string name;
    int strength;
    int agility;
    int level;
    int money;
    int maxHP;
    int currentHP;
    int exp;
    int maxexp;
    int maxmana;  //蓝量
    int currentmana;
    // int damage_absorption;



};

#endif
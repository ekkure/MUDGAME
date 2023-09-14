#ifndef ENEMY_H
#define ENEMY_H
#include<String>

using namespace std;

// µ–»À¿‡
class Enemy {
public:
    Enemy(){};
    Enemy(string name, int strength, int hp, int maxhp, int agility) :name(name),strength(strength),health(hp),maxhealth(maxhp),agility(agility){
    }
    string getname();
    void setname(string name);
    int getstrength();
    void setstr(int str);
    int getHp();
    void setHp(int hp);
    int getmaxHp();
    void setmaxHp(int max);
    int getagility();
    void setagi(int agi);
private:
    string name;
    int strength;
    int health;
    int maxhealth;
    int agility;
};
#endif
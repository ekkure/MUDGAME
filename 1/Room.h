#ifndef ROOM_H
#define ROOM_H

#include"Enemy.h"
#include"Item.h"
#include <iostream>
#include <vector>

// 房间类
class Room {
public:
    string name;
    int numm;
    vector<Item> items;
    vector<Enemy> enemies;
    Room* towards[5] = { nullptr,nullptr,nullptr,nullptr,nullptr };  // 东 南 西 北
    bool isfirstde = 1;
    bool isEnedead = 0;
    bool iscleaned = 0;
    bool taskdone = 0;
    string NPC[6];
    vector<Item> enemyitems;

    void NPCtalk();
};

#endif
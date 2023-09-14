#ifndef GAME_H
#define GAME_H
#include"Player.h"
#include"Map.h"
#include"Room.h"
#include"Shop.h"
// ��Ϸ��
class Game {
public:
    Player player;
    Room currentRoom;
    Shop shop;
    Map map;

    void initialize(int cho);
    //������������
    void displayRoom();

    void move(string direction);

    void pickUpItem(const string& itemName);

    void dropItem(const string& itemName);

    void displayInventory();

    void displayShop();

    void buyItem(const string& itemName);

    void sellItem(const string& itemName);

    void Whatbeingused();

    int fight(Enemy& badguy);
};

#endif
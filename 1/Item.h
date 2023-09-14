#ifndef ITEM_H
#define ITEM_H
#include<string>
#include <iostream>
using namespace std;

// 枚举类型表示物品类型

enum ItemType { //枚举类型
    WEAPON,
    ARMOR,
    HEALING_ITEM,
    MONEY
};


// 物品类
class Item {
public:
    bool isused = 0;
    Item() {};
    Item(string name, int price, ItemType type, int attackdam, int defen, int healing);
    string getname();
    int getprice();
    ItemType gettype();
    int getattdamage();
    int getdefense();
    int gethealing();
    void setname(string name);
    void setprice(int price);
    void setattd(int attk);
    void setdefen(int defen);
    void sethealing(int heal);
    void settype(ItemType type) {
        this->type = type;
    }
    //输入运算符重载
    friend istream& operator>>(istream& input, Item& item) {
        input >> item.name >> item.price;
        int type;
        input >> type;
        item.type = static_cast<ItemType>(type); //对于枚举类型 转化成int 再保存
        input >> item.attackDamage >> item.defense >> item.healingAmount >> item.isused;
        return input;
    }

    // 输出运算符重载
    friend ostream& operator<<(ostream& output, const Item& item) {
        output << item.name << ' ' << item.price << ' ';
        output << static_cast<int>(item.type) << ' ';
        output << item.attackDamage << ' ' << item.defense << ' ';
        output << item.healingAmount << ' ' << item.isused <<' ';
        return output;
    }

private:  //各种私有属性
    string name;
    int price;
    ItemType type;
    int attackDamage;
    int defense;
    int healingAmount;
};
#endif
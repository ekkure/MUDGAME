#ifndef ITEM_H
#define ITEM_H
#include<string>
#include <iostream>
using namespace std;

// ö�����ͱ�ʾ��Ʒ����

enum ItemType { //ö������
    WEAPON,
    ARMOR,
    HEALING_ITEM,
    MONEY
};


// ��Ʒ��
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
    //�������������
    friend istream& operator>>(istream& input, Item& item) {
        input >> item.name >> item.price;
        int type;
        input >> type;
        item.type = static_cast<ItemType>(type); //����ö������ ת����int �ٱ���
        input >> item.attackDamage >> item.defense >> item.healingAmount >> item.isused;
        return input;
    }

    // ������������
    friend ostream& operator<<(ostream& output, const Item& item) {
        output << item.name << ' ' << item.price << ' ';
        output << static_cast<int>(item.type) << ' ';
        output << item.attackDamage << ' ' << item.defense << ' ';
        output << item.healingAmount << ' ' << item.isused <<' ';
        return output;
    }

private:  //����˽������
    string name;
    int price;
    ItemType type;
    int attackDamage;
    int defense;
    int healingAmount;
};
#endif
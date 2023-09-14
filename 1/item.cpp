#include"Item.h"

//get set ·½·¨
Item::Item(string name, int price, ItemType type, int attackdam, int defen, int healing):name(name),price(price),type(type),attackDamage(attackdam),defense(defen),healingAmount(healing)  {

};
string Item::getname() {
    return name;
};
int Item::getprice() {
    return price;
};
ItemType Item::gettype() {
    return type;
};
int Item::getattdamage() {
    return attackDamage;
};
int Item::getdefense() {
    return defense;
};
int Item::gethealing() {
    return healingAmount;
};
void Item::setname(string name) {
    this->name = name;
};
void Item::setprice(int price) {
    this->price = price;
};
void Item::setattd(int attk) {
    this->attackDamage = attk;
};
void Item::setdefen(int defen) {
    defense = defen;
};
void Item::sethealing(int heal) {
    healingAmount = heal;
};
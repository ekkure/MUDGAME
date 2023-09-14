#include"Enemy.h"
//get set·½·¨

string Enemy::getname() {
	return name;
};

void Enemy::setname(string name) {
	this->name = name;
};

int Enemy::getstrength() {
	return strength;
};

void Enemy::setstr(int str) {
	strength = str;
};
int Enemy::getHp() {
	return health;
};
void Enemy::setHp(int hp) {
	health = hp;
};
int Enemy::getmaxHp() {
	return maxhealth;
};
void Enemy::setmaxHp(int max) {
	maxhealth = max;
};
int Enemy::getagility() {
	return agility;
}
void Enemy::setagi(int agi) {
	agility = agi;
};
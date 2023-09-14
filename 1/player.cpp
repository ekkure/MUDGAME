#include"Player.h"


void Player::addexp(int e) {
    exp = exp + e;

    cout << "���� " << e << "exp" << endl;
    if (exp >= maxexp) {
        level += 1;
        cout << "Your lv up to :" << level << endl;
        strength += 10;
        maxHP += 30;
        currentHP += 30;
        agility += 10;
        maxmana += 40;
        currentmana += 40;  //������������
        exp = exp - maxexp;
        maxexp = maxexp + 100;
        for (auto it = Skill.begin(); it != Skill.end(); ++it)   //���Ӽ����˺�
            it->second = it->second + 20;
    }
}

void Player::equipWeapon(Item& weapon) {                                // װ������
    if (weapon.gettype() == ItemType::WEAPON) {
        equippedWeapon = weapon;
        cout << "Equipped " << weapon.getname() << " as weapon" << endl;
        weapon.isused = 1;
    }
    else {
        cout << "Invalid item type for weapon!" << endl;
    }
}

void Player::equipArmor(Item& armor) {                  //װ������
    if (armor.gettype() == ItemType::ARMOR) {
        equippedArmor = armor;
        cout << "Equipped " << armor.getname() << " as armor" << endl;
        armor.isused = 1;
    }
    else {
        cout << "Invalid item type for armor!" << endl;
    }
}

void Player::drop(Item& item) {  //����Ʒ�ĺ���
    int count = 0;
    for (auto e : inventory)
        if (e.getname() == item.getname())break;
        else count++;
    inventory.erase(inventory.begin() + count);  //��vector��erase��
}

void Player::useItem(Item& item) {
    // ʹ��ҩ��
    if (item.gettype() == ItemType::HEALING_ITEM) {
        currentHP += item.gethealing();
        currentmana += item.gethealing() / 2;
        if (currentHP > maxHP) {
            currentHP = maxHP;
        }
        if (currentmana > maxmana) {
            currentmana = maxmana;
        }
        cout << "ʹ�� " << item.getname() << " �ָ��� " << item.gethealing() << " ��Ѫ��" << endl;
        drop(item);    //����drop���� ʹʹ�õ�ҩƷ��ʧ
       
    }
    else {
        cout << "Invalid item type for use!" << endl;
    }
}

void Player::attackEnemy(Enemy& enemy, int choice) {//ս������
    string s[3];     //���ڴ��漼�ܵ����� ���������ӡ
    int nn = 0;
    for (auto it = Skill.begin(); it != Skill.end(); ++it) {
        s[nn] = it->first;   //ʹ�õ���������map����
        nn++;
    }
    int damage;
    if (choice == 4)
        damage = strength + equippedWeapon.getattdamage();
    else {
        if (currentmana >= 10) {

            switch (choice) {
            case 1:damage = Skill["��������"] + equippedWeapon.getattdamage(); currentmana -= 10; break;
            case 2:damage = Skill["�����ǹ"] + equippedWeapon.getattdamage(); currentmana -= 10; break;
            case 3:damage = Skill["��ˮһս"] + equippedWeapon.getattdamage(); currentmana -= 10; break;
            default: cout << "No such skill �Զ�ƽa" << endl; damage = strength + equippedWeapon.getattdamage();
            }
        }
        else {
            cout << "��û���㹻������ �Զ���ͨ����" << endl;
            damage = strength + equippedWeapon.getattdamage();
        }
    }

    int cur=enemy.getHp() - damage;
    enemy.setHp(cur);
    if (choice == 4)
        cout << "�㹥���˵��� " << enemy.getname() << " ��� " << damage << "  �˺�" << endl;
    else
    {
        cout<<"��ʹ�� "<<s[choice-1]<<" �ش��˵��ˣ���� "<<damage << "  �˺�" << endl;
    }
    //�����ӡս����Ϣ
};

string Player::getname() {    //get set ����
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
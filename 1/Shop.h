#ifndef SHOP_H
#define SHOP_H
#include"Item.h"
#include<vector>
// �̵���
class Shop {
public:
    vector<Item> items;  //���ڴ�����۳���װ����ҩƷ
    void showList();
};

#endif
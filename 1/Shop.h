#ifndef SHOP_H
#define SHOP_H
#include"Item.h"
#include<vector>
// 商店类
class Shop {
public:
    vector<Item> items;  //用于储存可售出的装备和药品
    void showList();
};

#endif
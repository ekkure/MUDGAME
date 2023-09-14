#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <fstream> 
#include<windows.h>
#undef max
#include"Game.h"

void GameRun(Game game) {    //游戏运行函数
   

    int choice;
    string command;
    while (1) {
        int over = 1;
        int dea = 0;

        cout << "1.角色 2.战斗  3.探索房间  4.地图  5.商店  6.任务 7.对话  8.退出游戏" << endl;   //Game menu
        game.displayRoom();
        cout << "你要：" << endl;
        if (!(cin >> choice)) {
            cin.clear();                                          // 清除错误状态
            cin.ignore(numeric_limits<streamsize>::max(), '\n');// 忽略剩余的输入
            cout << "请输入有效的指令." << endl;
            continue;
        }
        switch (choice) {
        case 1: {
            cout << game.player.getname() << "： 1.状态  2.装备  3.背包" << endl;
            int t;
            cin >> t;
            if (t == 1) {     //显示玩家状态及属性
                cout << game.player.getname() << "    ";
                cout << "血量:  " << game.player.getcurrentHP() << "/" << game.player.getMaxHP() << endl;
                cout << "基础攻击力: " << game.player.getstrength() << "    护甲:" << game.player.equippedArmor.getdefense() << "     总攻击力 :" << game.player.equippedWeapon.getattdamage() + game.player.getstrength() << endl;
                cout << "等级：" << game.player.getlevel() << ", 经验：" << game.player.getexp() << " / " << game.player.getmaxexp() << endl;
            }
            else if (t == 2)//显示正在使用的武器护甲等
                game.Whatbeingused();
            else if (t == 3) { //显示正在使用的武器护甲 以及 背包中物品 并可替换使用等
                game.displayInventory();
                cout << endl << "你正在装备着的:" << endl;
                game.Whatbeingused();
                if (game.player.inventory.size() > 0) {
                    cout << endl << "1.使用  2.返回 ";
                    int cho;
                    if (!(cin >> cho)) {
                        cin.clear();                                          // 清除错误状态
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');// 忽略剩余的输入
                        cout << "请输入有效的指令." << endl;
                        break;
                    }
                   // cin >> cho;
                    if (cho == 2)
                        break;
                    else if(cho == 1)
                    {   
                        bool havew = 0, havea = 0;

                        Item* eqwe = nullptr; 
                        Item* eqar = nullptr;          //只用指针或引用 便于改变值 避免值传递中断
                        for (Item& item : game.player.inventory) {
                            if (item.isused == 1) {
                                if (item.gettype() == WEAPON) {    //寻找是否有在用的装备并使用指针临时保存
                                    havew = 1;
                                    eqwe = &item;
                                }
                                else if (item.gettype() == ARMOR) {
                                    havea = 1;
                                    eqar = &item;
                                }
                            }
                        }
                        cout << "你要使用:";
                        string itemName;
                        cin >> itemName;

                        bool have = 0;

                        for (Item& item : game.player.inventory)  //使用for-each 循环遍历容器 
                        {
                            if (item.getname() == itemName)   
                            {
                                //cout << item.getname() << endl;;
                                have = 1;                           //若存在这个物品  
                                if (item.gettype() == HEALING_ITEM) {//若类型为药品
                                 
                                    game.player.useItem(item);//直接使用
                                    break;
                                }
                                else {     //存在 但是用的是装备
                                    if (item.isused == 1) {//发现要使用的跟正在使用的一样 直接结束
                                        cout << "你正在使用"<<item.getname()<<endl;
                                        break;
                                    }
                                    else {  //与在使用的装备不同                  
                                        if (item.gettype() == WEAPON) {    //假设使用的为武器类型
                                            if (havew) {      //若已有装备的武器
                                                eqwe->isused = 0;//将装备的武器卸下
                                                item.isused = 1; //将要使用的武器装上去（通过一些特定的bool数）
                                                game.player.equippedWeapon = item;
                                            }
                                            else {
                                                item.isused = 1;//若没有已装备的武器
                                                game.player.equippedWeapon = item;//直接装备上去
                                            }
                                        }
                                        else if (item.gettype() == ARMOR) {
                                            if (havea) {
                                                eqar->isused = 0;
                                                item.isused = 1;
                                                game.player.equippedArmor = item;
                                            }
                                            else {
                                                item.isused = 1;
                                                game.player.equippedArmor = item;
                                            }
                                        }
                                    }
                                }                               
                            }
                        }//
                        if (have == 0)
                            cout << "背包中没有这个物品" << endl; //若遍历容器没有找到相应的Item
                    }

                    else {
                        cout << "这个指令可不行欧" << endl;
                    }
                }
                else
                    cout << "没有物品" << endl;
            }
        }; break;
        case 2: {
            cout << "输入你要战斗的敌人是（名字）:" << endl;
            for (auto it = game.currentRoom.enemies.begin(); it != game.currentRoom.enemies.end(); ++it)
                cout << it->getname() << "  :攻击力:" << it->getstrength() << "   HP:" << it->getHp() << endl;
            cout << endl;
            string oname;
            bool findv = 1;
            cin >> oname;
            Enemy* fightobject = nullptr;  //以Enemy* 为形参 便于操作
            for (auto it = game.currentRoom.enemies.begin();; ++it)
                if (it == game.currentRoom.enemies.end()) {
                    findv = 0;
                    break;          //没有找到对应的敌人
                }
                else if (it->getname() == oname) {
                    fightobject = &(*it); //找到敌人 用指针指向他 作为后续函数的形参
                    break;
                }
            if (!findv)
                cout << "这里没有 " << oname << endl;
            else {
                if (game.fight(*fightobject)==1) {
                    cout << "你获得了:" << endl;
                    for (Item& item : game.currentRoom.enemyitems) {
                        cout << item.getname() << endl;
                        game.player.inventory.push_back(item);
                        game.player.addexp(50);   //固定加50   //增加经验值
                    }

                    game.currentRoom.isEnedead = 1;  //设置敌人死亡bool数
                    bool y = game.map.checkTask(game.currentRoom); //检查任务是否完成并作出更新 做出提示

                    game.currentRoom.NPCtalk();            //输出一些故事情节
                    game.currentRoom.isfirstde = 0;
                    fightobject->setHp(fightobject->getmaxHp());
                    game.currentRoom.isEnedead = 0;// 怪兽回复血量  调回房间内敌人死亡bool数
                }
                
                else if(game.fight(*fightobject)==0){
                    cout << "败北了" << endl;
                    dea = 1;                 //通过fight函数返回值判断
                }
            }

        }; break;
        case 3: {
            if (game.currentRoom.iscleaned==0) {  //通过bool数判断房间是否已经clean 但可以通过刷新房间等方式刷新房间内物品
                cout << "你发现了 :";            

                for (auto it = game.currentRoom.items.begin(); it != game.currentRoom.items.end(); ++it) {
                    game.player.inventory.push_back(*it);
                    cout << it->getname() << "    ";     //将房间内物品 push到人物背包中  
                }
                cout << "200 money" << endl;

                game.player.setmoney(game.player.getmoney() + 200);
                game.currentRoom.iscleaned = 1;                   
                game.map.rooms[game.currentRoom.numm].iscleaned = 1;  /////设置刷新bool数
            }
            else {
                cout << "没有物品了" << endl;
            }

        }; break;
        case 4: {
            cout << "你现在位于：" << game.currentRoom.name << endl;
            cout << "地图:" << endl;
            ShowMap();
            cout << "输入任何按键进入操作地图";
            string direction;

            if (!(cin >> direction)) {
                cin.clear();                                          // 清除错误状态
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 忽略剩余的输入
                cout << "你不能去那里，请输入有效操作" << endl;
            }
            else
                game.move(direction);                               //必须加 game 否则为使用系统自带函数move


        }; break;
        case 5: {
            cout << "你想要：1.购买 2.卖出 3.退出" << endl;
            int choicee;
            if (!(cin >> choicee)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "请输入正确的命令！" << endl;
                break;
            }
            //cin >> choicee;
            if (choicee == 1) {
                game.shop.showList();
                string itemName;
                Item itemm;
                cout << "你有 " << game.player.getmoney() << " money" << endl;
                cout << "你要买:";
                cin >> itemName;
                int ishave = 0;
                for(Item& item:game.shop.items)
                    if (item.getname() == itemName) {        
                        ishave = 1;
                        itemm = item;                //在商店的vector中找到对应的Item 并用临时itemm保存 用作buy函数形参
                        break;
                    }
                if (!ishave) {
                    cout << "商店中没有名如 " << itemName << " 的物品" << endl;
                    break;
                }
                else {
                    cout << "请输入你要购买的数量:";
                    int count;
                   // cin >> count;
                    if (!(cin >> count)) {
                        cin.clear();                                          // 清除错误状态
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');// 忽略剩余的输入
                        cout << "请输入有效的数字来决定数量." << endl;
                    }
                    if (game.player.getmoney() < itemm.getprice() * count) {
                        cout << "你没有足够的钱来购买！" << endl;
                        break;
                    }
                    for (int i = 0; i < count; i++)
                        game.buyItem(itemName);
                    cout << "你购买了 " << itemName << "* " << count << endl;
                }
            }
            else if (choicee == 2) {
                game.displayInventory();
                cout << "你要卖(请输入装备的名字):";
                string itemName;
                cin >> itemName;
                bool ishavein = 0;
                for (Item& findt : game.player.inventory) {
                    if (findt.isused == 1)                   //防止卖出已装备的装备
                        continue;
                    if (findt.getname() == itemName) {
                        ishavein = 1;
                        break;
                    }
                }
                if (!ishavein)
                    cout << "空闲仓库中没有你要卖的..." << endl;
                else {
                    cout << "请输入你想要卖出的数量:";
                    int count=0, x = 0;
                    if (!(cin >> count)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "请输入正确的数量！" << endl;
                        break;
                    }
                    //cin >> count;
                    for (Item& lookfor : game.player.inventory) {
                        if (lookfor.isused == 1)
                            continue;
                        if (lookfor.getname() == itemName)
                            x++;
                    }                                //查找背包中的该物品的数量
                    if (x < count) {
                        cout << "你没有足够数量的 " << itemName << " ." << endl;
                        break;
                    }
                    for (int i = 0; i < count; i++)
                        game.sellItem(itemName);
                    cout << "你卖出了 " << itemName << " * " << count << endl;
                }
            }
            else if(choicee==3)
                break;
            else {
                cout << "无效的输入欧" << endl;
                break;
            }
        }; break;
        case 6: {
            game.map.showTask();   //展示主线任务
        }; break;
        case 7: {
            game.currentRoom.NPCtalk();    //触发剧情与人物对话
        } break;
        case 8: {

            cout << "1.保存游戏进度  2.直接退出" << endl;
            int qu;
            cin >> qu;
            if (qu == 1) {
                ofstream fileGame("save.dat", ios::out | ios_base::binary);

                if (!fileGame) {
                    cout << "无法打开保存文件！" << endl;
                    cout << "保存失败！" << endl;
                }
                else
                {
                    fileGame << game.player.getname() << ' '
                        << game.player.getstrength() << ' '
                        << game.player.getagility() << ' '
                        << game.player.getlevel() << ' '
                        << game.player.getmoney() << ' '
                        << game.player.getMaxHP() << ' '
                        << game.player.getcurrentHP() << ' '
                        << game.player.getexp() << ' '
                        << game.player.getmaxexp() << ' '
                        // << game.player.getmoney() << ' '
                        << game.player.getcurrmana() << ' '
                        << game.player.getmaxmana() << ' ';
                    int invennum = game.player.inventory.size();
                    fileGame << invennum << ' ';
                    // 读入全部装备
                    if (invennum > 0) {
                        for (int i = 0; i < invennum; i++) {
                            fileGame << game.player.inventory[i];  //前提是将 << 重载
                        }

                        //读入装备的
                        bool haveWeaeq = 0, haveAreq = 0;
                        for (Item& item : game.player.inventory) {
                            if (item.isused == 1) {
                                if (item.gettype() == WEAPON)
                                    haveWeaeq = 1;
                                else if (item.gettype() == ARMOR)
                                    haveAreq = 1;
                            }
                        }                         //保存是否已装备的bool数 
                        fileGame << haveWeaeq << ' '
                            << haveAreq << ' ';
                    }
                    //读入房间各种
                    for (int i = 0; i < 10; i++) {
                        int itemnum = 0;
                        itemnum = game.map.rooms[i].items.size();
                        fileGame << game.map.rooms[i].name << ' '
                            << game.map.rooms[i].numm << ' '
                            << game.map.rooms[i].isfirstde << ' '
                            << game.map.rooms[i].isEnedead << ' '
                            << game.map.rooms[i].iscleaned << ' '
                            << game.map.rooms[i].taskdone << ' '
                            << itemnum << ' ';
                        if (itemnum > 0) {              //保存各房间各种数值 如果itemnum>0 再保存房间内的物品
                            for (int j = 0; j < itemnum; j++) {
                                fileGame << game.map.rooms[i].items[j];
                            }
                        }
                    }
                    int currentplace = game.currentRoom.numm;
                    int currtask = game.map.currentTask;      //保存任务进度
                    fileGame << currentplace << ' '
                        << currtask << ' ';

                    cout << "保存成功！" << endl;
                    fileGame.close();
                    over = 0;
      
                    system("cls");
                }
            }
            else if (qu == 2) {
                ofstream fileGame("save.dat", ios::trunc); // 打开文件并截断内容  清空存档
                if (!fileGame) {
                    cout << "无法打开保存文件！" << endl;
                    cout << "清空失败！" << endl;
                }
                else {
                    cout << "正在直接退出游戏" << endl;
                    Sleep(1000);
                    over = 0;
                    cout << "退出成功！" << endl;
                    fileGame.close();
                }

            }
        }; break;
        default: {
            cout << "请输入有效操作" << endl;
        };
        }
        if (!over)
            break;
        if (dea) {
            ofstream fileGame("save.dat", ios::trunc);
            if (!fileGame) {
                cout << "无法打开保存文件！" << endl;
                cout << "死亡退出失败！" << endl;
            }
            else {
                fileGame.close();
                cout << "你已败北 重头再来吧少年.." << endl;
            }
            
            break;
        }
        system("pause");
        system("cls");
    }
}


int main() {
    int colorCode = 32;

    // 游戏名字
    string gameName = "魔林探秘";

    // 打印游戏开始界面
    cout << "\n";
    cout << "\t\t\t\t\t" << "\033[1;" << colorCode << "m";  // 设置文本颜色为绿色

    // 逐行打印大号的游戏名字
    cout << endl << "    ******   *********    *****   *********  ***  *****   ******     ******  " << endl;
    cout << "  **    **     **    **   **   **     **     ***   **   **  **    **   **    **" << endl;
    cout << " **            **    **  **     **    **     ** ** **   **  **         **      " << endl;
    cout << " **            **    **  **     **    **     **  ****   **  **         **      " << endl;
    cout << " **            **    **  **     **    **     **   ***   **  **   ****  **       " << endl;
    cout << "  **    **     **    **   **   **     **     **    **   **   **    **   **    **" << endl;
    cout << "    ******   *********    *****       **     **    **   **    ******     ******  " << endl;

    cout << "\033[0m";  // 重置文本颜色
    cout << "\n\n";

    system("pause");
    system("cls");

    string background = "    在一个遥远的魔法王国，有一个神秘而古老的森林，被称为”幽林“。幽林被认为是魔法的源头，充满了千奇百怪的生物和宝藏。然而，进入幽林的道路却不是轻松的事情。这片森林被一系列神秘而危险的房间所保护，每个房间都有其独特的挑战和宝藏。现在，你是一位冒险家，听说幽林中蕴藏着传说中的宝藏和魔法。你踏上了前往幽林的旅程，但必须在克服一系列挑战和与各种奇幻生物互动的同时，解开这个古老森林的秘密。你的目标是找到幽林深处的传说中的“魔法之心”，这颗宝石被认为拥有巨大的魔力，可以改变王国的命运。然而，你必须面对各种各样的任、危险，以及与NPC角色的互动，才能成功获得这颗宝石。你的命运和整个王国的命运都取决于你的勇气和智慧。";
   
    //打印故事背景
    for (int i = 0; i < background.size(); i++) {
      cout << background[i];
      Sleep(10);
    }
    cout << endl;

    system("pause");
    system("cls");

    Game game;
start:
    cout << "                                      1.新的游戏 2.读档  3.退出" << endl;
    int cho;
    if (!(cin >> cho)) {
        cin.clear();                                          // 清除错误状态
        cin.ignore(numeric_limits<streamsize>::max(), '\n');// 忽略剩余的输入
        cout << "Invalid input. Please try again." << endl;
        goto start;
    }
    //如果文件为空 新游戏
    //不为空 读档操作
    // 加上一个不保存退出
    if (cho == 1) {
        ofstream fileGame("save.dat", ios::trunc); // 打开文件并截断内容
        if (!fileGame) {
            cout << "无法打开保存文件！" << endl;
            cout << "清空失败！" << endl;
        }
        else
            cout << "开始一场新的冒险" << endl;
        fileGame.close();
        game.initialize(0);
        //cout << "------------------------------" << endl;
        system("pause");
        system("cls");
        GameRun(game);
    }
    else if (cho == 2) {
        game.initialize(1);
        // game.displayRoom();
        ifstream inGame("save.dat", ios_base::in | ios_base::binary);
        if (inGame.peek() != EOF) {  //若数据文件为空   
            string name;
            int strength, agility, level, money, MaxHP, currentHP, exp, maxexp, currmana, maxmana;
            inGame >> name >> strength >> agility >> level >> money >> MaxHP >> currentHP >> exp >> maxexp >> currmana >> maxmana;
            game.player.setname(name);
            game.player.setstrength(strength);
            game.player.setagility(agility);
            game.player.setlevel(level);
            game.player.setmoney(money);
            game.player.setMaxHP(MaxHP);
            game.player.setcurrent(currentHP);
            game.player.setexp(exp);
            game.player.setmaxexp(maxexp);
            game.player.setcurrmana(currmana);
            game.player.setmaxmana(maxmana);

            int invennum = 0;
            inGame >> invennum;

            if (invennum > 0) {
                string name;
                int price, attdamage, defense, healing;
                ItemType type;
                bool isused;
                Item item;
                game.player.inventory.clear();
                for (int i = 0; i < invennum; i++) {
                    inGame >> item;
                    game.player.inventory.push_back(item);
                }
                bool haveWeaeq, haveAreq;
                inGame >> haveWeaeq >> haveAreq;
                if (haveWeaeq || haveAreq) {
                    for (Item& item : game.player.inventory)
                        if (item.isused == 1) {
                            if (item.gettype() == WEAPON)
                                game.player.equippedWeapon = item;
                            else if (item.gettype() == ARMOR)
                                game.player.equippedArmor = item;
                        }
                }
            }
            for (int i = 0; i < 10; i++) {
                int itemnum = 0, numm=0;
                bool isfirstde=0, isEnedead=0, iscleaned=1, taskdone=0;
                string name;
                Item item;
                inGame >> name >> numm >> isfirstde >> isEnedead >> iscleaned >> taskdone >> itemnum;
                game.map.rooms[i].items.clear();
                if (itemnum > 0) {
                    for (int j = 0; j < itemnum; j++) {
                        inGame >> item;
                        game.map.rooms[i].items.push_back(item);
                    }
                }
            }
            int currentplace = 0, currtask = 0;
            inGame >> currentplace >> currtask;
            game.map.currentTask = currtask;
            game.currentRoom = game.map.rooms[currentplace];

            inGame.close();
            cout << "读入成功！" << endl;
            GameRun(game);
        }
        else {
            cout << "没有游戏存档！！" << endl;
            inGame.close();
        }
    }
    else if (cho == 3)
        return 0;
    else
        cout << "请重新输入" << endl;

    goto start;
    return 0;
}


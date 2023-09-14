#include"Game.h"
#include<stdio.h>
#include<windows.h>
#include<conio.h>
int N;

void Game::initialize(int cho) {                                      
    // 初始化玩家属性
    if (cho == 0) {
        cout << "请输入角色名称" << endl;
        string name;
        cin >> name;
        player.setname(name);
    }
    else
        player.setname("GGbond");
    player.setstrength(20);
    player.setagility(5);
    player.setlevel(1);
    player.setmoney(100);
    player.setMaxHP(100);
    player.setcurrent(100);
    player.setmaxexp(100);
    player.setexp(0);
    player.setmaxmana(60);
    player.setcurrmana(60);
    //初始化玩家的各种属性

    

     // 初始化房间
    for (int i = 0; i < 10; i++) {
        map.rooms[i].numm = i;
        map.rooms[i].enemies.clear();
        map.rooms[i].enemyitems.clear();
        map.rooms[i].items.clear();  //先清空 防止后续读档初始化时增多
    }

    //对各房间各属性初始化 并初始化掉落的物品以及敌人 和相对应的故事情节
    map.rooms[0].name = "迷失森林入口";
    map.rooms[0].items.push_back(Item{ "魔力恢复丸", 200, ItemType::HEALING_ITEM,0,0,50 });
    map.rooms[0].items.push_back(Item{ "匕首",100,ItemType::WEAPON,30,0,0 });
    map.rooms[0].enemyitems.push_back(Item{ "幽影匕首",500,ItemType::WEAPON,60,0,0 });
    map.rooms[0].enemies.push_back(Enemy{ "狼人", 10, 50, 50,3 });
    map.rooms[0].towards[4] = &map.rooms[1];
    map.rooms[0].NPC[0] = "狼人：谁敢踏入我的领土？走开，否则你会后悔的！除非你能帮我找到迷失森林的神秘花朵。";  // 首次见到敌人
    map.rooms[0].NPC[1] = "狼人：哼，你比看上去强大。这是你的奖励。现在离开这片森林，但要记住，神秘花朵的力量可以拯救生命";  //首次击败敌人
    map.rooms[0].NPC[2] = "狼人：你又回来了？看来你真的决心了。继续寻找那些神秘花朵，它们会在你的冒险中发挥作用。"; //第二次及以后击败敌人
    map.rooms[0].NPC[3] = "妙妙（草药师）：欢迎，勇敢的探险者。我是草药师妙妙。如果你需要草药来治疗伤害，我可以帮助你。";//遇到妙妙
    map.rooms[0].NPC[4] = "妙妙（草药师）：你找到了神秘花朵，它们是非常珍贵的草药。希望它们能在你的冒险中帮助你。";  //成功采集神秘花朵后
    map.rooms[0].NPC[5] = "妙妙（草药师）:欢迎回来，探险者。如果你再次需要草药，只管找我。";//第二次及以后击败狼人后

    map.rooms[1].name = "闪烁的荧光洞穴";
    map.rooms[1].items.push_back(Item{ "魔力恢复丸", 200, ItemType::HEALING_ITEM,0,0,50 });
    map.rooms[1].enemies.push_back(Enemy{ "怪物", 20, 80,80, 3 });
    map.rooms[1].enemyitems.push_back(Item{ "幽影匕首",500,ItemType::WEAPON,60,0,0 });
    map.rooms[1].towards[3] = &map.rooms[3];
    map.rooms[1].towards[1] = &map.rooms[4];
    map.rooms[1].towards[2] = &map.rooms[0];
    map.rooms[1].NPC[0] = "欢迎来到荧光洞穴，陌生人。你需要我的荧光蘑菇才能在这里安全行走。但首先，你必须回答我的谜题。";//（首次见到荧光蘑菇精灵）：
    map.rooms[1].NPC[1] = "你很聪明，这是荧光蘑菇，它们将为你点亮前方的道路。但要小心洞穴里的怪物。";//（回答正确谜题后）：
    map.rooms[1].NPC[2] = "谢谢你的勇气。现在，你可以继续前进，但请记住，荧光蘑菇是你的朋友。";  //（首次击败怪物）：
    map.rooms[1].NPC[3] = "嗨，陌生人。欢迎来到荧光洞穴。我可以给你一些荧光蘑菇，但你必须回答我的谜题。"; //格林光（荧光蘑菇精灵）:遇到格林光：
    map.rooms[1].NPC[4] = "太棒了！这是荧光蘑菇，拿去吧。它们将为你照亮前方的道路。";//回答正确谜题后：
    map.rooms[1].NPC[5] = "你打败了怪物，真了不起！荧光蘑菇是你的朋友，它们将保护你。";//首次击败怪物后：

    map.rooms[2].name = "巨大的蘑菇林";
    map.rooms[2].items.push_back(Item{ "魔力恢复丸", 200, ItemType::HEALING_ITEM,0,0,50 });
    map.rooms[2].enemyitems.push_back(Item{ "幽影匕首",500,ItemType::WEAPON,60,0,0 });
    map.rooms[2].enemies.push_back(Enemy{ "蘑菇精灵首领", 30, 120,120, 3 });
    map.rooms[2].towards[4] = &map.rooms[3];
    map.rooms[2].NPC[0] = "欢迎，勇敢的探险者。只有解开三个谜题，你才能穿越这片蘑菇林。";//（首次见到蘑菇精灵首领）：
    map.rooms[2].NPC[1] = "你回答得对，但这只是开始。下一个谜题在前方等着你。";  //（回答第一个谜题后）
    map.rooms[2].NPC[2] = "你证明了自己是值得信赖的。现在，你可以穿越蘑菇林，但请小心，它不是没有危险的。";//（成功解开三个谜题）：
    map.rooms[2].NPC[3] = " 欢迎来到蘑菇林，陌生人。只有解开三个谜题，你才能穿越这片蘑菇林。"; //蘑菇国王：遇到蘑菇国王：
    map.rooms[2].NPC[4] = " 你的智慧真是令人印象深刻，继续前进吧，下一个谜题在前方等着你";//回答第一个谜题后：
    map.rooms[2].NPC[5] = " 你证明了自己是值得信赖的。现在，你可以穿越蘑菇林，但请小心，它不是没有危险的。"; //成功解开三个谜题后：

    map.rooms[3].name = "暗黑的骷髅墓地";
    map.rooms[3].items.push_back(Item{ "魔力恢复丸", 200, ItemType::HEALING_ITEM,0,0,50 });
    map.rooms[3].enemyitems.push_back(Item{ "幽影匕首",500,ItemType::WEAPON,60,0,0 });
    map.rooms[3].enemies.push_back(Enemy{ "骷髅守卫", 35, 150,150 ,3 });
    map.rooms[3].towards[2] = &map.rooms[2];
    map.rooms[3].towards[4] = &map.rooms[6];
    map.rooms[3].towards[3] = &map.rooms[5];
    map.rooms[3].towards[1] = &map.rooms[1];
    map.rooms[3].NPC[0] = "谁敢闯入我们的领域？这里只有死亡等待你。";//（首次见到复活的骷髅守卫）：
    map.rooms[3].NPC[1] = "你的勇气令人印象深刻，探险者。你找到了骷髅王之冠，现在你可以继续前进。同时，这是骷髅墓地的历史记录，或许对你有帮助。";//（首次击败骷髅守卫并找到历史记录）：
    map.rooms[3].NPC[2] = "你又回来了，生者。但你的死期将至。";// 第二次及以后击败骷髅守卫）：
    map.rooms[3].NPC[3] = "： 你是来寻找骷髅王之冠的吗？我可以帮助你。但请帮我收集墓地的历史记录。";//艾莉丝（历史学家）：遇到艾莉丝
    map.rooms[3].NPC[4] = "你找到了历史记录，非常感谢。现在，骷髅王之冠是你的了。";//找到历史记录并解锁门后：
    map.rooms[3].NPC[5] = "欢迎回来，勇者。历史记载是无价的。";//第二次及以后击败骷髅守卫后：

    map.rooms[4].name = "魔法的水晶瀑布";
    map.rooms[4].items.push_back(Item{ "魔力恢复丸", 200, ItemType::HEALING_ITEM,0,0,50 });
    map.rooms[4].enemyitems.push_back(Item{ "幽影匕首",500,ItemType::WEAPON,60,0,0 });
    map.rooms[4].enemies.push_back(Enemy{ "水晶守卫", 35, 180,180, 3 });
    map.rooms[4].towards[3] = &map.rooms[1];
    map.rooms[4].towards[4] = &map.rooms[8];
    map.rooms[4].NPC[0] = "欢迎来到水晶瀑布，探险者。只有水晶之心才能解锁这些魔法水晶的力量。";//（首次见到水晶守卫）：
    map.rooms[4].NPC[1] = "你已经证明了自己对魔法的理解。现在，你可以采集魔法水晶，并用它们的力量保护自己。同时，这是水晶守卫失落的心脏，或许它对你有所帮助。";//（回答谜题并找到水晶之心）：
    map.rooms[4].NPC[2] = "你再次来到这里，探险者。但这次，我将不会手下留情。";//（第二次及以后击败水晶守卫）：
    map.rooms[4].NPC[3] = " 这是魔法水晶瀑布，探险者。只有水晶之心才能解锁这些水晶的力量。";//塞琳娜（水晶守卫）：遇到塞琳娜：
    map.rooms[4].NPC[4] = "你已经证明了自己对魔法的理解。现在，你可以采集魔法水晶，并用它们的力量保护自己。";//回答谜题并找到水晶之心后：
    map.rooms[4].NPC[5] = "欢迎回来，陌生人。水晶之心是你的，但你必须小心使用它。";//第二次及以后击败水晶守卫后：

    map.rooms[5].name = "妖精之泉";
    map.rooms[5].items.push_back(Item{ "魔力恢复丸", 200, ItemType::HEALING_ITEM,0,0,50 });
    map.rooms[5].enemyitems.push_back(Item{ "幽影匕首",500,ItemType::WEAPON,60,0,0 });
    map.rooms[5].enemies.push_back(Enemy{ "窃贼", 40, 200,200, 3 });
    map.rooms[5].towards[1] = &map.rooms[3];
    map.rooms[5].NPC[0] = "陌生人，我是妖精公主，我的魔法项链被窃贼偷走了。如果你能帮我找回它，我将教给你一项强大的咒语。";//（首次见到妖精公主）：
    map.rooms[5].NPC[1] = "你真是个好心人，陌生人。作为感谢，我将传授给你咒语，它将在你的冒险中派上用场。";//（成功找回魔法项链）：
    map.rooms[5].NPC[2] = "你再次回来了，我的救星。我的魔法项链再次被盗，但你总是能找回它。";//（第二次及以后击败盗贼并找回魔法项链）
    map.rooms[5].NPC[3] = "遇到亚妮：你是来帮助我的吗？我的魔法项链被窃贼偷走了。如果你能找回它，我将传授你一项咒语。";//亚妮（妖精公主）：
    map.rooms[5].NPC[4] = "谢谢你的帮助，陌生人。现在，我将履行我的诺言，传授给你一项强大的咒语。"; //成功找回魔法项链后：
    map.rooms[5].NPC[5] = "你再次来到这里，我的救星。我的魔法项链再次被盗，但你总是能找回它。";//第二次及以后击败盗贼并找回魔法项链后：
    //////////////////////////////////////////////////////
    map.rooms[6].name = "毒蛇洞";
    map.rooms[6].items.push_back(Item{ "Sword7", 50, ItemType::WEAPON ,10,0,0 });
    map.rooms[6].items.push_back(Item{ "魔力恢复丸", 200, ItemType::HEALING_ITEM,0,0,50 });
    map.rooms[6].enemies.push_back(Enemy{ "毒蛇女王", 50, 300,300, 3 });
    map.rooms[6].towards[2] = &map.rooms[3];
    map.rooms[6].NPC[0] = "这是毒蛇的领地，陌生人。只有解锁机关，你才能离开这里。但首先，你需要帮我收集毒蛇的毒液。";//（首次见到毒蛇女王）：
    map.rooms[6].NPC[1] = "你完成了任务，陌生人。现在，你可以离开这片危险的地方。这些毒液也许对你的冒险有所帮助。";//（解锁机关并收集毒蛇毒液）：
    map.rooms[6].NPC[2] = "你再次回来，勇者。这次你没有逃过。";//（第二次及以后击败毒蛇女王）：
    map.rooms[6].NPC[3] = "遇到瑞娜：这是毒蛇的领地，陌生人。只有解锁机关，你才能离开这里。但首先，你需要帮我收集毒蛇的毒液。";//瑞娜（毒蛇女王）：
    map.rooms[6].NPC[4] = "你完成了任务，陌生人。现在，你可以离开这片危险的地方。这些毒液也许对你的冒险有所帮助。";//解锁机关并收集毒蛇毒液后：
    map.rooms[6].NPC[5] = "你又来了，勇者。这次你没有逃过。";//第二次及以后击败毒蛇女王后：

    map.rooms[7].name = "龙之巢穴";
    map.rooms[7].items.push_back(Item{ "Sword8", 50, ItemType::WEAPON ,10,0,0 });
    map.rooms[7].items.push_back(Item{ "魔力恢复丸", 200, ItemType::HEALING_ITEM,0,0,50 });
    map.rooms[7].enemies.push_back(Enemy{ "巨龙", 80, 350,350, 3 });
    map.rooms[7].towards[1] = &map.rooms[8];
    map.rooms[7].NPC[0] = "我是这片森林的守护者，只有勇者才能与我对话。如果你想获取我的宝藏，你必须证明自己的勇气。";//首次见到巨龙）：
    map.rooms[7].NPC[1] = "你通过了我的考验，勇者。现在，你可以取走我的宝藏，但请对它们负起责任。";//（成功解开守护之谜）：
    map.rooms[7].NPC[2] = "你又回来了，陌生人。你是否准备好再次接受我的考验？";//（第二次及以后击败龙）：
    map.rooms[7].NPC[3] = " 我是这片森林的守护者，只有勇者才能与我对话。如果你想获取我的宝藏，你必须证明自己的勇气。";//德拉科斯（巨龙守护者）：遇到德拉科斯：
    map.rooms[7].NPC[4] = "你通过了我的考验，勇者。现在，你可以取走我的宝藏，但请对它们负起责任。";//成功解开守护之谜后： 
    map.rooms[7].NPC[5] = "你再次回来，陌生人。你是否准备好再次接受我的考验？";//第二次及以后击败龙后：

    map.rooms[8].name = "疯狂的赌场";
    map.rooms[8].items.push_back(Item{ "Sword9", 50, ItemType::WEAPON ,10,0,0 });
    map.rooms[8].items.push_back(Item{ "魔力恢复丸", 200, ItemType::HEALING_ITEM,0,0,50 });
    map.rooms[8].enemies.push_back(Enemy{ "贪婪的赌场老板", 90, 400,400, 3 });
    map.rooms[8].towards[2] = &map.rooms[4];
    map.rooms[8].towards[3] = &map.rooms[7];
    map.rooms[8].towards[1] = &map.rooms[9];
    map.rooms[8].NPC[0] = "欢迎来到我的赌场，陌生人。如果你能赢得足够的金币，我将为你提供通往传奇宝藏室的通行证。";//（首次进入赌场）：
    map.rooms[8].NPC[1] = "你的运气不错，陌生人。这是通向传奇宝藏室的通行证。但请记住，赌场中的胜利并不总是长久的。";//（赢得足够的金币并获取通行证）：
    map.rooms[8].NPC[2] = "欢迎回来，探险者。你又来挑战运气了吗？";//（第二次及以后进入赌场）：
    map.rooms[8].NPC[3] = "遇到巴克斯：欢迎来到我的赌场，陌生人。如果你能赢得足够的金币，我将为你提供通往传奇宝藏室的通行证。";//巴克斯（赌场老板）：
    map.rooms[8].NPC[4] = " 你的运气不错，陌生人。这是通向传奇宝藏室的通行证。但请记住，赌场中的胜利并不总是长久的。";//赢得足够的金币并获取通行证后：
    map.rooms[8].NPC[5] = "欢迎回来，探险者。你又来挑战运气了吗？";//第二次及以后进入赌场后：

    map.rooms[9].name = "传奇宝藏室";
    map.rooms[9].items.push_back(Item{ "Sword10", 50, ItemType::WEAPON ,10,0,0 });
    map.rooms[9].items.push_back(Item{ "魔力恢复丸", 200, ItemType::HEALING_ITEM,0,0,50 });
    map.rooms[9].enemies.push_back(Enemy{ "宝藏室的守护者", 100, 500,500, 3 });
    map.rooms[9].towards[3] = &map.rooms[8];
    map.rooms[9].NPC[0] = "你是第一个来到这里的人，陌生人。只有聪明的人才能解开宝藏的谜题。准备好了吗？";//（首次见到宝藏室的守护者）：
    map.rooms[9].NPC[1] = "你的智慧令人印象深刻，陌生人。现在，你可以拿走传奇宝藏，但要记住，它可能比你想象的更危险。";//（成功解开宝藏的保护机制）：
    map.rooms[9].NPC[2] = "你又来了，探险者。这次，你是否能再次解开谜题？或许宝藏之秘将揭示更多的真相。";//（第二次及以后进入宝藏室）：
    map.rooms[9].NPC[3] = "你是第一个来到这里的人，陌生人。只有聪明的人才能解开宝藏的谜题。准备好了吗？";//古老巨龙：遇到古老巨龙：
    map.rooms[9].NPC[4] = "你的智慧令人印象深刻，陌生人。现在，你可以拿走传奇宝藏，但要记住，它可能比你想象的更危险。";//成功解开宝藏的保护机制后： 
    map.rooms[9].NPC[5] = "你又来了，探险者。这次，你是否能再次解开谜题？或许宝藏之秘将揭示更多的真相。";//第二次及以后进入宝藏室后：

    currentRoom = map.rooms[0];
   
    // 初始化商店

    shop.items.push_back(Item{ "魔林之刃",1000,ItemType::WEAPON,100,0,0 });
    shop.items.push_back(Item{ "魔法长弓",800,ItemType::WEAPON,80,0,0 });
    shop.items.push_back(Item{ "噬魂之剑",1500,ItemType::WEAPON,120,0,0 });
    shop.items.push_back(Item{ "幽影匕首",500,ItemType::WEAPON,60,0,0 });
    shop.items.push_back(Item{ "魔林之怒",2000,ItemType::WEAPON,150,0,0 });
    shop.items.push_back(Item{ "影月双刃",1000,ItemType::WEAPON,90,0,0 });
    shop.items.push_back(Item{ "暗影之矛",1200,ItemType::WEAPON,70,0,0 });
    shop.items.push_back(Item{ "魔皮战甲",800,ItemType::ARMOR,0,50,0 });
    shop.items.push_back(Item{ "龙鳞战甲",1200,ItemType::ARMOR,0,70,0 });
    shop.items.push_back(Item{ "不朽铠甲",2000,ItemType::ARMOR,0,100,0 });
    shop.items.push_back(Item{ "幻影护甲",1500,ItemType::ARMOR,0,80,0 });
    shop.items.push_back(Item{ "光明圣装",2500,ItemType::ARMOR,0,120,0 });
    shop.items.push_back(Item{ "神速之丹", 150, ItemType::HEALING_ITEM,0,0,30 });
    shop.items.push_back(Item{ "血祭草药", 300, ItemType::HEALING_ITEM,0,0,80 });
    shop.items.push_back(Item{ "神行之丹", 200, ItemType::HEALING_ITEM,0,0,40 });
    shop.items.push_back(Item{ "魔力恢复丸", 200, ItemType::HEALING_ITEM,0,0,50 });
    shop.items.push_back(Item{ "灵魂净化剂", 500, ItemType::HEALING_ITEM,0,0,100 });
    shop.items.push_back(Item{ "魔力爆发丸", 300, ItemType::HEALING_ITEM,0,0,70 });
    shop.items.push_back(Item{ "魔力荒芜草药", 600, ItemType::HEALING_ITEM,0,0,120 });
    shop.items.push_back(Item{ "魔法抗性披风",1000,ItemType::ARMOR,0,60,0 });
    shop.items.push_back(Item{ "致命荆棘铠甲",1500,ItemType::ARMOR,0,90,0 });
    
}
 
void Game::displayRoom() { // 展示函数
    cout << "你在 " << currentRoom.name << endl;
    cout << "房间内的敌人: ";
    for ( Enemy& enemy : currentRoom.enemies) {
        cout << enemy.getname() << " ";
    }
    cout << endl;
}

void Game::move(string direction) {//移动函数 使用控制台操作
    int toward = 0;
    int x_pos = 1, y_pos = 1;
    if (N == 0) { x_pos = 14, y_pos = 17; };
    if (N == 1) { x_pos = 14, y_pos = 9; };
    if (N == 2) { x_pos = 10, y_pos = 13; };
    if (N == 3) { x_pos = 10, y_pos = 9; };
    if (N == 4) { x_pos = 24, y_pos = 9; };
    if (N == 5) { x_pos = 4, y_pos = 9; };
    if (N == 6) { x_pos = 10, y_pos = 5; };
    if (N == 7) { x_pos = 18, y_pos = 3; };
    if (N == 8) { x_pos = 24, y_pos = 3; };
    if (N == 9) { x_pos = 34, y_pos = 3; };
    ChangeColor(); pos(50, 30); printf("使用WSAD控制移动");
    cout << "\033[0m";  // 重置文本颜色
    cout << "\n\n";
    while (1) {
        switch (_getch()) {
        case 'w':
            y_pos -= 1; break;
        case 's':
            y_pos += 1; break;
        case 'a':
            x_pos -= 2; break;
        case 'd':
            x_pos += 2; break;
        }
        system("cls");

        pos(4, 10); printf("6");
        pos(10, 10); printf("4");
        pos(14, 10); printf("2");
        pos(24, 10); printf("5");
        pos(10, 6); printf("7");
        pos(10, 14); printf("3");
        pos(14, 18); printf("1");
        pos(18, 4); printf("8");
        pos(24, 4); printf("9");
        pos(34, 4); printf("10");
        for (int i = 6; i < 10; i++) {
            pos(i, 10); printf("-");
        }
        for (int i = 11; i < 14; i++) {
            pos(i, 10); printf("-");
        }
        for (int i = 16; i < 24; i++) {
            pos(i, 10); printf("-");
        }
        for (int i = 20; i < 24; i++) {
            pos(i, 4); printf("-");
        }
        for (int i = 26; i < 34; i++) {
            pos(i, 4); printf("-");
        }
        for (int j = 7; j < 10; j++) {
            pos(10, j); printf("|");
        }
        for (int j = 11; j < 14; j++) {
            pos(10, j); printf("|");
        }
        for (int j = 11; j < 18; j++) {
            pos(14, j); printf("|");
        }
        for (int j = 5; j < 10; j++) {
            pos(24, j); printf("|");
        }

        for (int i = 0; i < 40; i++) {
            pos(i, 20); printf("█");
        }
        for (int j = 0; j < 20; j++) {
            pos(40, j); printf("█");
        }
        for (int i = 0; i < 40; i++) {
            pos(i, 0); printf("█");
        }
        for (int j = 0; j < 20; j++) {
            pos(0, j); printf("█");
        }
      

        pos(x_pos, y_pos); printf("我");
        if (x_pos >= 39)
            x_pos=x_pos - 1;
        if (y_pos > 19)
            y_pos=y_pos - 1;
        pos(40, 22); printf("%d,%d", x_pos, y_pos);
        pos(50, 2); printf("1:迷失森林入口");
        pos(50, 4); printf("2:闪烁的荧光洞穴");
        pos(50, 6); printf("3:巨大的蘑菇林");
        pos(50, 8); printf("4:暗黑的骷髅墓地");
        pos(50, 10); printf("5:魔法的水晶瀑布");
        pos(50, 12); printf("6:妖精之泉");
        pos(50, 14); printf("7:毒蛇洞");
        pos(50, 16); printf("8:龙之巢穴");
        pos(50, 18); printf("9:疯狂的赌场");
        pos(50, 20); printf("10:传奇宝藏室");
        pos(10, 25); printf("注：请在范围内移动");

        if (x_pos == 14 && y_pos == 18) {
            map.checkTask(currentRoom);
            currentRoom = map.rooms[0];
            N = 0;
            break;
        }
        if (x_pos == 14 && y_pos == 10) {
            map.checkTask(currentRoom);
            currentRoom = map.rooms[1];
            N = 1;
            break;
        }
        if (x_pos == 10 && y_pos == 14) {
            map.checkTask(currentRoom);
            currentRoom = map.rooms[2];
            N = 2;
            break;
        }
        if (x_pos == 10 && y_pos == 10) {
            map.checkTask(currentRoom);
            currentRoom = map.rooms[3];
            N = 3;
            break;
        }
        if (x_pos == 24 && y_pos == 10) {
            map.checkTask(currentRoom);
            currentRoom = map.rooms[4];
            N = 4;
            break;
        }
        if (x_pos == 4 && y_pos == 10) {
            map.checkTask(currentRoom);
            currentRoom = map.rooms[5];
            N = 5;
            break;
        }
        if (x_pos == 10 && y_pos == 6) {
            map.checkTask(currentRoom);
            currentRoom = map.rooms[6];
            N = 6;
            break;
        }
        if (x_pos == 18 && y_pos == 4) {
            map.checkTask(currentRoom);
            currentRoom = map.rooms[7];
            N = 7;
            break;
        }
        if (x_pos == 24 && y_pos == 4) {
            map.checkTask(currentRoom);
            currentRoom = map.rooms[8];
            N = 8;
            break;
        }
        if (x_pos == 34 && y_pos == 4) {
            map.checkTask(currentRoom);
            currentRoom = map.rooms[9];
            N = 9;
            break;
        }
    };

}

void Game::pickUpItem(const string& itemName) {  //拾取函数
    //捡 调用时需提供参数name
    if (currentRoom.iscleaned) {
        cout << "The room is cleaned" << endl;
        return; 
    }
    for (auto it = currentRoom.items.begin(); it != currentRoom.items.end(); ++it) {
        if (it->getname() == itemName) {
            player.inventory.push_back(*it);
            currentRoom.items.erase(it);
            cout << "你捡起了 " << itemName << endl;
            return;
        }
    }
    cout << "房间里没有物品！" << endl;
}

void Game::dropItem(const string& itemName) {                 //扔 一样
    for (auto it = player.inventory.begin(); it != player.inventory.end(); ++it) {
        if (it->getname() == itemName) {
            currentRoom.items.push_back(*it);
            player.inventory.erase(it);
            cout << "你扔出了 " << itemName << endl;
            if (it->isused == 1)
                it->isused = 0;
            return;
        }
    }

    cout << "背包中没有该物品!" << endl;
}

void Game::displayInventory() {                             //展示装备库
    cout << "背包内的物品： ";
    for ( Item& item : player.inventory) {
        if (item.isused == 0)
            cout << item.getname() << "  ";
    }
    cout << endl;
    cout << "有  " << player.getmoney() << "  money 傍身" << endl;
    
}

void Game::displayShop() {                               //展示商店
    cout << "物品列表: " << endl;
    for ( Item& item : shop.items) {
        cout << item.getname() << " - 价格: " << item.getprice() << endl;
    }
}

void Game::buyItem(const string& itemName) {              //买东西 调用需提供name
    for (auto it = shop.items.begin(); it != shop.items.end(); ++it) {
        if (it->getname() == itemName) {
            if (player.getmoney() >= it->getprice()) {
                player.inventory.push_back(*it);
                player.setmoney(player.getmoney() - it->getprice());
                // shop.items.erase(it);                //商店库存无限

            }
            else {
                cout << "钱不够 " << itemName << endl;
            }
            return;
        }
    }
    cout << "商店中没有这个物品!" << endl;
}

void Game::sellItem(const string& itemName) {
    for (auto it = player.inventory.begin(); it != player.inventory.end(); ) {
        if (it->getname() == itemName) {
            player.setmoney( player.getmoney() + it->getprice());
            //shop.items.push_back(*it);
            it = player.inventory.erase(it);  // 更新迭代器，并将其指向下一个元素
            return;
        }
        else {
            ++it;  // 继续迭代
        }
    }
    cout << "背包中没有该物品!" << endl;
}

void Game::Whatbeingused() {
    int count = 0;
    for (auto it = player.inventory.begin(); it != player.inventory.end(); ++it)
        if (it->isused) {
            count++;
            if (it->gettype() == WEAPON)
                cout << "你正在使用的武器: " << it->getname() << endl;
            else if (it->gettype() == ARMOR)
                cout << "你现在装备的护甲: " << it->getname() << endl;
        }
    if (count == 0)
        cout << "没有正在使用的装备！" << endl;
}

int Game::fight(Enemy& badguy) {
    cout << "开始和 " << badguy.getname() << "的战斗" << endl;
    system("pause");
    system("cls");
    string s[3];
    int nn = 0;
    for (auto it = player.Skill.begin(); it != player.Skill.end(); ++it) {
        s[nn] = it->first;
        nn++;
    }
    int round = 1;
    for (round;; round++) {
        if (player.getcurrentHP() <= 0)
        {
            cout << "你被打败了 "  << endl;
            return 0;
        }
        else if (badguy.getHp() <= 0)
        {
            cout << "你打败了 " << badguy.getname() << " ,地上有一些物品掉落" << endl;
            return 1;
        }
        cout << "------------------------------" << endl;
        cout << "第" << round << " 回合" << endl;
        cout << player.getname() << "   血量: " << player.getcurrentHP() << "/" << player.getMaxHP() <<"   蓝量"<<player.getcurrmana()<<" / "<<player.getmaxmana() << " 敌方：:" << badguy.getHp() << endl;
        cout << "你想要 :1.攻击  2. 嗑药  3.逃跑" << endl;
        int fc;
        cin >> fc;
        if (fc == 1) {
            cout << "你要用：1." << s[0] << " 2." << s[1] << " 3. " << s[2] <<" 4.平a起手" << endl;
            int uchoice;
            cin >> uchoice;
            player.attackEnemy(badguy, uchoice);
            if (badguy.getstrength() > player.equippedArmor.getdefense() && badguy.getHp() > 0) {
                cout << badguy.getname() << " 对你造成了 " << badguy.getstrength() - player.equippedArmor.getdefense() << " 点伤害" << endl;
                cout << "------------------------------" << endl;
                system("pause");
                system("cls");
                int hp = player.getcurrentHP() - (badguy.getstrength() - player.equippedArmor.getdefense());
                player.setcurrent(hp);
            }
            else if (badguy.getstrength() <= player.equippedArmor.getdefense() && badguy.getHp() > 0) {
                cout << "你的护甲高于敌人的攻击力，他不能对你造成伤害！" << endl;
                cout << "------------------------------" << endl;
                system("pause");
                system("cls");
            }
        }
        else if (fc == 2) {
            string Itemname;
            cout << "背包中:" << endl;
            int count = 0;
            for (Item& item : player.inventory) {
                if (item.gettype() == HEALING_ITEM) {
                    count++;
                    cout << item.getname() << "   ";
                }
            }
            if (!count) {
                cout << "你的背包中没有丹药可以使用 " << endl;
                if (badguy.getstrength() > player.equippedArmor.getdefense()) {
                    cout << badguy.getname() << " 对你造成了 " << badguy.getstrength() - player.equippedArmor.getdefense() << " 点伤害" << endl;
                    int hp = player.getcurrentHP() - (badguy.getstrength() - player.equippedArmor.getdefense());
                    player.setcurrent(hp);
                    cout << "------------------------------" << endl;
                    system("pause");
                    system("cls");
                }
                else {
                    cout << "你的护甲高于敌人的攻击力，他不能对你造成伤害！" << endl;
                    cout << "------------------------------" << endl;
                    system("pause");
                    system("cls");
                }
                continue;
            }
            cout << endl;
            cout << "请输入你要使用的药品:" << endl;
            cin >> Itemname;
            for (Item& item : player.inventory)
                if (item.getname() == Itemname) {
                    player.useItem(item);
                }
            if (badguy.getstrength() > player.equippedArmor.getdefense()) {
                cout << badguy.getname() << "服用丹药触发无敌金身 敌人对你无法造成伤害 "  << endl;
                cout << "------------------------------" << endl;
                system("pause");
                system("cls");
            }
            else {
                cout << "------------------------------" << endl;
                system("pause");
                system("cls");
            }
        }
        else {
            cout << "敏捷度低于敌人，跑不了一点儿现在,白挨一下子.." << endl;
            if (badguy.getstrength() > player.equippedArmor.getdefense() && badguy.getHp() > 0) {
                cout << badguy.getname() << " 对你造成了 " << badguy.getstrength() - player.equippedArmor.getdefense() << " 点伤害" << endl;
                cout << "你的护甲高于敌人的攻击力，他不能对你造成伤害！" << endl;
                cout << "------------------------------" << endl;
                system("pause");
                system("cls");
                int hp = player.getcurrentHP() - (badguy.getstrength() - player.equippedArmor.getdefense());
                player.setcurrent(hp);
            }
            else if (badguy.getstrength() <= player.equippedArmor.getdefense() && badguy.getHp() > 0) {
                cout << "你的护甲高于敌人的攻击力，他不能对你造成伤害！" << endl;
                cout << "你的护甲高于敌人的攻击力，他不能对你造成伤害！" << endl;
                cout << "------------------------------" << endl;
                system("pause");
                system("cls");
            }


        }
    }
}
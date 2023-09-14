#ifndef MAP_H
#define MAP_H

#include"Room.h"
#include<queue>

//地图类 包括NPC和Task
class Map {
public:
    Room rooms[10];
    
    string Task[10] = {
        "任务内容：前往迷失森林入口 击败敌人",
        "任务内容：前往闪烁的荧光洞穴 击败敌人",
        "任务内容：前往巨大的蘑菇林 击败敌人",
        "任务内容：前往暗黑的骷髅墓地 击败敌人",
        "任务内容：前往魔法的水晶瀑布 击败敌人",
        "任务内容：前往妖精之泉 击败敌人",
        "任务内容：前往毒蛇洞 击败敌人",
        "任务内容：前往龙之巢穴 击败敌人",
        "任务内容：前往疯狂的赌场 击败敌人",
        "任务内容：前往传奇宝藏室 击败敌人",
    };    //任务的完成顺序根据房间的标号来 然后完成的判断也是根据这样
    int currentTask = 0;//任务检测在每次战斗结束 或者 其他一些动作之后 自动检测？ 
    void showTask();
    bool checkTask(Room& room);

};

void ShowMap();

void pos(int x_pos, int y_pos);
void ChangeColor();
#endif
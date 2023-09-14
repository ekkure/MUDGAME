#include"Room.h"


void Room::NPCtalk() {
    if (!isEnedead) {      //敌人没有死亡触发的对话
        cout << NPC[0] << endl;
        system("pause");
        cout << NPC[3] << endl;
    }
    else if (isEnedead && isfirstde) {//敌人第一次死亡触发的对话
        cout << NPC[1] << endl;
        system("pause");
        cout << NPC[4] << endl;
        isfirstde = 0;
    }
    else if (isEnedead && !isfirstde) {
        cout << NPC[2] << endl;//敌人后续死亡触发的情节对话
        system("pause");
        cout << NPC[5] << endl;
    }
}


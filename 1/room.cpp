#include"Room.h"


void Room::NPCtalk() {
    if (!isEnedead) {      //����û�����������ĶԻ�
        cout << NPC[0] << endl;
        system("pause");
        cout << NPC[3] << endl;
    }
    else if (isEnedead && isfirstde) {//���˵�һ�����������ĶԻ�
        cout << NPC[1] << endl;
        system("pause");
        cout << NPC[4] << endl;
        isfirstde = 0;
    }
    else if (isEnedead && !isfirstde) {
        cout << NPC[2] << endl;//���˺���������������ڶԻ�
        system("pause");
        cout << NPC[5] << endl;
    }
}


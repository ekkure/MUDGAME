#include"Map.h"
#include"Room.h"
#include<stdio.h>
#include<windows.h>
#include<conio.h>

void Map::showTask() {
	cout << Task[currentTask] << endl;

}

bool Map::checkTask(Room& room) {

	if (room.numm == currentTask) {
		if ( room.taskdone == 0 && room.isEnedead==1) {   ////////////////////////////////////room.isfirstde == 1 &&
			rooms[room.numm].taskdone = 1;
			currentTask++;
			cout << "任务完成 请查看下一个任务" << endl;
			return true;
		}
			
	}
	else
		return false;
}

void ShowMap() {
	
	cout << "                                    __________    __________    __________       " << endl;
	cout << "                                   |          |  |          |  |          |      " << endl;
	cout << "                                   |    8     |__|    9     |__|    10    |      " << endl;
	cout << "                                   |龙之巢穴  |  |疯狂的赌场|  |传奇宝藏室|      " << endl;
	cout << "                                   |__________|  |__________|  |__________|      " << endl;
	cout << "                      __________                      |                          " << endl;
	cout << "                     |          |                     |                          " << endl;
	cout << "                     |    7     |                     |                          " << endl;
	cout << "                     | 毒蛇洞   |                     |                          " << endl;
	cout << "                     |__________|                     |                          " << endl;
	cout << "    __________        ____|______  _____________   ___________                    " << endl;
	cout << "   |          |      |    4     |  |    2      |  |    5      |                    " << endl;
	cout << "   |    6     |______| 暗黑的骷 |__|  闪烁的   |__|魔法的水   |                    " << endl;
	cout << "   | 妖精之泉 |      | 髅墓地   |  | 荧光洞穴  |  |晶瀑布     |                    " << endl;
	cout << "   |__________|      |__________|  |___________|  |___________|                    " << endl;
	cout << "                           |            |                                        " << endl;
	cout << "                      _____|_____       |                                        " << endl;
	cout << "                     |          |       |                                        " << endl;
	cout << "                     |    3     |       |                                        " << endl;
	cout << "                     | 巨大的   |       |                                        " << endl;
	cout << "                     | 蘑菇林   |       |                                        " << endl;
	cout << "                     |__________|       |                                        " << endl;
	cout << "                                    ____|_____                                   " << endl;
	cout << "                                   |    1     |                                  " << endl;
	cout << "                                   | 迷失森林 |                                  " << endl;
	cout << "                                   |  入口    |                                  " << endl;
	cout << "                                   |__________|                                  " << endl;

}

void pos(int x_pos, int y_pos) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x_pos,y_pos };
	SetConsoleCursorPosition(hOut, pos);
}
void ChangeColor() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}



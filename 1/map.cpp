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
			cout << "������� ��鿴��һ������" << endl;
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
	cout << "                                   |��֮��Ѩ  |  |���Ķĳ�|  |���汦����|      " << endl;
	cout << "                                   |__________|  |__________|  |__________|      " << endl;
	cout << "                      __________                      |                          " << endl;
	cout << "                     |          |                     |                          " << endl;
	cout << "                     |    7     |                     |                          " << endl;
	cout << "                     | ���߶�   |                     |                          " << endl;
	cout << "                     |__________|                     |                          " << endl;
	cout << "    __________        ____|______  _____________   ___________                    " << endl;
	cout << "   |          |      |    4     |  |    2      |  |    5      |                    " << endl;
	cout << "   |    6     |______| ���ڵ��� |__|  ��˸��   |__|ħ����ˮ   |                    " << endl;
	cout << "   | ����֮Ȫ |      | ��Ĺ��   |  | ӫ�ⶴѨ  |  |���ٲ�     |                    " << endl;
	cout << "   |__________|      |__________|  |___________|  |___________|                    " << endl;
	cout << "                           |            |                                        " << endl;
	cout << "                      _____|_____       |                                        " << endl;
	cout << "                     |          |       |                                        " << endl;
	cout << "                     |    3     |       |                                        " << endl;
	cout << "                     | �޴��   |       |                                        " << endl;
	cout << "                     | Ģ����   |       |                                        " << endl;
	cout << "                     |__________|       |                                        " << endl;
	cout << "                                    ____|_____                                   " << endl;
	cout << "                                   |    1     |                                  " << endl;
	cout << "                                   | ��ʧɭ�� |                                  " << endl;
	cout << "                                   |  ���    |                                  " << endl;
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



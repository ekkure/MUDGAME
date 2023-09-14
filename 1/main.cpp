#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <fstream> 
#include<windows.h>
#undef max
#include"Game.h"

void GameRun(Game game) {    //��Ϸ���к���
   

    int choice;
    string command;
    while (1) {
        int over = 1;
        int dea = 0;

        cout << "1.��ɫ 2.ս��  3.̽������  4.��ͼ  5.�̵�  6.���� 7.�Ի�  8.�˳���Ϸ" << endl;   //Game menu
        game.displayRoom();
        cout << "��Ҫ��" << endl;
        if (!(cin >> choice)) {
            cin.clear();                                          // �������״̬
            cin.ignore(numeric_limits<streamsize>::max(), '\n');// ����ʣ�������
            cout << "��������Ч��ָ��." << endl;
            continue;
        }
        switch (choice) {
        case 1: {
            cout << game.player.getname() << "�� 1.״̬  2.װ��  3.����" << endl;
            int t;
            cin >> t;
            if (t == 1) {     //��ʾ���״̬������
                cout << game.player.getname() << "    ";
                cout << "Ѫ��:  " << game.player.getcurrentHP() << "/" << game.player.getMaxHP() << endl;
                cout << "����������: " << game.player.getstrength() << "    ����:" << game.player.equippedArmor.getdefense() << "     �ܹ����� :" << game.player.equippedWeapon.getattdamage() + game.player.getstrength() << endl;
                cout << "�ȼ���" << game.player.getlevel() << ", ���飺" << game.player.getexp() << " / " << game.player.getmaxexp() << endl;
            }
            else if (t == 2)//��ʾ����ʹ�õ��������׵�
                game.Whatbeingused();
            else if (t == 3) { //��ʾ����ʹ�õ��������� �Լ� ��������Ʒ �����滻ʹ�õ�
                game.displayInventory();
                cout << endl << "������װ���ŵ�:" << endl;
                game.Whatbeingused();
                if (game.player.inventory.size() > 0) {
                    cout << endl << "1.ʹ��  2.���� ";
                    int cho;
                    if (!(cin >> cho)) {
                        cin.clear();                                          // �������״̬
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');// ����ʣ�������
                        cout << "��������Ч��ָ��." << endl;
                        break;
                    }
                   // cin >> cho;
                    if (cho == 2)
                        break;
                    else if(cho == 1)
                    {   
                        bool havew = 0, havea = 0;

                        Item* eqwe = nullptr; 
                        Item* eqar = nullptr;          //ֻ��ָ������� ���ڸı�ֵ ����ֵ�����ж�
                        for (Item& item : game.player.inventory) {
                            if (item.isused == 1) {
                                if (item.gettype() == WEAPON) {    //Ѱ���Ƿ������õ�װ����ʹ��ָ����ʱ����
                                    havew = 1;
                                    eqwe = &item;
                                }
                                else if (item.gettype() == ARMOR) {
                                    havea = 1;
                                    eqar = &item;
                                }
                            }
                        }
                        cout << "��Ҫʹ��:";
                        string itemName;
                        cin >> itemName;

                        bool have = 0;

                        for (Item& item : game.player.inventory)  //ʹ��for-each ѭ���������� 
                        {
                            if (item.getname() == itemName)   
                            {
                                //cout << item.getname() << endl;;
                                have = 1;                           //�����������Ʒ  
                                if (item.gettype() == HEALING_ITEM) {//������ΪҩƷ
                                 
                                    game.player.useItem(item);//ֱ��ʹ��
                                    break;
                                }
                                else {     //���� �����õ���װ��
                                    if (item.isused == 1) {//����Ҫʹ�õĸ�����ʹ�õ�һ�� ֱ�ӽ���
                                        cout << "������ʹ��"<<item.getname()<<endl;
                                        break;
                                    }
                                    else {  //����ʹ�õ�װ����ͬ                  
                                        if (item.gettype() == WEAPON) {    //����ʹ�õ�Ϊ��������
                                            if (havew) {      //������װ��������
                                                eqwe->isused = 0;//��װ��������ж��
                                                item.isused = 1; //��Ҫʹ�õ�����װ��ȥ��ͨ��һЩ�ض���bool����
                                                game.player.equippedWeapon = item;
                                            }
                                            else {
                                                item.isused = 1;//��û����װ��������
                                                game.player.equippedWeapon = item;//ֱ��װ����ȥ
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
                            cout << "������û�������Ʒ" << endl; //����������û���ҵ���Ӧ��Item
                    }

                    else {
                        cout << "���ָ��ɲ���ŷ" << endl;
                    }
                }
                else
                    cout << "û����Ʒ" << endl;
            }
        }; break;
        case 2: {
            cout << "������Ҫս���ĵ����ǣ����֣�:" << endl;
            for (auto it = game.currentRoom.enemies.begin(); it != game.currentRoom.enemies.end(); ++it)
                cout << it->getname() << "  :������:" << it->getstrength() << "   HP:" << it->getHp() << endl;
            cout << endl;
            string oname;
            bool findv = 1;
            cin >> oname;
            Enemy* fightobject = nullptr;  //��Enemy* Ϊ�β� ���ڲ���
            for (auto it = game.currentRoom.enemies.begin();; ++it)
                if (it == game.currentRoom.enemies.end()) {
                    findv = 0;
                    break;          //û���ҵ���Ӧ�ĵ���
                }
                else if (it->getname() == oname) {
                    fightobject = &(*it); //�ҵ����� ��ָ��ָ���� ��Ϊ�����������β�
                    break;
                }
            if (!findv)
                cout << "����û�� " << oname << endl;
            else {
                if (game.fight(*fightobject)==1) {
                    cout << "������:" << endl;
                    for (Item& item : game.currentRoom.enemyitems) {
                        cout << item.getname() << endl;
                        game.player.inventory.push_back(item);
                        game.player.addexp(50);   //�̶���50   //���Ӿ���ֵ
                    }

                    game.currentRoom.isEnedead = 1;  //���õ�������bool��
                    bool y = game.map.checkTask(game.currentRoom); //��������Ƿ���ɲ��������� ������ʾ

                    game.currentRoom.NPCtalk();            //���һЩ�������
                    game.currentRoom.isfirstde = 0;
                    fightobject->setHp(fightobject->getmaxHp());
                    game.currentRoom.isEnedead = 0;// ���޻ظ�Ѫ��  ���ط����ڵ�������bool��
                }
                
                else if(game.fight(*fightobject)==0){
                    cout << "�ܱ���" << endl;
                    dea = 1;                 //ͨ��fight��������ֵ�ж�
                }
            }

        }; break;
        case 3: {
            if (game.currentRoom.iscleaned==0) {  //ͨ��bool���жϷ����Ƿ��Ѿ�clean ������ͨ��ˢ�·���ȷ�ʽˢ�·�������Ʒ
                cout << "�㷢���� :";            

                for (auto it = game.currentRoom.items.begin(); it != game.currentRoom.items.end(); ++it) {
                    game.player.inventory.push_back(*it);
                    cout << it->getname() << "    ";     //����������Ʒ push�����ﱳ����  
                }
                cout << "200 money" << endl;

                game.player.setmoney(game.player.getmoney() + 200);
                game.currentRoom.iscleaned = 1;                   
                game.map.rooms[game.currentRoom.numm].iscleaned = 1;  /////����ˢ��bool��
            }
            else {
                cout << "û����Ʒ��" << endl;
            }

        }; break;
        case 4: {
            cout << "������λ�ڣ�" << game.currentRoom.name << endl;
            cout << "��ͼ:" << endl;
            ShowMap();
            cout << "�����κΰ������������ͼ";
            string direction;

            if (!(cin >> direction)) {
                cin.clear();                                          // �������״̬
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // ����ʣ�������
                cout << "�㲻��ȥ�����������Ч����" << endl;
            }
            else
                game.move(direction);                               //����� game ����Ϊʹ��ϵͳ�Դ�����move


        }; break;
        case 5: {
            cout << "����Ҫ��1.���� 2.���� 3.�˳�" << endl;
            int choicee;
            if (!(cin >> choicee)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "��������ȷ�����" << endl;
                break;
            }
            //cin >> choicee;
            if (choicee == 1) {
                game.shop.showList();
                string itemName;
                Item itemm;
                cout << "���� " << game.player.getmoney() << " money" << endl;
                cout << "��Ҫ��:";
                cin >> itemName;
                int ishave = 0;
                for(Item& item:game.shop.items)
                    if (item.getname() == itemName) {        
                        ishave = 1;
                        itemm = item;                //���̵��vector���ҵ���Ӧ��Item ������ʱitemm���� ����buy�����β�
                        break;
                    }
                if (!ishave) {
                    cout << "�̵���û������ " << itemName << " ����Ʒ" << endl;
                    break;
                }
                else {
                    cout << "��������Ҫ���������:";
                    int count;
                   // cin >> count;
                    if (!(cin >> count)) {
                        cin.clear();                                          // �������״̬
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');// ����ʣ�������
                        cout << "��������Ч����������������." << endl;
                    }
                    if (game.player.getmoney() < itemm.getprice() * count) {
                        cout << "��û���㹻��Ǯ������" << endl;
                        break;
                    }
                    for (int i = 0; i < count; i++)
                        game.buyItem(itemName);
                    cout << "�㹺���� " << itemName << "* " << count << endl;
                }
            }
            else if (choicee == 2) {
                game.displayInventory();
                cout << "��Ҫ��(������װ��������):";
                string itemName;
                cin >> itemName;
                bool ishavein = 0;
                for (Item& findt : game.player.inventory) {
                    if (findt.isused == 1)                   //��ֹ������װ����װ��
                        continue;
                    if (findt.getname() == itemName) {
                        ishavein = 1;
                        break;
                    }
                }
                if (!ishavein)
                    cout << "���вֿ���û����Ҫ����..." << endl;
                else {
                    cout << "����������Ҫ����������:";
                    int count=0, x = 0;
                    if (!(cin >> count)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "��������ȷ��������" << endl;
                        break;
                    }
                    //cin >> count;
                    for (Item& lookfor : game.player.inventory) {
                        if (lookfor.isused == 1)
                            continue;
                        if (lookfor.getname() == itemName)
                            x++;
                    }                                //���ұ����еĸ���Ʒ������
                    if (x < count) {
                        cout << "��û���㹻������ " << itemName << " ." << endl;
                        break;
                    }
                    for (int i = 0; i < count; i++)
                        game.sellItem(itemName);
                    cout << "�������� " << itemName << " * " << count << endl;
                }
            }
            else if(choicee==3)
                break;
            else {
                cout << "��Ч������ŷ" << endl;
                break;
            }
        }; break;
        case 6: {
            game.map.showTask();   //չʾ��������
        }; break;
        case 7: {
            game.currentRoom.NPCtalk();    //��������������Ի�
        } break;
        case 8: {

            cout << "1.������Ϸ����  2.ֱ���˳�" << endl;
            int qu;
            cin >> qu;
            if (qu == 1) {
                ofstream fileGame("save.dat", ios::out | ios_base::binary);

                if (!fileGame) {
                    cout << "�޷��򿪱����ļ���" << endl;
                    cout << "����ʧ�ܣ�" << endl;
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
                    // ����ȫ��װ��
                    if (invennum > 0) {
                        for (int i = 0; i < invennum; i++) {
                            fileGame << game.player.inventory[i];  //ǰ���ǽ� << ����
                        }

                        //����װ����
                        bool haveWeaeq = 0, haveAreq = 0;
                        for (Item& item : game.player.inventory) {
                            if (item.isused == 1) {
                                if (item.gettype() == WEAPON)
                                    haveWeaeq = 1;
                                else if (item.gettype() == ARMOR)
                                    haveAreq = 1;
                            }
                        }                         //�����Ƿ���װ����bool�� 
                        fileGame << haveWeaeq << ' '
                            << haveAreq << ' ';
                    }
                    //���뷿�����
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
                        if (itemnum > 0) {              //��������������ֵ ���itemnum>0 �ٱ��淿���ڵ���Ʒ
                            for (int j = 0; j < itemnum; j++) {
                                fileGame << game.map.rooms[i].items[j];
                            }
                        }
                    }
                    int currentplace = game.currentRoom.numm;
                    int currtask = game.map.currentTask;      //�����������
                    fileGame << currentplace << ' '
                        << currtask << ' ';

                    cout << "����ɹ���" << endl;
                    fileGame.close();
                    over = 0;
      
                    system("cls");
                }
            }
            else if (qu == 2) {
                ofstream fileGame("save.dat", ios::trunc); // ���ļ����ض�����  ��մ浵
                if (!fileGame) {
                    cout << "�޷��򿪱����ļ���" << endl;
                    cout << "���ʧ�ܣ�" << endl;
                }
                else {
                    cout << "����ֱ���˳���Ϸ" << endl;
                    Sleep(1000);
                    over = 0;
                    cout << "�˳��ɹ���" << endl;
                    fileGame.close();
                }

            }
        }; break;
        default: {
            cout << "��������Ч����" << endl;
        };
        }
        if (!over)
            break;
        if (dea) {
            ofstream fileGame("save.dat", ios::trunc);
            if (!fileGame) {
                cout << "�޷��򿪱����ļ���" << endl;
                cout << "�����˳�ʧ�ܣ�" << endl;
            }
            else {
                fileGame.close();
                cout << "���Ѱܱ� ��ͷ����������.." << endl;
            }
            
            break;
        }
        system("pause");
        system("cls");
    }
}


int main() {
    int colorCode = 32;

    // ��Ϸ����
    string gameName = "ħ��̽��";

    // ��ӡ��Ϸ��ʼ����
    cout << "\n";
    cout << "\t\t\t\t\t" << "\033[1;" << colorCode << "m";  // �����ı���ɫΪ��ɫ

    // ���д�ӡ��ŵ���Ϸ����
    cout << endl << "    ******   *********    *****   *********  ***  *****   ******     ******  " << endl;
    cout << "  **    **     **    **   **   **     **     ***   **   **  **    **   **    **" << endl;
    cout << " **            **    **  **     **    **     ** ** **   **  **         **      " << endl;
    cout << " **            **    **  **     **    **     **  ****   **  **         **      " << endl;
    cout << " **            **    **  **     **    **     **   ***   **  **   ****  **       " << endl;
    cout << "  **    **     **    **   **   **     **     **    **   **   **    **   **    **" << endl;
    cout << "    ******   *********    *****       **     **    **   **    ******     ******  " << endl;

    cout << "\033[0m";  // �����ı���ɫ
    cout << "\n\n";

    system("pause");
    system("cls");

    string background = "    ��һ��ңԶ��ħ����������һ�����ض����ϵ�ɭ�֣�����Ϊ�����֡������ֱ���Ϊ��ħ����Դͷ��������ǧ��ٹֵ�����ͱ��ء�Ȼ�����������ֵĵ�·ȴ�������ɵ����顣��Ƭɭ�ֱ�һϵ�����ض�Σ�յķ�����������ÿ�����䶼������ص���ս�ͱ��ء����ڣ�����һλð�ռң���˵�������̲��Ŵ�˵�еı��غ�ħ������̤����ǰ�����ֵ��ọ́��������ڿ˷�һϵ����ս�������������ﻥ����ͬʱ���⿪�������ɭ�ֵ����ܡ����Ŀ�����ҵ�������Ĵ�˵�еġ�ħ��֮�ġ�����ű�ʯ����Ϊӵ�о޴��ħ�������Ըı����������ˡ�Ȼ�����������Ը��ָ������Ρ�Σ�գ��Լ���NPC��ɫ�Ļ��������ܳɹ������ű�ʯ��������˺��������������˶�ȡ��������������ǻۡ�";
   
    //��ӡ���±���
    for (int i = 0; i < background.size(); i++) {
      cout << background[i];
      Sleep(10);
    }
    cout << endl;

    system("pause");
    system("cls");

    Game game;
start:
    cout << "                                      1.�µ���Ϸ 2.����  3.�˳�" << endl;
    int cho;
    if (!(cin >> cho)) {
        cin.clear();                                          // �������״̬
        cin.ignore(numeric_limits<streamsize>::max(), '\n');// ����ʣ�������
        cout << "Invalid input. Please try again." << endl;
        goto start;
    }
    //����ļ�Ϊ�� ����Ϸ
    //��Ϊ�� ��������
    // ����һ���������˳�
    if (cho == 1) {
        ofstream fileGame("save.dat", ios::trunc); // ���ļ����ض�����
        if (!fileGame) {
            cout << "�޷��򿪱����ļ���" << endl;
            cout << "���ʧ�ܣ�" << endl;
        }
        else
            cout << "��ʼһ���µ�ð��" << endl;
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
        if (inGame.peek() != EOF) {  //�������ļ�Ϊ��   
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
            cout << "����ɹ���" << endl;
            GameRun(game);
        }
        else {
            cout << "û����Ϸ�浵����" << endl;
            inGame.close();
        }
    }
    else if (cho == 3)
        return 0;
    else
        cout << "����������" << endl;

    goto start;
    return 0;
}


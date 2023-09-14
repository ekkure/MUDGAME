#include"Game.h"
#include<stdio.h>
#include<windows.h>
#include<conio.h>
int N;

void Game::initialize(int cho) {                                      
    // ��ʼ���������
    if (cho == 0) {
        cout << "�������ɫ����" << endl;
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
    //��ʼ����ҵĸ�������

    

     // ��ʼ������
    for (int i = 0; i < 10; i++) {
        map.rooms[i].numm = i;
        map.rooms[i].enemies.clear();
        map.rooms[i].enemyitems.clear();
        map.rooms[i].items.clear();  //����� ��ֹ����������ʼ��ʱ����
    }

    //�Ը���������Գ�ʼ�� ����ʼ���������Ʒ�Լ����� �����Ӧ�Ĺ������
    map.rooms[0].name = "��ʧɭ�����";
    map.rooms[0].items.push_back(Item{ "ħ���ָ���", 200, ItemType::HEALING_ITEM,0,0,50 });
    map.rooms[0].items.push_back(Item{ "ذ��",100,ItemType::WEAPON,30,0,0 });
    map.rooms[0].enemyitems.push_back(Item{ "��Ӱذ��",500,ItemType::WEAPON,60,0,0 });
    map.rooms[0].enemies.push_back(Enemy{ "����", 10, 50, 50,3 });
    map.rooms[0].towards[4] = &map.rooms[1];
    map.rooms[0].NPC[0] = "���ˣ�˭��̤���ҵ��������߿�����������ڵģ��������ܰ����ҵ���ʧɭ�ֵ����ػ��䡣";  // �״μ�������
    map.rooms[0].NPC[1] = "���ˣ��ߣ���ȿ���ȥǿ��������Ľ����������뿪��Ƭɭ�֣���Ҫ��ס�����ػ��������������������";  //�״λ��ܵ���
    map.rooms[0].NPC[2] = "���ˣ����ֻ����ˣ���������ľ����ˡ�����Ѱ����Щ���ػ��䣬���ǻ������ð���з������á�"; //�ڶ��μ��Ժ���ܵ���
    map.rooms[0].NPC[3] = "�����ҩʦ������ӭ���¸ҵ�̽���ߡ����ǲ�ҩʦ����������Ҫ��ҩ�������˺����ҿ��԰����㡣";//��������
    map.rooms[0].NPC[4] = "�����ҩʦ�������ҵ������ػ��䣬�����Ƿǳ����Ĳ�ҩ��ϣ�������������ð���а����㡣";  //�ɹ��ɼ����ػ����
    map.rooms[0].NPC[5] = "�����ҩʦ��:��ӭ������̽���ߡ�������ٴ���Ҫ��ҩ��ֻ�����ҡ�";//�ڶ��μ��Ժ�������˺�

    map.rooms[1].name = "��˸��ӫ�ⶴѨ";
    map.rooms[1].items.push_back(Item{ "ħ���ָ���", 200, ItemType::HEALING_ITEM,0,0,50 });
    map.rooms[1].enemies.push_back(Enemy{ "����", 20, 80,80, 3 });
    map.rooms[1].enemyitems.push_back(Item{ "��Ӱذ��",500,ItemType::WEAPON,60,0,0 });
    map.rooms[1].towards[3] = &map.rooms[3];
    map.rooms[1].towards[1] = &map.rooms[4];
    map.rooms[1].towards[2] = &map.rooms[0];
    map.rooms[1].NPC[0] = "��ӭ����ӫ�ⶴѨ��İ���ˡ�����Ҫ�ҵ�ӫ��Ģ�����������ﰲȫ���ߡ������ȣ������ش��ҵ����⡣";//���״μ���ӫ��Ģ�����飩��
    map.rooms[1].NPC[1] = "��ܴ���������ӫ��Ģ�������ǽ�Ϊ�����ǰ���ĵ�·����ҪС�Ķ�Ѩ��Ĺ��";//���ش���ȷ����󣩣�
    map.rooms[1].NPC[2] = "лл������������ڣ�����Լ���ǰ���������ס��ӫ��Ģ����������ѡ�";  //���״λ��ܹ����
    map.rooms[1].NPC[3] = "�ˣ�İ���ˡ���ӭ����ӫ�ⶴѨ���ҿ��Ը���һЩӫ��Ģ�����������ش��ҵ����⡣"; //���ֹ⣨ӫ��Ģ�����飩:�������ֹ⣺
    map.rooms[1].NPC[4] = "̫���ˣ�����ӫ��Ģ������ȥ�ɡ����ǽ�Ϊ������ǰ���ĵ�·��";//�ش���ȷ�����
    map.rooms[1].NPC[5] = "�����˹�����˲���ӫ��Ģ����������ѣ����ǽ������㡣";//�״λ��ܹ����

    map.rooms[2].name = "�޴��Ģ����";
    map.rooms[2].items.push_back(Item{ "ħ���ָ���", 200, ItemType::HEALING_ITEM,0,0,50 });
    map.rooms[2].enemyitems.push_back(Item{ "��Ӱذ��",500,ItemType::WEAPON,60,0,0 });
    map.rooms[2].enemies.push_back(Enemy{ "Ģ����������", 30, 120,120, 3 });
    map.rooms[2].towards[4] = &map.rooms[3];
    map.rooms[2].NPC[0] = "��ӭ���¸ҵ�̽���ߡ�ֻ�н⿪�������⣬����ܴ�Խ��ƬĢ���֡�";//���״μ���Ģ���������죩��
    map.rooms[2].NPC[1] = "��ش�öԣ�����ֻ�ǿ�ʼ����һ��������ǰ�������㡣";  //���ش��һ�������
    map.rooms[2].NPC[2] = "��֤�����Լ���ֵ�������ġ����ڣ�����Դ�ԽĢ���֣�����С�ģ�������û��Σ�յġ�";//���ɹ��⿪�������⣩��
    map.rooms[2].NPC[3] = " ��ӭ����Ģ���֣�İ���ˡ�ֻ�н⿪�������⣬����ܴ�Խ��ƬĢ���֡�"; //Ģ������������Ģ��������
    map.rooms[2].NPC[4] = " ����ǻ���������ӡ����̣�����ǰ���ɣ���һ��������ǰ��������";//�ش��һ�������
    map.rooms[2].NPC[5] = " ��֤�����Լ���ֵ�������ġ����ڣ�����Դ�ԽĢ���֣�����С�ģ�������û��Σ�յġ�"; //�ɹ��⿪���������

    map.rooms[3].name = "���ڵ�����Ĺ��";
    map.rooms[3].items.push_back(Item{ "ħ���ָ���", 200, ItemType::HEALING_ITEM,0,0,50 });
    map.rooms[3].enemyitems.push_back(Item{ "��Ӱذ��",500,ItemType::WEAPON,60,0,0 });
    map.rooms[3].enemies.push_back(Enemy{ "��������", 35, 150,150 ,3 });
    map.rooms[3].towards[2] = &map.rooms[2];
    map.rooms[3].towards[4] = &map.rooms[6];
    map.rooms[3].towards[3] = &map.rooms[5];
    map.rooms[3].towards[1] = &map.rooms[1];
    map.rooms[3].NPC[0] = "˭�Ҵ������ǵ���������ֻ�������ȴ��㡣";//���״μ��������������������
    map.rooms[3].NPC[1] = "�����������ӡ����̣�̽���ߡ����ҵ���������֮�ڣ���������Լ���ǰ����ͬʱ����������Ĺ�ص���ʷ��¼����������а�����";//���״λ��������������ҵ���ʷ��¼����
    map.rooms[3].NPC[2] = "���ֻ����ˣ����ߡ���������ڽ�����";// �ڶ��μ��Ժ����������������
    map.rooms[3].NPC[3] = "�� ������Ѱ��������֮�ڵ����ҿ��԰����㡣��������ռ�Ĺ�ص���ʷ��¼��";//����˿����ʷѧ�ң�����������˿
    map.rooms[3].NPC[4] = "���ҵ�����ʷ��¼���ǳ���л�����ڣ�������֮��������ˡ�";//�ҵ���ʷ��¼�������ź�
    map.rooms[3].NPC[5] = "��ӭ���������ߡ���ʷ�������޼۵ġ�";//�ڶ��μ��Ժ��������������

    map.rooms[4].name = "ħ����ˮ���ٲ�";
    map.rooms[4].items.push_back(Item{ "ħ���ָ���", 200, ItemType::HEALING_ITEM,0,0,50 });
    map.rooms[4].enemyitems.push_back(Item{ "��Ӱذ��",500,ItemType::WEAPON,60,0,0 });
    map.rooms[4].enemies.push_back(Enemy{ "ˮ������", 35, 180,180, 3 });
    map.rooms[4].towards[3] = &map.rooms[1];
    map.rooms[4].towards[4] = &map.rooms[8];
    map.rooms[4].NPC[0] = "��ӭ����ˮ���ٲ���̽���ߡ�ֻ��ˮ��֮�Ĳ��ܽ�����Щħ��ˮ����������";//���״μ���ˮ����������
    map.rooms[4].NPC[1] = "���Ѿ�֤�����Լ���ħ������⡣���ڣ�����Բɼ�ħ��ˮ�����������ǵ����������Լ���ͬʱ������ˮ������ʧ������࣬��������������������";//���ش����Ⲣ�ҵ�ˮ��֮�ģ���
    map.rooms[4].NPC[2] = "���ٴ��������̽���ߡ�����Σ��ҽ������������顣";//���ڶ��μ��Ժ����ˮ����������
    map.rooms[4].NPC[3] = " ����ħ��ˮ���ٲ���̽���ߡ�ֻ��ˮ��֮�Ĳ��ܽ�����Щˮ����������";//�����ȣ�ˮ�������������������ȣ�
    map.rooms[4].NPC[4] = "���Ѿ�֤�����Լ���ħ������⡣���ڣ�����Բɼ�ħ��ˮ�����������ǵ����������Լ���";//�ش����Ⲣ�ҵ�ˮ��֮�ĺ�
    map.rooms[4].NPC[5] = "��ӭ������İ���ˡ�ˮ��֮������ģ��������С��ʹ������";//�ڶ��μ��Ժ����ˮ��������

    map.rooms[5].name = "����֮Ȫ";
    map.rooms[5].items.push_back(Item{ "ħ���ָ���", 200, ItemType::HEALING_ITEM,0,0,50 });
    map.rooms[5].enemyitems.push_back(Item{ "��Ӱذ��",500,ItemType::WEAPON,60,0,0 });
    map.rooms[5].enemies.push_back(Enemy{ "����", 40, 200,200, 3 });
    map.rooms[5].towards[1] = &map.rooms[3];
    map.rooms[5].NPC[0] = "İ���ˣ����������������ҵ�ħ������������͵���ˡ�������ܰ����һ������ҽ��̸���һ��ǿ������";//���״μ���������������
    map.rooms[5].NPC[1] = "�����Ǹ������ˣ�İ���ˡ���Ϊ��л���ҽ����ڸ���������������ð���������ó���";//���ɹ��һ�ħ����������
    map.rooms[5].NPC[2] = "���ٴλ����ˣ��ҵľ��ǡ��ҵ�ħ�������ٴα����������������һ�����";//���ڶ��μ��Ժ���ܵ������һ�ħ��������
    map.rooms[5].NPC[3] = "�������ݣ������������ҵ����ҵ�ħ������������͵���ˡ���������һ������ҽ�������һ�����";//���ݣ�������������
    map.rooms[5].NPC[4] = "лл��İ�����İ���ˡ����ڣ��ҽ������ҵ�ŵ�ԣ����ڸ���һ��ǿ������"; //�ɹ��һ�ħ��������
    map.rooms[5].NPC[5] = "���ٴ���������ҵľ��ǡ��ҵ�ħ�������ٴα����������������һ�����";//�ڶ��μ��Ժ���ܵ������һ�ħ��������
    //////////////////////////////////////////////////////
    map.rooms[6].name = "���߶�";
    map.rooms[6].items.push_back(Item{ "Sword7", 50, ItemType::WEAPON ,10,0,0 });
    map.rooms[6].items.push_back(Item{ "ħ���ָ���", 200, ItemType::HEALING_ITEM,0,0,50 });
    map.rooms[6].enemies.push_back(Enemy{ "����Ů��", 50, 300,300, 3 });
    map.rooms[6].towards[2] = &map.rooms[3];
    map.rooms[6].NPC[0] = "���Ƕ��ߵ���أ�İ���ˡ�ֻ�н������أ�������뿪��������ȣ�����Ҫ�����ռ����ߵĶ�Һ��";//���״μ�������Ů������
    map.rooms[6].NPC[1] = "�����������İ���ˡ����ڣ�������뿪��ƬΣ�յĵط�����Щ��ҺҲ������ð������������";//���������ز��ռ����߶�Һ����
    map.rooms[6].NPC[2] = "���ٴλ��������ߡ������û���ӹ���";//���ڶ��μ��Ժ���ܶ���Ů������
    map.rooms[6].NPC[3] = "�������ȣ����Ƕ��ߵ���أ�İ���ˡ�ֻ�н������أ�������뿪��������ȣ�����Ҫ�����ռ����ߵĶ�Һ��";//���ȣ�����Ů������
    map.rooms[6].NPC[4] = "�����������İ���ˡ����ڣ�������뿪��ƬΣ�յĵط�����Щ��ҺҲ������ð������������";//�������ز��ռ����߶�Һ��
    map.rooms[6].NPC[5] = "�������ˣ����ߡ������û���ӹ���";//�ڶ��μ��Ժ���ܶ���Ů����

    map.rooms[7].name = "��֮��Ѩ";
    map.rooms[7].items.push_back(Item{ "Sword8", 50, ItemType::WEAPON ,10,0,0 });
    map.rooms[7].items.push_back(Item{ "ħ���ָ���", 200, ItemType::HEALING_ITEM,0,0,50 });
    map.rooms[7].enemies.push_back(Enemy{ "����", 80, 350,350, 3 });
    map.rooms[7].towards[1] = &map.rooms[8];
    map.rooms[7].NPC[0] = "������Ƭɭ�ֵ��ػ��ߣ�ֻ�����߲������ҶԻ�����������ȡ�ҵı��أ������֤���Լ���������";//�״μ�����������
    map.rooms[7].NPC[1] = "��ͨ�����ҵĿ��飬���ߡ����ڣ������ȡ���ҵı��أ���������Ǹ������Ρ�";//���ɹ��⿪�ػ�֮�գ���
    map.rooms[7].NPC[2] = "���ֻ����ˣ�İ���ˡ����Ƿ�׼�����ٴν����ҵĿ��飿";//���ڶ��μ��Ժ����������
    map.rooms[7].NPC[3] = " ������Ƭɭ�ֵ��ػ��ߣ�ֻ�����߲������ҶԻ�����������ȡ�ҵı��أ������֤���Լ���������";//������˹�������ػ��ߣ�������������˹��
    map.rooms[7].NPC[4] = "��ͨ�����ҵĿ��飬���ߡ����ڣ������ȡ���ҵı��أ���������Ǹ������Ρ�";//�ɹ��⿪�ػ�֮�պ� 
    map.rooms[7].NPC[5] = "���ٴλ�����İ���ˡ����Ƿ�׼�����ٴν����ҵĿ��飿";//�ڶ��μ��Ժ��������

    map.rooms[8].name = "���Ķĳ�";
    map.rooms[8].items.push_back(Item{ "Sword9", 50, ItemType::WEAPON ,10,0,0 });
    map.rooms[8].items.push_back(Item{ "ħ���ָ���", 200, ItemType::HEALING_ITEM,0,0,50 });
    map.rooms[8].enemies.push_back(Enemy{ "̰���Ķĳ��ϰ�", 90, 400,400, 3 });
    map.rooms[8].towards[2] = &map.rooms[4];
    map.rooms[8].towards[3] = &map.rooms[7];
    map.rooms[8].towards[1] = &map.rooms[9];
    map.rooms[8].NPC[0] = "��ӭ�����ҵĶĳ���İ���ˡ��������Ӯ���㹻�Ľ�ң��ҽ�Ϊ���ṩͨ�����汦���ҵ�ͨ��֤��";//���״ν���ĳ�����
    map.rooms[8].NPC[1] = "�����������İ���ˡ�����ͨ���汦���ҵ�ͨ��֤�������ס���ĳ��е�ʤ���������ǳ��õġ�";//��Ӯ���㹻�Ľ�Ҳ���ȡͨ��֤����
    map.rooms[8].NPC[2] = "��ӭ������̽���ߡ���������ս��������";//���ڶ��μ��Ժ����ĳ�����
    map.rooms[8].NPC[3] = "�����Ϳ�˹����ӭ�����ҵĶĳ���İ���ˡ��������Ӯ���㹻�Ľ�ң��ҽ�Ϊ���ṩͨ�����汦���ҵ�ͨ��֤��";//�Ϳ�˹���ĳ��ϰ壩��
    map.rooms[8].NPC[4] = " �����������İ���ˡ�����ͨ���汦���ҵ�ͨ��֤�������ס���ĳ��е�ʤ���������ǳ��õġ�";//Ӯ���㹻�Ľ�Ҳ���ȡͨ��֤��
    map.rooms[8].NPC[5] = "��ӭ������̽���ߡ���������ս��������";//�ڶ��μ��Ժ����ĳ���

    map.rooms[9].name = "���汦����";
    map.rooms[9].items.push_back(Item{ "Sword10", 50, ItemType::WEAPON ,10,0,0 });
    map.rooms[9].items.push_back(Item{ "ħ���ָ���", 200, ItemType::HEALING_ITEM,0,0,50 });
    map.rooms[9].enemies.push_back(Enemy{ "�����ҵ��ػ���", 100, 500,500, 3 });
    map.rooms[9].towards[3] = &map.rooms[8];
    map.rooms[9].NPC[0] = "���ǵ�һ������������ˣ�İ���ˡ�ֻ�д������˲��ܽ⿪���ص����⡣׼��������";//���״μ��������ҵ��ػ��ߣ���
    map.rooms[9].NPC[1] = "����ǻ�����ӡ����̣�İ���ˡ����ڣ���������ߴ��汦�أ���Ҫ��ס�������ܱ�������ĸ�Σ�ա�";//���ɹ��⿪���صı������ƣ���
    map.rooms[9].NPC[2] = "�������ˣ�̽���ߡ���Σ����Ƿ����ٴν⿪���⣿������֮�ؽ���ʾ��������ࡣ";//���ڶ��μ��Ժ���뱦���ң���
    map.rooms[9].NPC[3] = "���ǵ�һ������������ˣ�İ���ˡ�ֻ�д������˲��ܽ⿪���ص����⡣׼��������";//���Ͼ������������Ͼ�����
    map.rooms[9].NPC[4] = "����ǻ�����ӡ����̣�İ���ˡ����ڣ���������ߴ��汦�أ���Ҫ��ס�������ܱ�������ĸ�Σ�ա�";//�ɹ��⿪���صı������ƺ� 
    map.rooms[9].NPC[5] = "�������ˣ�̽���ߡ���Σ����Ƿ����ٴν⿪���⣿������֮�ؽ���ʾ��������ࡣ";//�ڶ��μ��Ժ���뱦���Һ�

    currentRoom = map.rooms[0];
   
    // ��ʼ���̵�

    shop.items.push_back(Item{ "ħ��֮��",1000,ItemType::WEAPON,100,0,0 });
    shop.items.push_back(Item{ "ħ������",800,ItemType::WEAPON,80,0,0 });
    shop.items.push_back(Item{ "�ɻ�֮��",1500,ItemType::WEAPON,120,0,0 });
    shop.items.push_back(Item{ "��Ӱذ��",500,ItemType::WEAPON,60,0,0 });
    shop.items.push_back(Item{ "ħ��֮ŭ",2000,ItemType::WEAPON,150,0,0 });
    shop.items.push_back(Item{ "Ӱ��˫��",1000,ItemType::WEAPON,90,0,0 });
    shop.items.push_back(Item{ "��Ӱ֮ì",1200,ItemType::WEAPON,70,0,0 });
    shop.items.push_back(Item{ "ħƤս��",800,ItemType::ARMOR,0,50,0 });
    shop.items.push_back(Item{ "����ս��",1200,ItemType::ARMOR,0,70,0 });
    shop.items.push_back(Item{ "��������",2000,ItemType::ARMOR,0,100,0 });
    shop.items.push_back(Item{ "��Ӱ����",1500,ItemType::ARMOR,0,80,0 });
    shop.items.push_back(Item{ "����ʥװ",2500,ItemType::ARMOR,0,120,0 });
    shop.items.push_back(Item{ "����֮��", 150, ItemType::HEALING_ITEM,0,0,30 });
    shop.items.push_back(Item{ "Ѫ����ҩ", 300, ItemType::HEALING_ITEM,0,0,80 });
    shop.items.push_back(Item{ "����֮��", 200, ItemType::HEALING_ITEM,0,0,40 });
    shop.items.push_back(Item{ "ħ���ָ���", 200, ItemType::HEALING_ITEM,0,0,50 });
    shop.items.push_back(Item{ "��꾻����", 500, ItemType::HEALING_ITEM,0,0,100 });
    shop.items.push_back(Item{ "ħ��������", 300, ItemType::HEALING_ITEM,0,0,70 });
    shop.items.push_back(Item{ "ħ�����߲�ҩ", 600, ItemType::HEALING_ITEM,0,0,120 });
    shop.items.push_back(Item{ "ħ����������",1000,ItemType::ARMOR,0,60,0 });
    shop.items.push_back(Item{ "������������",1500,ItemType::ARMOR,0,90,0 });
    
}
 
void Game::displayRoom() { // չʾ����
    cout << "���� " << currentRoom.name << endl;
    cout << "�����ڵĵ���: ";
    for ( Enemy& enemy : currentRoom.enemies) {
        cout << enemy.getname() << " ";
    }
    cout << endl;
}

void Game::move(string direction) {//�ƶ����� ʹ�ÿ���̨����
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
    ChangeColor(); pos(50, 30); printf("ʹ��WSAD�����ƶ�");
    cout << "\033[0m";  // �����ı���ɫ
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
            pos(i, 20); printf("��");
        }
        for (int j = 0; j < 20; j++) {
            pos(40, j); printf("��");
        }
        for (int i = 0; i < 40; i++) {
            pos(i, 0); printf("��");
        }
        for (int j = 0; j < 20; j++) {
            pos(0, j); printf("��");
        }
      

        pos(x_pos, y_pos); printf("��");
        if (x_pos >= 39)
            x_pos=x_pos - 1;
        if (y_pos > 19)
            y_pos=y_pos - 1;
        pos(40, 22); printf("%d,%d", x_pos, y_pos);
        pos(50, 2); printf("1:��ʧɭ�����");
        pos(50, 4); printf("2:��˸��ӫ�ⶴѨ");
        pos(50, 6); printf("3:�޴��Ģ����");
        pos(50, 8); printf("4:���ڵ�����Ĺ��");
        pos(50, 10); printf("5:ħ����ˮ���ٲ�");
        pos(50, 12); printf("6:����֮Ȫ");
        pos(50, 14); printf("7:���߶�");
        pos(50, 16); printf("8:��֮��Ѩ");
        pos(50, 18); printf("9:���Ķĳ�");
        pos(50, 20); printf("10:���汦����");
        pos(10, 25); printf("ע�����ڷ�Χ���ƶ�");

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

void Game::pickUpItem(const string& itemName) {  //ʰȡ����
    //�� ����ʱ���ṩ����name
    if (currentRoom.iscleaned) {
        cout << "The room is cleaned" << endl;
        return; 
    }
    for (auto it = currentRoom.items.begin(); it != currentRoom.items.end(); ++it) {
        if (it->getname() == itemName) {
            player.inventory.push_back(*it);
            currentRoom.items.erase(it);
            cout << "������� " << itemName << endl;
            return;
        }
    }
    cout << "������û����Ʒ��" << endl;
}

void Game::dropItem(const string& itemName) {                 //�� һ��
    for (auto it = player.inventory.begin(); it != player.inventory.end(); ++it) {
        if (it->getname() == itemName) {
            currentRoom.items.push_back(*it);
            player.inventory.erase(it);
            cout << "���ӳ��� " << itemName << endl;
            if (it->isused == 1)
                it->isused = 0;
            return;
        }
    }

    cout << "������û�и���Ʒ!" << endl;
}

void Game::displayInventory() {                             //չʾװ����
    cout << "�����ڵ���Ʒ�� ";
    for ( Item& item : player.inventory) {
        if (item.isused == 0)
            cout << item.getname() << "  ";
    }
    cout << endl;
    cout << "��  " << player.getmoney() << "  money ����" << endl;
    
}

void Game::displayShop() {                               //չʾ�̵�
    cout << "��Ʒ�б�: " << endl;
    for ( Item& item : shop.items) {
        cout << item.getname() << " - �۸�: " << item.getprice() << endl;
    }
}

void Game::buyItem(const string& itemName) {              //���� �������ṩname
    for (auto it = shop.items.begin(); it != shop.items.end(); ++it) {
        if (it->getname() == itemName) {
            if (player.getmoney() >= it->getprice()) {
                player.inventory.push_back(*it);
                player.setmoney(player.getmoney() - it->getprice());
                // shop.items.erase(it);                //�̵�������

            }
            else {
                cout << "Ǯ���� " << itemName << endl;
            }
            return;
        }
    }
    cout << "�̵���û�������Ʒ!" << endl;
}

void Game::sellItem(const string& itemName) {
    for (auto it = player.inventory.begin(); it != player.inventory.end(); ) {
        if (it->getname() == itemName) {
            player.setmoney( player.getmoney() + it->getprice());
            //shop.items.push_back(*it);
            it = player.inventory.erase(it);  // ���µ�������������ָ����һ��Ԫ��
            return;
        }
        else {
            ++it;  // ��������
        }
    }
    cout << "������û�и���Ʒ!" << endl;
}

void Game::Whatbeingused() {
    int count = 0;
    for (auto it = player.inventory.begin(); it != player.inventory.end(); ++it)
        if (it->isused) {
            count++;
            if (it->gettype() == WEAPON)
                cout << "������ʹ�õ�����: " << it->getname() << endl;
            else if (it->gettype() == ARMOR)
                cout << "������װ���Ļ���: " << it->getname() << endl;
        }
    if (count == 0)
        cout << "û������ʹ�õ�װ����" << endl;
}

int Game::fight(Enemy& badguy) {
    cout << "��ʼ�� " << badguy.getname() << "��ս��" << endl;
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
            cout << "�㱻����� "  << endl;
            return 0;
        }
        else if (badguy.getHp() <= 0)
        {
            cout << "������ " << badguy.getname() << " ,������һЩ��Ʒ����" << endl;
            return 1;
        }
        cout << "------------------------------" << endl;
        cout << "��" << round << " �غ�" << endl;
        cout << player.getname() << "   Ѫ��: " << player.getcurrentHP() << "/" << player.getMaxHP() <<"   ����"<<player.getcurrmana()<<" / "<<player.getmaxmana() << " �з���:" << badguy.getHp() << endl;
        cout << "����Ҫ :1.����  2. �ҩ  3.����" << endl;
        int fc;
        cin >> fc;
        if (fc == 1) {
            cout << "��Ҫ�ã�1." << s[0] << " 2." << s[1] << " 3. " << s[2] <<" 4.ƽa����" << endl;
            int uchoice;
            cin >> uchoice;
            player.attackEnemy(badguy, uchoice);
            if (badguy.getstrength() > player.equippedArmor.getdefense() && badguy.getHp() > 0) {
                cout << badguy.getname() << " ��������� " << badguy.getstrength() - player.equippedArmor.getdefense() << " ���˺�" << endl;
                cout << "------------------------------" << endl;
                system("pause");
                system("cls");
                int hp = player.getcurrentHP() - (badguy.getstrength() - player.equippedArmor.getdefense());
                player.setcurrent(hp);
            }
            else if (badguy.getstrength() <= player.equippedArmor.getdefense() && badguy.getHp() > 0) {
                cout << "��Ļ��׸��ڵ��˵Ĺ������������ܶ�������˺���" << endl;
                cout << "------------------------------" << endl;
                system("pause");
                system("cls");
            }
        }
        else if (fc == 2) {
            string Itemname;
            cout << "������:" << endl;
            int count = 0;
            for (Item& item : player.inventory) {
                if (item.gettype() == HEALING_ITEM) {
                    count++;
                    cout << item.getname() << "   ";
                }
            }
            if (!count) {
                cout << "��ı�����û�е�ҩ����ʹ�� " << endl;
                if (badguy.getstrength() > player.equippedArmor.getdefense()) {
                    cout << badguy.getname() << " ��������� " << badguy.getstrength() - player.equippedArmor.getdefense() << " ���˺�" << endl;
                    int hp = player.getcurrentHP() - (badguy.getstrength() - player.equippedArmor.getdefense());
                    player.setcurrent(hp);
                    cout << "------------------------------" << endl;
                    system("pause");
                    system("cls");
                }
                else {
                    cout << "��Ļ��׸��ڵ��˵Ĺ������������ܶ�������˺���" << endl;
                    cout << "------------------------------" << endl;
                    system("pause");
                    system("cls");
                }
                continue;
            }
            cout << endl;
            cout << "��������Ҫʹ�õ�ҩƷ:" << endl;
            cin >> Itemname;
            for (Item& item : player.inventory)
                if (item.getname() == Itemname) {
                    player.useItem(item);
                }
            if (badguy.getstrength() > player.equippedArmor.getdefense()) {
                cout << badguy.getname() << "���õ�ҩ�����޵н��� ���˶����޷�����˺� "  << endl;
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
            cout << "���ݶȵ��ڵ��ˣ��ܲ���һ�������,�װ�һ����.." << endl;
            if (badguy.getstrength() > player.equippedArmor.getdefense() && badguy.getHp() > 0) {
                cout << badguy.getname() << " ��������� " << badguy.getstrength() - player.equippedArmor.getdefense() << " ���˺�" << endl;
                cout << "��Ļ��׸��ڵ��˵Ĺ������������ܶ�������˺���" << endl;
                cout << "------------------------------" << endl;
                system("pause");
                system("cls");
                int hp = player.getcurrentHP() - (badguy.getstrength() - player.equippedArmor.getdefense());
                player.setcurrent(hp);
            }
            else if (badguy.getstrength() <= player.equippedArmor.getdefense() && badguy.getHp() > 0) {
                cout << "��Ļ��׸��ڵ��˵Ĺ������������ܶ�������˺���" << endl;
                cout << "��Ļ��׸��ڵ��˵Ĺ������������ܶ�������˺���" << endl;
                cout << "------------------------------" << endl;
                system("pause");
                system("cls");
            }


        }
    }
}
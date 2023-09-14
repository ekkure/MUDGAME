#include"Shop.h"
#include<iomanip>


void Shop::showList() {
    for (auto it = items.begin(); it != items.end(); ++it) {
        cout << setiosflags(ios::left);

        cout << setw(18) << it->getname() <<setw(18) << it->getprice() ;
        if (it->gettype() == WEAPON)
            cout << setw(18) << "      �������ԣ�" << it->getattdamage() << endl;
        else if(it->gettype()==ARMOR)
            cout << setw(18) << "      �������ԣ�" << it->getdefense() << endl;
        else if(it->gettype()==HEALING_ITEM)
            cout << setw(18) << "      �������ԣ�" << it->gethealing() << endl;
    }
    //��ʽ��ӡ

}

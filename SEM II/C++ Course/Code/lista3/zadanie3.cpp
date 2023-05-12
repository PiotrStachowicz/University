#include "Header.hpp"
int main(void){
    liczba l = liczba();
    l.add(1);
    cout << "Current:" << l.getcurrent() << endl;
    l.print();
    cout << "--------" << endl;
    l.add(2);
    cout << "Current:" << l.getcurrent() << endl;
    l.print();
    cout << "--------" << endl;
    l.add(3);
    cout << "Current:" << l.getcurrent() << endl;
    l.print();
    cout << "--------" << endl;
    l.add(4);
    cout << "Current:" << l.getcurrent() << endl;
    l.print();
    cout << "--------" << endl;
    l.add(5);
    cout << "Current:" << l.getcurrent() << endl;
    l.print();
    cout << "--------" << endl;
    l.add(6);
    cout << "Current:" << l.getcurrent() << endl;
    l.print();
    cout << "--------" << endl;
    l.add(7);
    cout << "Current:" << l.getcurrent() << endl;
    l.print();
    cout << "--------" << endl;
    // konstruktor kopiujący
    liczba lprim = liczba(l);
    // konstruktor przenoszący
    liczba lprimprim = liczba(std::move(lprim));
    // operator kopiujący
    liczba lprimprimprim = liczba();
    lprimprimprim.operator=(lprimprim);
    // operator przenoszący
    liczba l1 = liczba();
    l.operator=(std::move(lprimprim));
    l.add(1);
    l.add(2);
    l.add(3);
    l.add(4);
    cout << "Current:" << l.getcurrent() << endl;
    l.print();
    cout << "--------" << endl;
    l.goback();
    l.goback();
    cout << "Current:" << l.getcurrent() << endl;
    l.print();
    cout << "--------" << endl;
    return 0;
}
#include "Header.hpp"
int main(int argc, char* argv[]){
    tab_bit t(100); // tablica 46-bitowa (zainicjalizowana zerami)
    tab_bit h(46);
    tab_bit u(45ull); // tablica 64-bitowa (sizeof(uint64_t)*8)
    cout << u << endl;
    tab_bit v(t); // tablica 46-bitowa (skopiowana z t)
    tab_bit x(move(u));
    //cout << x << endl;
    initializer_list<bool> initializerList = {1, 0, 1, 1, 0, 0, 0, 1};
    tab_bit w(initializerList); // tablica 8-bitowa (przeniesiona)
    v[0] = 1; // ustawienie bitu 0-go bitu na 1
    t[1] = true; // ustawienie bitu 45-go bitu na 1
    cout << t << endl;
    // bool b = v[1]; // odczytanie bitu 1-go
    u[45] = true;
    u[45] = u[46] = u[63]; // przepisanie bitu 63-go do bitow 45-go i 46-go
    cout<<v<<endl; // wysietlenie zawartości tablicy bitów na ekranie
    tab_bit pp(45);
    cin >> pp;
    cout << pp << endl;
    t = !t;
    tab_bit j(45);
    j = !j;
    tab_bit i(45);
    i |= j;
    cout << i << endl;
    i &= j;
    cout << i << endl;
    cout << t << endl;
    t |= t; // dostaniemy to samo
    cout << t << endl;
    return 0;
}
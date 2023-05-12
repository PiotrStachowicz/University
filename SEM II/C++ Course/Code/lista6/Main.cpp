#include "Header.hpp"

int main(int argc, char* argv[]){
    zmienna *x = new zmienna("x");
    zmienna *y = new zmienna("y");
    zmienna::dodaj_zmienna("x",0); // defaultowo
    zmienna::dodaj_zmienna("y",0); // defaultowo
    //(x-1)*x/2
    wyrazenie *w1 = new dziel(
            new mnoz(
                    new odejmij(x, new liczba(1)), x),
                    new liczba(2));
    cout << w1->zapis() << endl;
    //(3+5)/(2+x*7)
    wyrazenie *w2 = new dziel(
            new dodaj(
                    new liczba(3), new liczba(5)), new dodaj(
                            new liczba(2),
                            new mnoz(x, new liczba(7))));
    cout << w2->zapis() << endl;
    //(2+x*7)-(y*3+5)
    wyrazenie *w3 = new odejmij(
            new dodaj(
                    new liczba(2),
                    new mnoz(x,new liczba(7))),
                    new dodaj(new mnoz(y,new liczba(3)),
                              new liczba(5)));
    cout << w3->zapis() << endl;
    //cos((x+1)*pi)/e^x^2
    wyrazenie *w4 = new dziel(
            new cos_fun(
                    new mnoz(
                            new dodaj(x, new liczba(1)),
                            new pi())), new exp_fun(
                                    new potega(x, new liczba(2))));
    cout << w4->zapis() << endl;
    // pi-(2+x*7)
    wyrazenie *w5 = new odejmij(
            new pi(), new dodaj(
                    new liczba(2), new mnoz(x, new liczba(7))));
    cout << w5->zapis() << endl;
    cout << "TESTY!:" << endl;
    for(double val = 0.0 ;val<=1.0;val += 0.01){
        zmienna::zmien_zmienna("x",val);
        zmienna::zmien_zmienna("y", val);
        cout << w1->oblicz() << endl;
        cout << w2->oblicz() << endl;
        cout << w3->oblicz() << endl;
        cout << w4->oblicz() << endl;
        cout << w5->oblicz() << endl;
        putchar('\n');
    }
    return 0;
}
#include "Header.hpp"
using namespace std;
void printodc(odcinek odc1){
    cout << odc1.getPoczatek().getX() << " " << odc1.getPoczatek().getY() << " "  << odc1.getKoniec().getX() << " " << odc1.getKoniec().getY() << endl;
}
int main(){
    //Punkty
    punkt A = punkt(1,1);
    punkt B = punkt(7,13);
    wektor W = wektor(2,2);
    A.przesun(W);
    cout << A.getY() << " " << A.getX() << endl;
    B.rotate(180, A);
    cout << B.getY() << " " << B.getX() << endl;
    punkt C = punkt(-3, 12);
    A.symPoint(C);
    cout << A.getY() << " " << A.getX() << endl;
    cout << odleglosc(A,C) << endl;
    B.symX(5);
    cout << B.getY() << " " << B.getX() << endl;
    B.symProsta(prosta(3,4));
    cout << B.getY() << " " << B.getX() << endl;
    B.symAsymptotaPionowa(3);
    cout << B.getY() << " " << B.getX() << endl;
    //Odcinki
    odcinek odc1 = odcinek(punkt(1,2), punkt(3,4));
    odcinek odc2 = odcinek(punkt(2,2),punkt(4,4));
    cout << odc1.wspA() << endl;
    cout << odc2.wspA() << endl;
    printodc(odc1);
    odc1.przesun(W);
    printodc(odc1);
    odc1.symProsta(prosta(3,4));
    printodc(odc1);
    odc1.rotate(75,B);
    printodc(odc1);
    if(odc1.nalezy(C)) cout << "Nalezy!" << endl;
    odc1.symPoint(C);
    cout << odc1.dlugosc() << endl;
    if(rownolegle(odc1, odc2)){
        cout << "Rownolegle!" << endl;
    }
    if(prostopadle(odc1,odc2)){
        cout << "Prostopadle!" << endl;
    }
    //Trojkaty
    trojkat T1 = trojkat(A, B , C);
    trojkat T2 = trojkat(punkt(2,8), punkt(14, -3), punkt(21, 13));
    cout << T1.pole() << endl;
    cout << T1.obwod() << endl;
    T1.symPoint(A);
    if(T1.nalezy(B)) cout << "Nalezy!" << endl;
    if(rozlaczne(T1,T2)) cout << "Rozlaczne" << endl;
    if(zawieranie(T1, T2)) cout << "Zawieraja sie" << endl;
    //Tutaj już nie testuje reszty przesunięć symetrii i obrotów, zadziałały dla punktów to dla trójkąta też działają
    return 0;
}

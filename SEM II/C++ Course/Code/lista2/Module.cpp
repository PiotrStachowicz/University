#include "Header.hpp"
//PROSTA
prosta::prosta(double da, double db) : a(da) , b(db) {};
//PUNKT
punkt::punkt() : x(0), y(0) {}
punkt::punkt(double x, double y) : x(x), y(y) {}
double punkt::getX() {
    return x;
}
double punkt::getY(){
    return y;
}
void punkt::przesun(wektor W){
    x += W.dx;
    y += W.dy;
}
void punkt::symX(double b){
    y = -y + 2*b;
}
void punkt::symAsymptotaPionowa(double dx){
    x = -x + 2*dx;
}
void punkt::symProsta(prosta P1){
    if(P1.a==0){
        symX(P1.b);
    } else{
        double  a = (1/P1.a)*(-1);
        double b = getY() - a*getY();
        double dx = (b - P1.b)/(P1.a - a);
        double dy = (dx*a + b);
        punkt punkt1 = punkt(dx,dy);
        rotate(180,punkt1);
    }
}
void punkt::symPoint(punkt p){
    rotate(180,p);
}
void punkt::rotate(double angle, punkt p) {
    double rad = angle * M_PI / 180.0;
    double dx = p.getX()+ (x-p.getX()) * cos(rad) - (y-p.getY()) * sin(rad);
    double dy = p.getY()+ (x-p.getX()) * sin(rad) + (y-p.getY()) * cos(rad);
    x = dx;
    y = dy;
}
//GLOBALNE
double odleglosc(punkt A, punkt B){
    double dx = A.getX()-B.getX();
    double dy = A.getY()-B.getY();
    return sqrt(dx*dx + dy*dy);
}
//ODCINEK
odcinek::odcinek() : poczatek(punkt()), koniec(punkt()) {}
odcinek::odcinek(punkt A, punkt B) : poczatek(A), koniec(B) {
    if(A.getX()==B.getX() && A.getY() == B.getY()){
        throw std::invalid_argument("nie można utworzyć odcinka o długości 0");
    }
}
punkt odcinek::getPoczatek(){
    return poczatek;
}
punkt odcinek::getKoniec(){
    return koniec;
}
void odcinek::przesun(wektor W){
    poczatek.przesun(W);
    koniec.przesun(W);
}
void odcinek::symX(double b)
{
    poczatek.symX(b);
    koniec.symX(b);
}
void odcinek::symAsymptotaPionowa(double dx){
    poczatek.symAsymptotaPionowa(dx);
    koniec.symAsymptotaPionowa(dx);
}
void odcinek::symProsta(prosta P1){
    poczatek.symProsta(P1);
    koniec.symProsta(P1);
}
void odcinek::symPoint(punkt p){
    poczatek.symPoint(p);
    koniec.symPoint(p);
}
void odcinek::rotate(double angle, punkt p) {
    poczatek.rotate(angle, p);
    koniec.rotate(angle, p);
}
double odcinek::dlugosc(){
    return odleglosc(poczatek, koniec);
}
bool odcinek::nalezy(punkt p){
    double odl1 = odleglosc(poczatek,p);
    double odl2 = odleglosc(p,koniec);
    if(odl1+odl2== odleglosc(poczatek,koniec)){
        return true;
    }
    return false;
}
double odcinek::wspA(){
    return (getPoczatek().getY() - getKoniec().getY())/(getKoniec().getX() - getPoczatek().getX());
}
double odcinek::wspB(){
    return getKoniec().getY()-wspA()*getKoniec().getX();
}
//GLOBALNE
bool przecinaja(odcinek A, odcinek B){
    if(rownolegle(A,B)) return false;
    double x1 = (A.wspB()-B.wspB())/(A.wspA()-B.wspA());
    if((A.getPoczatek().getX()<=x1<=A.getKoniec().getX()) || (A.getKoniec().getX() <= x1 <= A.getPoczatek().getX()) || (B.getPoczatek().getX()<=x1<=B.getKoniec().getX()) || (B.getKoniec().getX()<=x1<=B.getPoczatek().getX())) return true;
    return false;
}
bool rownolegle(odcinek A, odcinek B){
    if(A.wspA() == B.wspA()) return true;
    return false;
}
bool wsplin(punkt A, punkt B, punkt C){
    return (odcinek(A,B).nalezy(C) || odcinek(B,C).nalezy(A) || odcinek(A,C).nalezy(B));
}
bool prostopadle(odcinek A, odcinek B){
    if(A.getPoczatek().getX()==A.getKoniec().getX() && B.getPoczatek().getX() == B.getKoniec().getX()) return false;
    if(A.getPoczatek().getX() == A.getKoniec().getX() && B.wspA()==0 || B.getPoczatek().getX() == B.getKoniec().getX() && A.wspA()==0) return true;
    if(A.wspA()*B.wspA()==-1) return true;
    return false;
}
//TRÓJKĄT
trojkat::trojkat() : A(punkt()), B(punkt()), C(punkt()){};
trojkat::trojkat(punkt A, punkt B, punkt C) : A(A), B(B), C(C){
    if(wsplin(A,B,C)){
        throw std::invalid_argument("boki trojkata nie moga byc wspolliniowe");
    }
};
punkt trojkat::getA(){
    return A;
}
punkt trojkat::getB(){
    return B;
}
punkt trojkat::getC(){
    return C;
}
void trojkat::przesun(wektor W){
    A.przesun(W);
    B.przesun(W);
    C.przesun(W);
}
void trojkat::symX(double b){
    A.symX(b);
    B.symX(b);
    C.symX(b);
}
void trojkat::symAsymptotaPionowa(double dx){
    A.symAsymptotaPionowa(dx);
    B.symAsymptotaPionowa(dx);
    C.symAsymptotaPionowa(dx);
}
void trojkat::symProsta(prosta P1) {
    A.symProsta(P1);
    B.symProsta(P1);
    C.symProsta(P1);
}
void trojkat::symPoint(punkt p){
    A.symPoint(p);
    B.symPoint(p);
    C.symPoint(p);
}
void trojkat::rotate(double angle, punkt p){
    A.rotate(angle,p);
    B.rotate(angle,p);
    C.rotate(angle,p);
}
double trojkat::obwod(){
    return odcinek(A,B).dlugosc() + odcinek(B,C).dlugosc() + odcinek(A,C).dlugosc();
}
bool trojkat::nalezy(punkt p){
    if(wsplin(A,B,p) || wsplin(B,C,p) || wsplin(A,C,p)) return true;
    trojkat T1 = trojkat(A,B,p);
    trojkat T2 = trojkat(p,B,C);
    trojkat T3 = trojkat(A,C,p);
    double P1 = T1.pole();
    double P2 = T2.pole();
    double P3 = T3.pole();
    return (P1+P2+P3==pole());
}
double trojkat::pole(){
    double p = obwod()/2;
    return sqrt(p*(p-odcinek(A,B).dlugosc())*(p-odcinek(B,C).dlugosc())*(p-odcinek(A,C).dlugosc()));
}
//GLOBALNE
bool rozlaczne(trojkat T1, trojkat T2){
    odcinek O1 = odcinek(T1.getA(),T1.getB());
    odcinek O2 = odcinek(T1.getB(),T1.getC());
    odcinek O3 = odcinek(T1.getA(), T1.getC());
    odcinek O4 = odcinek(T2.getA(), T2.getB());
    odcinek O5 = odcinek(T2.getB(), T2.getC());
    odcinek O6 = odcinek(T2.getA(), T2.getC());
    return !(przecinaja(O1,O6) || przecinaja(O1,O4) || przecinaja(O1,O5) || przecinaja(O2,O5) || przecinaja(O2, O6) ||
            przecinaja(O2, O4) || przecinaja(O3, O5) || przecinaja(O3, O6) || przecinaja(O3, O4));
}
bool zawieranie(trojkat T1, trojkat T2){
    return (T1.nalezy(T2.getA()) && T1.nalezy(T2.getB()) && T1.nalezy(T2.getC())) || (T2.nalezy(T1.getA()) && T2.nalezy(T1.getB()) && T2.nalezy(T1.getC()));
}
wektor::wektor(double ddx, double ddy) : dx(ddx), dy(ddy) {}
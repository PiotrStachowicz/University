//Piotr Stachowicz
//Lista 2
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <math.h>
#include <stdexcept>
#ifndef UNTITLED_HEADER_H
#define UNTITLED_HEADER_H
class wektor{
public:
    const double dx;
    const double dy;
    wektor(double ddx, double ddy);
};
class prosta{
public:
    double a;
    double b;
    prosta(double da, double db);
};
class punkt{
private:
    double x;
    double y;
public:
    punkt();
    punkt(double x, double y);
    double getX();
    double getY();
    void przesun(wektor W);
    void symX(double b);
    void symAsymptotaPionowa(double dx);
    void symProsta(prosta P1);
    void symPoint(punkt p);
    void rotate(double angle, punkt p);
};
double odleglosc(punkt A, punkt B);
class odcinek{
private:
    punkt poczatek;
    punkt koniec;
public:
    odcinek();
    odcinek(punkt A, punkt B);
    punkt getPoczatek();
    punkt getKoniec();
    void przesun(wektor W);
    void symX(double b);
    void symProsta(prosta P1);
    void symAsymptotaPionowa(double dx);
    void symPoint(punkt p);
    void rotate(double angle, punkt p);
    double dlugosc();
    bool nalezy(punkt p);
    double wspA();
    double wspB();
};
bool rownolegle(odcinek A, odcinek B);
bool prostopadle(odcinek A, odcinek B);
bool przecinaja(odcinek A, odcinek B);
class trojkat{
private:
    punkt A;
    punkt B;
    punkt C;
public:
    trojkat();
    trojkat(punkt A, punkt B, punkt C);
    punkt getA();
    punkt getB();
    punkt getC();
    void przesun(wektor W);
    void symX(double b);
    void symProsta(prosta P1);
    void symAsymptotaPionowa(double dx);
    void symPoint(punkt p);
    void rotate(double angle, punkt p);
    double obwod();
    bool nalezy(punkt p);
    double pole();
};
bool rozlaczne(trojkat T1, trojkat T2);
bool zawieranie(trojkat T1, trojkat T2);
#endif //UNTITLED_HEADER_H
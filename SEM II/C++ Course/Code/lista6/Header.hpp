// Piotr Stachowicz Lista 6
#ifndef UNTITLED_HEADEREK_HPP
#define UNTITLED_HEADEREK_HPP
#include <iostream>
#include <string>
#include <utility>
#include <math.h>
#include <vector>
#include <stdexcept>
#include <cctype>
using namespace std;
typedef double (*fptr)(double);
typedef double (*fptr2)(double, double);
// "Abstrakcyjna" klasa
class wyrazenie{
public:
    virtual double oblicz() = 0;
    virtual string zapis() = 0;
    virtual int priority() = 0;
    wyrazenie() = default;
    wyrazenie(const wyrazenie &wyrazenie1) = delete;
    wyrazenie(wyrazenie &&wyrazenie2) = delete;
};
class operator1arg : public wyrazenie{
protected:
    string nazwa;
    wyrazenie *Wyrazenie;
    fptr funkcja1;
    int prio;
public:
    int priority() override;
    operator1arg(wyrazenie *wyrazenie, fptr f, int priority, string nazwa1);
    double oblicz() override;
    string zapis() override;
    ~operator1arg();
};
// Funckje 2-anre
class operator2arg : public operator1arg{
protected:
    wyrazenie *leweWyrazenie;
    fptr2 funkcja;
public:
    operator2arg(wyrazenie *lewo, wyrazenie *prawo, fptr2 f, int priority, string nazwa1);
    double oblicz() override;
    string zapis() override;
    ~operator2arg();
};

class dodaj : public operator2arg{
public:
    static double add(double x, double y);
    dodaj(wyrazenie *lewo, wyrazenie *prawo);
};

class odejmij : public operator2arg{
public:
    static double sub(double x, double y);
    odejmij(wyrazenie *lewo, wyrazenie *prawo);
};

class mnoz : public operator2arg{
public:
    mnoz(wyrazenie *lewo, wyrazenie *prawo);
    static double times(double x, double y);
};

class dziel : public operator2arg{
public:
    dziel(wyrazenie *lewo, wyrazenie *prawo);
    static double divide(double x, double y);
};

class logarytm : public operator2arg{
public:
    logarytm(wyrazenie *lewo, wyrazenie *prawo);
    static double log(double x, double y);
};

class modulo : public operator2arg{
public:
    modulo(wyrazenie *lewo, wyrazenie *prawo);
    static double mod(double x, double y);
};

class potega : public operator2arg{
public:
    potega(wyrazenie *lewo, wyrazenie *prawo);
    string zapis() override;
};
// Funkcje 1-arne

class sin_fun : public operator1arg{
public:
    sin_fun(wyrazenie *wyrazenie);
};

class cos_fun : public operator1arg{
public:
    cos_fun(wyrazenie *wyrazenie);
};

class exp_fun : public operator1arg{
public:
    exp_fun(wyrazenie *wyrazenie);
};

class ln : public operator1arg{
public:
    ln(wyrazenie *wyrazenie);
};

class bezwzgl : public operator1arg{
public:
    bezwzgl(wyrazenie *wyrazenie);
};

class przeciw : public operator1arg{
public:
    przeciw(wyrazenie *wyrazenie);
    static double prz(double x);
};

class odwrot : public operator1arg{
public:
    odwrot(wyrazenie *wyrazenie);
    static double odw(double x);
};
// Liczba
class liczba : public wyrazenie{
protected:
    double wartosc;
    int prio = 10;
public:
    int priority() override;
    liczba(double val);
    double oblicz() override;
    string zapis() override;
};
// Stałe
class stala : public wyrazenie{
protected:
    double wartosc;
    string nazwa;
public:
    stala(double val, string name1);
    int priority() override;
    double oblicz() override;
    string zapis() override;
};

class pi final : public stala{
public:
    pi();
};

class e final : public stala{
public:
    e();
};

class fi final : public stala{
public:
    fi();
};
// Zmienna
class zmienna : public wyrazenie{
private:
    static vector<pair<string, double>> hash;
protected:
    string nazwaZmiennej;
    int prio = 10;
public:
    int priority() override;
    zmienna(string nazwa);
    static void usun_zmienna(string &nazwa);
    static void zmien_zmienna(string nazwa, double wartosc);
    static void dodaj_zmienna(string nazwa, double wartosc);
    double oblicz() override;
    string zapis() override;
};
#endif //UNTITLED_HEADEREK_HPP
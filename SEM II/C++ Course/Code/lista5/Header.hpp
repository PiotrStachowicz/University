//Piotr Stachowicz
//Lista 5
#ifndef UNTITLED_HEADEREK_HPP
#define UNTITLED_HEADER_HPP
#include <iostream>
#include <string>
#include <utility>
#include <math.h>
#include <stdexcept>
#include <cctype>
using namespace std;
class kolor{
protected:
    int redValue; // 0-255
    int greenValue; // 0-255
    int blueValue; // 0-255
public:
    kolor();
    kolor(int r, int g, int b);
    int getr() const;
    int getg() const;
    int getb() const;
    void setr(int r);
    void setg(int g);
    void setb(int b);
    void lighten(int amount);
    void darken(int amount);
    kolor mix(kolor a, kolor b);
};
class kolortransparenty : virtual public kolor{
protected:
    int alfa; // 0-255
public:
    kolortransparenty();
    kolortransparenty(int alfa1, int r, int g, int b);
    int getalfa();
    void setalfa(int alfa1);
};
class kolornazwy : virtual public kolor{
protected:
    string nazwa;
public:
    kolornazwy();
    kolornazwy(string string1, int r,int g,int b);
    string getname();
    void setname(string name);
};
class kolornt : public kolornazwy, public kolortransparenty{
public:
    kolornt();
    kolornt(int r, int g, int b, int alfa, const string& string1);
};
#endif //UNTITLED_HEADEREK_HPP

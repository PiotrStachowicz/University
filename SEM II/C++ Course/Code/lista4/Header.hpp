//Piotr Stachowicz
//Lista 4
#ifndef UNTITLED_HEADER_HPP
#define UNTITLED_HEADER_HPP
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <math.h>
#include <stdexcept>
using namespace std;
class tab_bit
{
    typedef uint64_t slowo;
    static const int rozmiarSlowa = sizeof(slowo)*8;
    class ref
    {
        friend tab_bit;
        tab_bit& tb;
        int indeks;
    public:
        ref(tab_bit& tb, int indeks) : tb(tb), indeks(indeks) {}
        ref& operator=(bool b){
            tb.pisz(indeks,b);
            return *this;
        }
        operator bool() const{
            return tb.czytaj(indeks);
        }
        ref& operator=(const ref& rr){
            tb.pisz(indeks,(bool) rr);
            return *this;
        }
    };
public:
    int dl;
    slowo *tab;
public:
    explicit tab_bit (int rozm);
    explicit tab_bit (slowo tb);
    tab_bit (const tab_bit &tb);
    tab_bit (tab_bit &&tb);
    tab_bit(initializer_list<bool> il);
    tab_bit& operator=(const tab_bit &tb);
    tab_bit& operator=(tab_bit &&tb);
    ~tab_bit ();
public:
    bool czytaj (int i) const;
    bool pisz (int i, bool b);
public:
    bool operator[] (int i) const;
    ref operator[] (int i);
    inline int rozmiar () const;
public:
    friend tab_bit operator!(const tab_bit& a);
    friend tab_bit operator^(const tab_bit& a, const tab_bit &b);
    friend tab_bit operator|(const tab_bit& a, const tab_bit &b);
    friend tab_bit operator&(const tab_bit& a, const tab_bit &b);
    tab_bit& operator|=(const tab_bit& tb);
    tab_bit& operator&=(const tab_bit& tb);
    tab_bit& operator^=(const tab_bit& tb);
public:
    friend istream & operator >> (istream &we, tab_bit &tb);
    friend ostream & operator << (ostream &wy, const tab_bit &tb);
};
#endif //UNTITLED_HEADER_HPP
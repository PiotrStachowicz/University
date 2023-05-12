#include "Header.hpp"
tab_bit::tab_bit (int rozm){
    tab = new slowo[(rozm + rozmiarSlowa)/rozmiarSlowa];
    dl = rozm;
    for(int i = 0; i<((rozm + rozmiarSlowa)/rozmiarSlowa);i++){
        tab[i] = 0;
    }
}
tab_bit::tab_bit (slowo tb){
    tab = new slowo[1];
    tab[0] = tb;
    dl = rozmiarSlowa;
}
tab_bit::tab_bit (const tab_bit &tb) : tab(new slowo[(tb.dl % rozmiarSlowa)+1]) , dl(tb.dl){
    memcpy(tab,tb.tab,tb.dl);
}
tab_bit::tab_bit (tab_bit &&tb) : tab(nullptr), dl(0) {
    swap(tab,tb.tab);
    swap(dl,tb.dl);
}
tab_bit& tab_bit::operator=(const tab_bit &tb){
    if(this==&tb) return *this;
    dl = tb.dl;
    memcpy(tab,tb.tab,dl);
    return *this;
}
tab_bit& tab_bit::operator=(tab_bit &&tb){
    if(this==&tb) return *this;
    swap(dl,tb.dl);
    swap(tab,tb.tab);
    return *this;
}
tab_bit::~tab_bit() {
    delete[] tab;
}
bool tab_bit::czytaj(int i) const
{
    if (i < 0 || i >= dl) throw out_of_range("zly indeks");
    int indeks = i / rozmiarSlowa;
    int przesuniecie = i % rozmiarSlowa;
    return (tab[indeks] >> przesuniecie) & 1ULL;
}
bool tab_bit::pisz(int i, bool b)
{
    if (i < 0 || i >= dl) throw out_of_range("zly indeks");
    int indeks = i / rozmiarSlowa;
    int przesuniecie = i % rozmiarSlowa;
    if (b){
        tab[indeks] |= (1ULL << przesuniecie);
    }
    else{
        tab[indeks] &= ~(1ULL << przesuniecie);
    }
    return b;
}
inline int tab_bit::rozmiar() const{
    return dl;
}
bool tab_bit::operator[] (int i) const {
    if (i < 0 || i >= dl) throw out_of_range("zly indeks");
    return czytaj(i);
}
ostream& operator<<(ostream &wy, const tab_bit &tb){
    wy << "[";
    for(int i = 0; i<tb.rozmiar();i++){
        wy << tb[i];
    }
    wy << "]";
    return wy;
}
istream& operator>>(istream &we, tab_bit &tb) {
    string bitString;
    we >> bitString;
    int len = bitString.length();
    for (int i = 0; i < len; i++){
        if (bitString[i] == '0'){
            tb.pisz(i, false);
        }
        else if (bitString[i] == '1'){
            tb.pisz(i, true);
        }
        else{
            throw invalid_argument("Bit moze byc tylko 0 lub 1");
        }
    }
    return we;
}
tab_bit& tab_bit::operator|=(const tab_bit& tb){
    if(this==&tb) return *this;
    if(tb.dl!=dl) throw out_of_range("roznej wielkosci tablice");
    int max_idx =  (tb.dl + tb.rozmiarSlowa)/tb.rozmiarSlowa;
    for(int i = 0; i < max_idx; i++){
        tab[i] |= tb.tab[i];
    }
    return *this;
}
tab_bit& tab_bit::operator&=(const tab_bit& tb){
    if(this==&tb) return *this;
    if(tb.dl!=dl) throw out_of_range("roznej wielkosci tablice");
    int max_idx =  (tb.dl + tb.rozmiarSlowa)/tb.rozmiarSlowa;
    for(int i = 0; i < max_idx; i++){
        tab[i] &= tb.tab[i];
    }
    return *this;
}
tab_bit& tab_bit::operator^=(const tab_bit& tb){
    if(this==&tb) return *this;
    if(tb.dl!=dl) throw out_of_range("roznej wielkosci tablice");
    int max_idx =  (tb.dl + tb.rozmiarSlowa)/tb.rozmiarSlowa;
    for(int i = 0; i < max_idx; i++){
        tab[i] ^= tb.tab[i];
    }
    return *this;
}
tab_bit::ref tab_bit::operator[](int i){
    return ref(*this,i);
}
tab_bit operator!(const tab_bit &a) {
    int max_idx =  (a.dl + a.rozmiarSlowa)/a.rozmiarSlowa;
    for(int i = 0;i<max_idx;i++){
        a.tab[i] = ~a.tab[i];
    }
    return a;
}
tab_bit::tab_bit(initializer_list<bool> il) : tab_bit(il.size()){
    int idx = 0;
    for(bool b : il){
        pisz(idx,b);
        idx++;
    }
}
tab_bit operator^(const tab_bit& a, const tab_bit &b){
     if(a.dl != b.dl) throw out_of_range("roznej wielkosci tablice");
     for(int i = 0; i<a.dl;i++){
         a.tab[i] ^= b.tab[i];
     }
     return a;
}
tab_bit operator|(const tab_bit& a, const tab_bit &b){
    if(a.dl != b.dl) throw out_of_range("roznej wielkosci tablice");
    for(int i = 0; i<a.dl;i++){
        a.tab[i] |= b.tab[i];
    }
    return a;
}
tab_bit operator&(const tab_bit& a, const tab_bit &b){
    if(a.dl != b.dl) throw out_of_range("roznej wielkosci tablice");
    for(int i = 0; i<a.dl;i++){
        a.tab[i] &= b.tab[i];
    }
    return a;
}
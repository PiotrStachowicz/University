#include "Header.hpp"
#include "HeaderPiksel.hpp"
kolor::kolor(){
    kolor(0,0,0);
}

kolor::kolor(int r, int g, int b){
    if (r < 0 || g < 0 || b < 0 || b > 255 || g > 255 || r > 255) {
        throw new logic_error("Kolor jest z przedziału 0-255!");
    }
    redValue = r;
    greenValue = g;
    blueValue = b;
}

int kolor::getr() const{
    return redValue;
}

int kolor::getg() const{
    return greenValue;
}

int kolor::getb() const{
    return blueValue;
}

void kolor::setr(int r){
    if(r>255 || r< 0) throw new logic_error("Kolor jest z przedziału 0-255!");
    redValue = r;
}

void kolor::setg(int g){
    if(g>255 || g< 0) throw new logic_error("Kolor jest z przedziału 0-255!");
    greenValue = g;
}

void kolor::setb(int b){
    if(b>255 || b< 0) throw new logic_error("Kolor jest z przedziału 0-255!");
    blueValue = b;
}

void kolor::lighten(int amount){
    redValue = min(255, redValue+amount);
    greenValue = min(255, greenValue+amount);
    blueValue = min(255, blueValue+amount);
}

void kolor::darken(int amount){
    redValue = max(0, redValue-amount);
    greenValue = max(0, greenValue-amount);
    blueValue = max(0, blueValue-amount);
}

kolor kolor::mix(kolor a, kolor b){
    return kolor((a.redValue+b.redValue)/2,(a.greenValue+b.greenValue)/2,(a.blueValue+b.blueValue)/2);
}

kolortransparenty::kolortransparenty() {
    kolortransparenty(0, 0 , 0 ,0);
}

kolortransparenty::kolortransparenty(int alfa1, int r, int g, int b) : kolor(r,g,b){
    if(alfa1 > 255 || alfa1 < 0) throw new logic_error("Kolor jest z przedziału 0-255!");
    alfa = alfa1;
}

int kolortransparenty::getalfa() {
    return alfa;
}

void kolortransparenty::setalfa(int alfa1) {
    if(alfa1 > 255 || alfa1 < 0) throw new logic_error("Kolor jest z przedziału 0-255!");
    alfa = alfa1;
}

const string piksel::standard = "HDTV1080";

kolornazwy::kolornazwy(){
    kolornazwy("",0,0,0);
}

kolornazwy::kolornazwy(string string1, int r, int g, int b) : kolor(r,g,b){
    for(int i = 0;i<string1.length();i++){
        if(string1[i]<'a' || string1[i]>'z'){
            throw new logic_error("zle literki");
        }
    }
    nazwa = string1;
}

string kolornazwy::getname(){
    return nazwa;
}

void kolornazwy::setname(string name) {
    for(int i = 0;i<name.length();i++){
        if(name[i]<'a' || name[i]>'z'){
            throw new logic_error("zle literki");
        }
    }
    nazwa = name;
}

kolornt::kolornt() : kolor(), kolortransparenty(), kolornazwy(){};

kolornt::kolornt(int r, int g, int b, int alfa, const string& string1) : kolor(r,g,b), kolortransparenty(alfa, r, g, b), kolornazwy(string1, r , g ,b){};

piksel::piksel() {
    piksel(0,0);
}

piksel::piksel(int xp, int yp) {
    if(xp<0 || yp<0 || xp>1920 || yp>1080) throw new out_of_range("Piksel poza ekranem!");
    x = xp;
    y = yp;
}

int piksel::distanceTop() {
    return y;
}

int piksel::distanceBottom() {
    return 1080-y;
}

int piksel::distanceLeft() {
    return x;
}

int piksel::distanceRight() {
    return 1920-x;
}

int piksel::getx() {
    return x;
}

int piksel::gety() {
    return y;
}

void piksel::set(int xp, int yp) {
    if(xp<0 || yp<0 || xp>1920 || yp>1080) throw new out_of_range("Piksel poza ekranem!");
    x = xp;
    y = yp;
}

pikselkolorowy::pikselkolorowy(int x, int y, const kolortransparenty &kolor) : piksel(x,y){
    set(x,y);
    setKolor(kolor);
}

void pikselkolorowy::setKolor(const kolortransparenty &kolor) {
    kolorpix = kolor;
}

kolortransparenty pikselkolorowy::getKolor() {
    return kolorpix;
}

void pikselkolorowy::przesun(int dx, int dy) {
    if(dx+getx()>1920 || dx+getx()<0 || dy+gety()>1080 || dy+gety()<0) throw new out_of_range("Piksel wyszedl poza ekran!");
    set(dx+getx(),dy+gety());
}

int odleglosc(piksel &p, piksel &q) {
    int dx = p.getx() - q.getx();
    int dy = p.gety() - q.gety();
    return round(sqrt(dx*dx + dy*dy));
}

int odleglosc(piksel *p, piksel *q) {
    return odleglosc(*p,*q);
}

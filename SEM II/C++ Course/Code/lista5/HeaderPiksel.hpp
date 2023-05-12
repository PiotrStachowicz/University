#include "Header.hpp"

#ifndef UNTITLED_HEADERPIKSEL_H
#define UNTITLED_HEADERPIKSEL_H
class piksel{
protected:
    int x;
    int y;
    const static string standard; // 1080p
    const static int max_x = 1920;
    const static int max_y = 1080;
public:
    piksel();
    piksel(int xp, int yp);
    int getx();
    int gety();
    void set(int xp, int yp);
    int distanceTop();
    int distanceBottom();
    int distanceLeft();
    int distanceRight();
};
class pikselkolorowy : public piksel{
protected:
    kolortransparenty kolorpix;
public:
    pikselkolorowy(int x, int y, const kolortransparenty &kolor);
    void setKolor(const kolortransparenty &kolor);
    kolortransparenty getKolor();
    void przesun(int dx, int dy);
};
int odleglosc(piksel &p, piksel &q);
int odleglosc(piksel *p, piksel *q);
#endif //UNTITLED_HEADERPIKSEL_H

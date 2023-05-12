#include "Header.hpp"
#include "HeaderPiksel.hpp"
int main(void){
    kolor kolor1 = kolor(200,34,22);
    kolor1.setr(199);
    cout << kolor1.getr() << endl;
    kolor1.lighten(1);
    cout << kolor1.getr() << endl;
    kolor kolor2 = kolor(152,31,94);
    kolor2 = kolor2.mix(kolor1,kolor2);
    kolornt kolornt1 = kolornt(55,55,55,22,"dziwny kolor");
    cout << kolornt1.getname() << endl;
    cout << kolornt1.getalfa() << endl;
    kolornt1.setname("normalny kolor");
    cout << kolornt1.getname() << endl;
    piksel pix1 = piksel(2, 3);
    pix1.set(1920,0);
    cout << pix1.distanceLeft() << endl;
    pikselkolorowy pikselkolorowy1 = pikselkolorowy(12 , 12, kolortransparenty(22, kolor2.getr(), kolor2.getg(), kolor2.getb()));
    pikselkolorowy1.przesun(12 ,12);
    piksel pix2 = piksel(1920,1080);
    cout << odleglosc(&pix1,&pix2) << endl;
    pix1.set(0,0);
    pix2.set(4,3);
    cout << odleglosc(pix1,pix2) << endl;
    return 0;
}

#include "Header.hpp"
// Funkcje 2-arne
operator2arg::operator2arg(wyrazenie *lewo, wyrazenie *prawo, fptr2 f, int priority, string nazwa1) :
        operator1arg(prawo,nullptr,priority,nazwa1) , leweWyrazenie(lewo), funkcja(f) {}

double operator2arg::oblicz() {
    if (isnan(leweWyrazenie->oblicz()) || isnan(Wyrazenie->oblicz())) {
        throw new logic_error("nan");
    }
    double x = funkcja(leweWyrazenie->oblicz(), Wyrazenie->oblicz());
    if (isnan(x)) {
        throw new logic_error("nan");
    }
    return x;
}

string operator2arg::zapis() {
    string lewo = leweWyrazenie->zapis();
    string prawo = Wyrazenie->zapis();
    if(leweWyrazenie->priority()<prio){lewo = "(" + lewo + ")";}
    if(Wyrazenie->priority()<=prio){prawo = "(" + prawo + ")";}
    return lewo + nazwa + prawo;
}

operator2arg::~operator2arg() {
    delete leweWyrazenie;
}

dodaj::dodaj(wyrazenie *lewo, wyrazenie *prawo) : operator2arg(lewo,prawo,add,3,"+") {}

double dodaj::add(double x, double y) { return x + y; };

odejmij::odejmij(wyrazenie *lewo, wyrazenie *prawo) : operator2arg(lewo,prawo,sub,3,"-") {}

double odejmij::sub(double x, double y) { return x - y; };

mnoz::mnoz(wyrazenie *lewo, wyrazenie *prawo) : operator2arg(lewo,prawo,times,5,"*"){}

double mnoz::times(double x, double y) { return x * y; };

dziel::dziel(wyrazenie *lewo, wyrazenie *prawo) : operator2arg(lewo,prawo,divide,5,"/"){}

double dziel::divide(double x, double y) { return x / y; };

logarytm::logarytm(wyrazenie *lewo, wyrazenie *prawo) : operator2arg(lewo,prawo,log,6,"ln") {}

double logarytm::log(double x, double y) {
    return (logb(x)/logb(y));
}

modulo::modulo(wyrazenie *lewo, wyrazenie *prawo) : operator2arg(lewo,prawo,mod,6,"%") {}

double modulo::mod(double x, double y) {
    while (x-y>0){ x-= y;};
    return x;
}

potega::potega(wyrazenie *lewo, wyrazenie *prawo) : operator2arg(lewo,prawo,std::pow,6,"^") {}

string potega::zapis() {
    string lewo = leweWyrazenie->zapis();
    string prawo = Wyrazenie->zapis();
    if(leweWyrazenie->priority()<=prio){lewo = "(" + lewo + ")";}
    if(Wyrazenie->priority()<prio){prawo = "(" + prawo + ")";}
    return lewo + nazwa + prawo;
}
// Funkcje 1-arne
operator1arg::operator1arg(wyrazenie *wyrazenie, fptr f, int priority, string nazwa1) :
Wyrazenie(wyrazenie), funkcja1(f), prio(priority), nazwa(nazwa1){}

int operator1arg::priority() {return prio;}

double operator1arg::oblicz() {
    if(isnan(Wyrazenie->oblicz())){
        throw new logic_error("nan");
    }
    return funkcja1(Wyrazenie->oblicz());
}

string operator1arg::zapis() {
    return  "(" + nazwa + Wyrazenie->zapis() + ")";
}

operator1arg::~operator1arg() {
    delete Wyrazenie;
}


sin_fun::sin_fun(wyrazenie *wyrazenie) : operator1arg(wyrazenie,std::sin, 6,"sin") {}

cos_fun::cos_fun(wyrazenie *wyrazenie) : operator1arg(wyrazenie,std::cos,6,"cos") {}

exp_fun::exp_fun(wyrazenie *wyrazenie) : operator1arg(wyrazenie,std::exp,6,"exp") {}

ln::ln(wyrazenie *wyrazenie) : operator1arg(wyrazenie,std::log,6,"ln") {}

bezwzgl::bezwzgl(wyrazenie *wyrazenie) : operator1arg(wyrazenie,std::abs,6,"abs") {}

przeciw::przeciw(wyrazenie *wyrazenie) : operator1arg(wyrazenie,prz,5,"-") {}

double przeciw::prz(double x){
    return -x;
}

odwrot::odwrot(wyrazenie *wyrazenie) : operator1arg(wyrazenie,odw,5,"1/") {}

double odwrot::odw(double x){
    return 1.0/x;
}

liczba::liczba(double val) : wartosc(val){}

double liczba::oblicz() {
    return wartosc;
}

string liczba::zapis() {
    return to_string(wartosc);
}

int liczba::priority() {
    return prio;
}

stala::stala(double val, string name1) : wartosc(val), nazwa(name1){}

int stala::priority() {
    return 10;
}

double stala::oblicz() {
    return wartosc;
}

string stala::zapis() {
    return nazwa;
}

pi::pi() : stala(numbers::pi, "pi"){}

zmienna::zmienna(string nazwa) : nazwaZmiennej(nazwa) {}

void zmienna::usun_zmienna(string &nazwa) {
    for(auto item = hash.begin(); item<hash.end(); item++){
        if(item->first == nazwa){
            hash.erase(item);
            break;
        }
    }
}

void zmienna::zmien_zmienna(string nazwa, double wartosc) {
    for(auto item = hash.begin(); item<hash.end(); item++){
        if(item->first == nazwa){
            item->second = wartosc;
            break;
        }
    }
}

void zmienna::dodaj_zmienna(string nazwa, double wartosc) {
    hash.push_back(pair(nazwa,wartosc));
}

double zmienna::oblicz() {
    for(auto item = hash.begin(); item<hash.end(); item++){
        if(item->first == nazwaZmiennej){
            return item->second;
        }
    }
    throw new logic_error("Nie znaleziono zmiennej" + nazwaZmiennej);
}

string zmienna::zapis() {
    return nazwaZmiennej;
}

int zmienna::priority() {
    return prio;
}

vector<pair<string, double>> zmienna::hash;

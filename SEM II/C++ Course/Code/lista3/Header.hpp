//Piotr Stachowicz
//Lista 3
#ifndef UNTITLED_HEADER_HPP
#define UNTITLED_HEADER_HPP
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <math.h>
#include <stdexcept>
using namespace std;
class liczba{
private:
    double *history;
    static const int max_hist_length = 3;
    int list_size;
    int last_idx;
    int first_idx;
    double current;
    bool empty;
public:
    liczba();
    liczba(double current);
    liczba(const liczba& l);
    liczba(liczba&& l);
    liczba& operator=(const liczba& other);
    liczba& operator=(liczba&& other);
    ~liczba();
    double getcurrent();
    void goback();
    void add(double x);
    void print();
};
#endif //UNTITLED_HEADER_HPP

#include "Header.hpp"
liczba::liczba() : liczba(0.0) {}
liczba::liczba(double current) : history(new double [max_hist_length]),
empty(false) ,last_idx(0), current(current), list_size(1), first_idx(1) {
    history[0] = current;
}
liczba::liczba(const liczba& l) : liczba(l.current) {}
liczba::liczba(liczba&& l) : history(nullptr), current(0), empty(false), list_size(0), last_idx(0), first_idx(1){
    swap(history,l.history);
    swap(current,l.current);
    swap(list_size, l.list_size);
    swap(last_idx, l.last_idx);
    swap(first_idx, l.first_idx);
    swap(empty,l.empty);
}
liczba& liczba::operator=(const liczba& other){
    if(this==&other) return *this;
    memcpy(history,other.history,sizeof(double)*max_hist_length);
    list_size = other.list_size;
    current = other.current;
    last_idx = other.last_idx;
    first_idx = other.first_idx;
    empty = other.empty;
    return *this;
}
liczba& liczba::operator=(liczba&& other){
    if(this==&other) return *this;
    swap(history, other.history);
    swap(current, other.current);
    swap(list_size, other.list_size);
    swap(last_idx, other.last_idx);
    swap(first_idx, other.first_idx);
    swap(empty,other.empty);
    return *this;
}
liczba::~liczba() {
    delete[] history;
}
double liczba::getcurrent(){
    return current;
}
void liczba::print(){
    for (int i = 0; i < max_hist_length; ++i) {
        cout << history[i] <<"-->";
    }
    cout << endl;
}
void liczba::add(double x){
    empty = false;
    if(list_size == max_hist_length){
        history[last_idx % max_hist_length] = x;
        current = x;
        last_idx++;
        first_idx++;
    }else{
        history[list_size] = x;
        first_idx = list_size;
        current = x;
        last_idx = 0;
        list_size++;
    }
}

void liczba::goback(){
    if(empty){
        throw invalid_argument("Nie mozna wykonac operacji");
    }
    first_idx -= 1;
    current = history[first_idx % max_hist_length];
    if(first_idx % max_hist_length == last_idx % max_hist_length){
        last_idx = 0;
        empty = true;
    }
}
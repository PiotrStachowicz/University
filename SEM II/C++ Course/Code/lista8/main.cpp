#include "header.hpp"
using namespace obliczenia;
int main(void){
    wymierna wymierna1 = wymierna(1,4);
    wymierna wymierna4 = wymierna(1,1);
    std::cout << wymierna1 + wymierna4 << std::endl;
    wymierna wymierna2 = wymierna(3,4);
    wymierna wymierna3 = wymierna(2359348, 99900);
    std::cout << wymierna1 << std::endl;
    std::cout << wymierna2 << std::endl;
    std::cout << wymierna1 / wymierna2 << std::endl;
    std::cout << wymierna1 * wymierna2 << std::endl;
    std::cout << wymierna1 + wymierna2 << std::endl;
    std::cout << wymierna1 - wymierna2 << std::endl;
    std::cout << -wymierna1 << std::endl;
    std::cout << !wymierna1 << std::endl;
    std::cout << wymierna3 << std::endl;
    return 0;
}
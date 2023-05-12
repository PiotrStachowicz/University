#include "ControlHpp.hpp"
#include <cctype>
namespace Control{
    void print(int *b){
        std::cout << " | A | B | C |" << std::endl;
        std::cout << " -------------" << std::endl;
        for(int i = 0;i<9;i++){
            if(i%3==0){
                std::cout << ((i/3)%3)+1 << "|";
            }
            std::string p = " * |";
            if(b[i]==1){
                p = " X |";
            }
            if(b[i]==-1){
                p = " O |";
            }
            std::cout << p;
            if((i+1)%3==0){
                std::cout << std::endl;
            }
        }
        std::cout << " -------------" << std::endl;
    }
    int move(int *b){
        std::string output;
        int y;
        char x;
        std::cout << "Podaj ruch (wzorcowo np. A3):";
        std::cin >> output;
        x = output[0];
        y = output[1]-49;
        return ((x-'A')+(3*y));
    }
}

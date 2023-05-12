#include "AIHpp.hpp"
#include "math.h"
namespace AI{
    int random_move(int *b) {
        while (true){
            int x = rand()%9;
            if(b[x]==0){
                return x;
            }
        }
    }
}
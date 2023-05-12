#include <iostream>
#include <string>
#include <vector>
#include <utility>
// Piotr Stachowicz
using namespace std;
string bin2roman(int x);
const vector<pair<int, string>> rzym = {
        {1000, "M"},{900, "CM"},{500, "D"},{400, "CD"},{100, "C"},{90, "XC"},{50, "L"},{40, "XL"},{10, "X"},{9, "IX"},{5, "V"},{4, "IV"},{1, "I"}
};
int main(int argc, char* argv[]){
    int number;
    for(int i = 1;i < argc;i++){
        try{
            number = stoi(argv[i]);
            if(number < 1 or number > 3999){
                clog << "Liczba musi byc z zakresu [1;3999]!" << endl;
            } else{
                string roman = bin2roman(number);
                cout << roman << endl;
            }
        }catch (exception &err){
            clog << "Zly argument: " << argv[i] << " '" << err.what() << "'" << endl;
        }
    }
    return 0;
}
string bin2roman(int x){
    string y {""};
    int idx = 0;
    while (x>0){
        if(x - rzym[idx].first >= 0){
            x -= rzym[idx].first;
            y += rzym[idx].second;
        } else{
            idx++;
        }
    }
    return y;
}
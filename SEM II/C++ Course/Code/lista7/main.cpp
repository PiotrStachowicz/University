#include "ControlHpp.hpp"
#include "AIHpp.hpp"
#include "StateHpp.hpp"
void game();
int main(void){
    srand(time(0));
    game();
    return 0;
}
void game(){
    State::State state;
    Control::print(state.board);
    while (!state.isFull() and !state.win) {
        while(true){
            int x = Control::move(state.board);
            if (state.board[x] == 0) {
                state.board[x] = 1;
                break;
            }
        }
        Control::print(state.board);
        if (state.checkForWin()) {
            if (state.human == 1) std::cout << "YOU WON!" << std::endl;
            else std::cout << "YOU LOST!" << std::endl;
            break;
        }else if (state.isFull()) {
            std::cout << "DRAW!" << std::endl;
            state.win = true;
        }
        state.human *= -1;
        std::cout << "komputer wykonuje ruch..." << std::endl;
        int y = AI::random_move(state.board);
        state.board[y] = -1;
        if (state.checkForWin()) {
            if (state.human == 1) std::cout << "YOU WON!" << std::endl;
            else std::cout << "YOU LOST!" << std::endl;
            state.win = true;
        }else if (state.isFull()) {
            std::cout << "DRAW!" << std::endl;
            state.win = true;
        }
        state.human *= -1;
        Control::print(state.board);
    }
}
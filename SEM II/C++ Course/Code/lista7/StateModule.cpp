#include "StateHpp.hpp"

namespace State{
    State::State() : board(new int[9]{}), human(1), win(false) {}
    bool State::checkForWin() {
        int currentPlayer = 1;
        if ((board[0] == currentPlayer && board[1] == currentPlayer && board[2] == currentPlayer) ||
            (board[3] == currentPlayer && board[4] == currentPlayer && board[5] == currentPlayer) ||
            (board[6] == currentPlayer && board[7] == currentPlayer && board[8] == currentPlayer) ||
            (board[0] == currentPlayer && board[3] == currentPlayer && board[6] == currentPlayer) ||
            (board[1] == currentPlayer && board[4] == currentPlayer && board[7] == currentPlayer) ||
            (board[2] == currentPlayer && board[5] == currentPlayer && board[8] == currentPlayer) ||
            (board[0] == currentPlayer && board[4] == currentPlayer && board[8] == currentPlayer) ||
            (board[6] == currentPlayer && board[4] == currentPlayer && board[2] == currentPlayer))
        {
            return true;
        }
        currentPlayer = -currentPlayer;
        if ((board[0] == currentPlayer && board[1] == currentPlayer && board[2] == currentPlayer) ||
            (board[3] == currentPlayer && board[4] == currentPlayer && board[5] == currentPlayer) ||
            (board[6] == currentPlayer && board[7] == currentPlayer && board[8] == currentPlayer) ||
            (board[0] == currentPlayer && board[3] == currentPlayer && board[6] == currentPlayer) ||
            (board[1] == currentPlayer && board[4] == currentPlayer && board[7] == currentPlayer) ||
            (board[2] == currentPlayer && board[5] == currentPlayer && board[8] == currentPlayer) ||
            (board[0] == currentPlayer && board[4] == currentPlayer && board[8] == currentPlayer) ||
            (board[6] == currentPlayer && board[4] == currentPlayer && board[2] == currentPlayer))
        {
            return true;
        }
        return false;
    }
    bool State::isFull() {
        for(int i = 0;i<9;i++){
            if(board[i]==0) return false;
        }
        return true;
    }
};
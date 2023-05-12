#ifndef UNIVERSITY_STATEHPP_HPP
#define UNIVERSITY_STATEHPP_HPP
namespace State{
    class State {
    public:
        int *board;
        int human;
        bool win;
        State();
        bool checkForWin();
        bool isFull();
    };
}
#endif //UNIVERSITY_STATEHPP_HPP

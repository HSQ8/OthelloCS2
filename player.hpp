#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side my_side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

    Move* doRandomMove();
    Move* doSimpleHeuristicMove();

    Move* doMiniMax(int depth);
    int doBottomHeuristicMove(Board * _board, Side _side);
    Move* doMiniMaxRecurse(Board* _board, Side _side, int depth);

    void setPlayerBoard(char data[]);

private:
    Board *playerboard;
    Side plyside;
    Side oppSide;
};


#endif

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
    Move* doMiniMax();
    Move* doMiniMaxRecurse();

    //static std::vector<Move>* getMoveList(Board* _board, Side _side);

private:
    Board *playerboard;
    Side side;
    Side oppSide;
};


#endif

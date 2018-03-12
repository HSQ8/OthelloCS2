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
    int doBottomHeuristicMove(Board * _board, Side _side);
    
    Move* doMiniMax(int depth);
    Move* doMiniMaxRecurse(Board* _board, Side _side, int depth);
    Move* doMiniMaxWithHeuristicRecurse(Board* _board, Side _side, int depth, int toplevel);
    Move* doMiniMaxWithHeuristic(int depth);

    Move* doAlphaBetaMax(int depth);
    int doAlphaBetaRecurse(Board* _board, Side _side, int depth, int alpha, int beta);

    void setPlayerBoard(char data[]);

private:
    Board *playerboard;
    Side plyside;
    Side oppSide;
};


#endif

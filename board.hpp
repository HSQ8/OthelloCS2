#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitset>
#include "common.hpp"
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class Board {

private:
    bitset<64> black;
    bitset<64> taken;
    bool debug = false;

    bool occupied(int x, int y);
    bool get(Side side, int x, int y);
    void set(Side side, int x, int y);
    bool onBoard(int x, int y);

public:
    Board();
    ~Board();
    Board *copy();

    bool isDone();
    bool hasMoves(Side side);
    bool checkMove(Move *m, Side side);
    void doMove(Move *m, Side side);
    int count(Side side);
    int countBlack();
    int countWhite();


    // Added Functions
    void setBoard(char data[]); // Sets up board 

    // Finds all moves in current state
    std::vector<Move>* getMoveList(Side _side); 

    // Heuristic to evaluate moves
    int getMoveScoreHeuristic(Move* _move, Side side);

    // Heuristic used for testing Minimax
    int getSimpleMoveScoreHeuristic(Move* _move, Side side);

    // Determines how many blank neighbors are near a cell.
    bool hasBlankNeighbor(int i, int j,Side side, Side other);
};

#endif

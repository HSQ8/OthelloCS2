#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitset>
#include "common.hpp"
#include <iostream>
#include <vector>
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

    void setBoard(char data[]);
    std::vector<Move>* getMoveList(Side _side);
    int getMoveScoreHeuristic(Move* _move, Side side);
    bool hasBlankNeighbor(int i, int j,Side side, Side other);
};

#endif

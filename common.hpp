#ifndef __COMMON_H__
#define __COMMON_H__

enum Side { 
    WHITE, BLACK
};

class Move {
   
public:
    int x, y;
    Move(int x, int y) {
        this->x = x;
        this->y = y;        
    }
    ~Move() {}
/*
    Move* copy(Move& _move){
        Move* newmove = new Move();
        newmove->setX(_move.getX());
        newmove->setY(_move.getY());
        return newmove;
    }
*/
    int getX() { return x; }
    int getY() { return y; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
};

#endif

#include <iostream>

#ifndef __COMMON_H__
#define __COMMON_H__

enum Side { 
    WHITE, BLACK
};

class Move {
   
public:
    double score;
    int ringWeight;
    int x, y;
    int ring;
    bool corner;
    bool debug = false;

    Move(int x, int y, double _s) {
        this->x = x;
        this->y = y;
        this->score = _s;
        //this->ringWeight = getRingMultiplier();
    }
    Move(int x, int y) {
        this->x = x;
        this->y = y;
        this->score = 0.0;
        //this->ringWeight = getRingMultiplier();
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
    int getRingMultiplier(){
        int ringx = (x > 3) ? x-3 : 4 - x;
        int ringy = (y > 3) ? y-3 : 4 - y;

        if(debug){
            std::cerr << "Location: " << x << ' ' << y << std::endl;
            std::cerr << "Move: " << ringx << ' ' << ringy << std::endl;
        }
        if((ringy == 4) && (ringx == 4)){
            corner = true;
            if(debug)
                std::cerr << "*********** Corner ***********" << std::endl;
            return 40;
        }
        else if((ringy == 3) && (ringx == 3)){
            if(debug)
                std::cerr << "Next to Corner" << std::endl;
            return -40;

        }
        else if(((ringy == 3) && (ringx == 4)) || ((ringy == 4) && (ringx == 3))){
            if(debug)
                std::cerr << "Edge of Corner" << std::endl;
            return -30;
        }
        
        ring = (ringx > ringy) ? ringx: ringy;
        switch (ring){
            case 1:
                return 1;        
            case 2:
                return 1;
            case 3:
                return -1;
            case 4:
                return 10;
        }
    
    return 0;

    }

    int getX() { return x; }
    int getY() { return y; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }

    double getScore() { return this->score;}
    void setScore(double _s) { this->score = _s; }

    int getRingWeight() { return this->ringWeight;}

};


#endif

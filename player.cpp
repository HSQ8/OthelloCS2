#include "player.hpp"


/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side my_side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    // Initialize the board and player side.
    playerboard = new Board;
    side = my_side;

    if (side == WHITE)
        oppSide = BLACK;
    else
        oppSide = WHITE;

    // Setting up the board. 

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete playerboard;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    //std::cerr << "Starting the next move... " << std::endl;

    // First we need to update the board.
    playerboard->doMove(opponentsMove, oppSide);

    //return doRandomMove();
    return doSimpleHeuristicMove();
    
}

Move* Player::doRandomMove(){
    if (playerboard->hasMoves(side))
    {
        // We have a possible move and can continue.
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Move move(i, j);
                if (playerboard->checkMove(&move, side)) {
                    auto tempmove = new Move(move.getX(), move.getY());
                    playerboard->doMove(tempmove, side);
                    return tempmove;
                }
            }
        }
    }
    else
    {
        // We need to pass.
    }

    return nullptr;
}

Move* Player::doSimpleHeuristicMove(){
    /*if (debug) {
        std::cerr << "###################### Test 1 ##################" << std::endl;
    }*/

    if (playerboard->hasMoves(side)) {
        auto moveList = playerboard->getMoveList(side);
        //std::cerr << "Test 2" << std::endl;
        int moveScore;
        int bestScore = -1000;
        Move *bestMove = new Move(-1, -1);

        for(int i = 0, j = moveList->size(); i < j; ++i){
            //std::cerr << "Test 3: " << moveList->at(i).getX() << ' ' << moveList->at(i).getY() << std::endl;
            moveScore = playerboard->getMoveScoreHeuristic(&moveList->at(i), side);
            //std::cerr << "        Score: " << moveScore << ' ' << moveList->at(i).getScore() << std::endl;
            if (moveScore > bestScore) {
                bestMove->setX(moveList->at(i).getX());
                bestMove->setY(moveList->at(i).getY());

                /*if (debug) {
                    std::cerr << "NEW BEST MOVE!!!" << std::endl;
                }*/
                bestScore = moveScore;
            }
        }
        
        delete moveList;

        playerboard->doMove(bestMove, side);

        /*if (debug) {
            std::cerr << "Sending the next move... " << bestMove->getX()<< ' ' << bestMove->getY() << std::endl;
        }*/

        return new Move(bestMove->getX(), bestMove->getY());
    }
    else
    {
        // We need to pass.
    }
    return nullptr;

}

Move* doMiniMax(){
    return nullptr;
}

Move* doMiniMaxRecurse(){
    /*
    pseudocode

    if node is leaf or if current depth is 0:
        return numeric value for heuristic score
        set bestscore as -MAXINT

    for all moves in each state of the board,
        take maximum score dominmaxrecurse(a, -minimax, -play) 
    */
    return nullptr;
}


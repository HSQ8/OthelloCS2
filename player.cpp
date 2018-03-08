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
    plyside = my_side;

    if (my_side == WHITE)
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

void Player::setPlayerBoard(char data[]){
    playerboard->setBoard(data);
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

    /*if (msLeft > 100000) {
        return doMiniMax(4);
    }

    else if (msLeft > 50000) {
        return doMiniMax(3);
    }

    else if (msLeft > 25000) {
        return doMiniMax(2);
    }

    else if (msLeft > 12500) {
        return doMiniMax(1);
    }

    else */if (msLeft > 10000) {
        return doSimpleHeuristicMove();
    }

    else if (msLeft >= 0) {
        return doRandomMove();
    }
    else { // Player is not using time
        return doMiniMax(2);
    }
    
}
/**
 * Do Random Move returns a random move to the game that is valid. 
 * It works by searching the game space for a valid move given the side we are on, then
 * it returns the first such valid move that we find.
 * @return a pointer to a move object
 */
Move* Player::doRandomMove(){
    if (playerboard->hasMoves(plyside))
    {
        // We have a possible move and can continue.
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Move move(i, j);
                if (playerboard->checkMove(&move, plyside)) {
                    auto tempmove = new Move(move.getX(), move.getY());
                    playerboard->doMove(tempmove, plyside);
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

/**
 * [Player::doSimpleHeuristicMove Do simple HeristivesMove simply returns the piece advantage that we would gain
 * with a greedy heuristic algorithm. It computes a list of possible moves and gets the most efficient from a set of heuristics
 * that we define in board. then it iterates through all those Moves to find the one with the most efficient short term gain in
 * piece advantage]
 * 
 * The function first gets a list of moves possible 
 * @return [a move pointer to the most optimal move]
 */
Move* Player::doSimpleHeuristicMove(){

    if (playerboard->hasMoves(plyside)) {
        auto moveList = playerboard->getMoveList(plyside);

        int moveScore;
        int bestScore = std::numeric_limits<int>::min();;
        Move *bestMove = new Move(-1, -1);

        for(int i = 0, j = moveList->size(); i < j; ++i){
            Board *tempBoard = playerboard->copy();

            moveScore = tempBoard->getMoveScoreHeuristic(&moveList->at(i), plyside);
            moveScore += tempBoard->getBoardHeuristic(plyside);

            if (moveScore > bestScore) {
                bestMove->setX(moveList->at(i).getX());
                bestMove->setY(moveList->at(i).getY());

                bestScore = moveScore;
            }

            delete tempBoard;
        }
        
        delete moveList;

        playerboard->doMove(bestMove, plyside);

        return new Move(bestMove->getX(), bestMove->getY());
    }

    else
    {
        // We need to pass.
    }
    return nullptr;

}

/**
 * [Player::doMiniMax description]
 * Do minimax is a simple minimax wrapper that performs minimax recursive search. We first generate a list of possible moves and
 * then we recursively search the move tree for each of those moves based on a heuristic we define. Each search tree returns the
 * lowest value of the branch, and we take the branch with the highest lowest value and use the move that corresponds to that branch
 * as the most optimal move that we use to play our next move, this minimizes our loss and places our side into an optimal position.
 * @return [a pointer to a move object]
 */
Move* Player::doMiniMax(int depth){

    if (playerboard->hasMoves(plyside)) {
        auto moveList = playerboard->getMoveList(plyside);

        int moveScore;

        int bestScore = std::numeric_limits<int>::min(); // Negative infinity

        Move *bestMove = new Move(-1, -1);

        for(int i = 0, j = moveList->size(); i < j; i++){
            Board *tempBoard = playerboard->copy();

            tempBoard->doMove(&moveList->at(i), plyside);

            moveScore = doMiniMaxRecurse(tempBoard, oppSide, depth - 1);
            

            if (moveScore > bestScore) {
                bestMove->setX(moveList->at(i).getX());
                bestMove->setY(moveList->at(i).getY());

                bestScore = moveScore;
            }

            delete tempBoard;
        }
        
        delete moveList;

        playerboard->doMove(bestMove, plyside);

        return bestMove;
    }
    else
    {
        // We need to pass.
    }

    return nullptr;
}

/**
 * doMiniMaxRecurse is the actual working function in minimax
 * here, we recursively search for the move with the most negative move score based on a heuristic and then search the 
 * tree of possible moves based on each of those moves and return the lowest possible score. This ensures that we then can minimize our
 * loss in the wrapper function. we return once we exhaust the search tree or we reach our recursion limit.
 * @param  _move  [a move object of the current move being considered]
 * @param  _board [the current board context that the move being considered is in]
 * @param  side   [the side, which playe we are(white/black)]
 * @param  depth  [the depth limit, used to keep track of which level we are in.]
 * @return        [description]
 */
int Player::doMiniMaxRecurse(Board* _board, Side _side, int depth){
    /*
    pseudocode:
    if node is a leaf or if the depth counter is 0,
        simply return the value of the move
    Otherwise, we want to maximize the player's score
    and minimize the opponent score.
    We do this by taking the max score of the player
    or the min score of the opponent.*/
    
    if(depth <= 0 || _board->isDone()){
        if(testingMinimax){
            return _board->getBoardHeuristic(_side);
        }
        else {
            
            if (_side == plyside)
            {
                return _board->getBoardHeuristic(plyside);
            }
            else
            {
                return - _board->getBoardHeuristic(plyside);
            }
            
        }
    }

    // Get all the possible moves 
    auto moveList = _board->getMoveList(_side);

    // If the player must pass,
    if(moveList->size() < 1)
    {
        if(testingMinimax){
            return _board->getBoardHeuristic(_side);
        }
        else {
            std::cerr << "None left Score: " << _board->getBoardHeuristic(_side) <<std::endl;
            return 0;
        }
    }

    if (_side == plyside)
    {
        int bestScore = std::numeric_limits<int>::min(); // Negative Infinity;
        int moveScore;

        // Iterate through the moves
        for(int i = 0, j = moveList->size(); i < j; ++i){
            Board *tempBoard = _board->copy();

            _board->doMove(&moveList->at(i), plyside);

            // Calculate minimax
            moveScore = doMiniMaxRecurse(tempBoard, oppSide, depth - 1);

            // Update bestScore
            bestScore = max(bestScore, moveScore);

            delete tempBoard;
        }

        delete moveList;

        return bestScore;
    }

    else
    {
        int bestScore = std::numeric_limits<int>::max(); // Positive Infinity;
        int moveScore;

        // Iterate through the moves
        for(int i = 0, j = moveList->size(); i < j; ++i){
            Board *tempBoard = _board->copy();

            _board->doMove(&moveList->at(i), oppSide);

            // Calculate minimax
            moveScore = doMiniMaxRecurse(tempBoard, plyside, depth - 1);

            // Update bestScore
            bestScore = min(bestScore, moveScore);

            delete tempBoard;
        }

        delete moveList;

        return bestScore;
    }
}


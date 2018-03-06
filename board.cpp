#include "board.hpp"

/*
 * Make a standard 8x8 othello board and initialize it to the standard setup.
 */
Board::Board() {
    taken.set(3 + 8 * 3);
    taken.set(3 + 8 * 4);
    taken.set(4 + 8 * 3);
    taken.set(4 + 8 * 4);
    black.set(4 + 8 * 3);
    black.set(3 + 8 * 4);
}

/*
 * Destructor for the board.
 */
Board::~Board() {
}

/*
 * Returns a copy of this board.
 */
Board *Board::copy() {
    Board *newBoard = new Board();
    newBoard->black = black;
    newBoard->taken = taken;
    return newBoard;
}

bool Board::occupied(int x, int y) {
    return taken[x + 8*y];
}

bool Board::get(Side side, int x, int y) {
    return occupied(x, y) && (black[x + 8*y] == (side == BLACK));
}

void Board::set(Side side, int x, int y) {
    taken.set(x + 8*y);
    black.set(x + 8*y, side == BLACK);
}

bool Board::onBoard(int x, int y) {
    return(0 <= x && x < 8 && 0 <= y && y < 8);
}


/*
 * Returns true if the game is finished; false otherwise. The game is finished
 * if neither side has a legal move.
 */
bool Board::isDone() {
    if(debug)
        std::cerr << "Check" << std::endl;
    if (!(hasMoves(BLACK) || hasMoves(WHITE)))
        if(debug)
            std::cerr << "End of Game" << std::endl;
    return !(hasMoves(BLACK) || hasMoves(WHITE));
}

/*
 * Returns true if there are legal moves for the given side.
 */
bool Board::hasMoves(Side side) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move move(i, j);
            if (checkMove(&move, side)) return true;
        }
    }
    return false;
}

/*
 * Returns true if a move is legal for the given side; false otherwise.
 */
bool Board::checkMove(Move *m, Side side) {
    // Passing is only legal if you have no moves.
    if (m == nullptr) return !hasMoves(side);

    int X = m->getX();
    int Y = m->getY();

    // Make sure the square hasn't already been taken.
    if (occupied(X, Y)) return false;

    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            // Is there a capture in that direction?
            int x = X + dx;
            int y = Y + dy;
            if (onBoard(x, y) && get(other, x, y)) {
                do {
                    x += dx;
                    y += dy;
                } while (onBoard(x, y) && get(other, x, y));

                if (onBoard(x, y) && get(side, x, y)) return true;
            }
        }
    }
    return false;
}

/*
 * Modifies the board to reflect the specified move.
 */
void Board::doMove(Move *m, Side side) {
    // A nullptr move means pass.
    if (m == nullptr) return;

    // Ignore if move is invalid.
    if (!checkMove(m, side)) return;

    int X = m->getX();
    int Y = m->getY();
    Side other = (side == BLACK) ? WHITE : BLACK;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) continue;

            int x = X;
            int y = Y;
            do {
                x += dx;
                y += dy;
            } while (onBoard(x, y) && get(other, x, y));

            if (onBoard(x, y) && get(side, x, y)) {
                x = X;
                y = Y;
                x += dx;
                y += dy;
                while (onBoard(x, y) && get(other, x, y)) {
                    set(side, x, y);
                    x += dx;
                    y += dy;
                }
            }
        }
    }
    set(side, X, Y);
}

/*
 * Current count of given side's stones.
 */
int Board::count(Side side) {
    return (side == BLACK) ? countBlack() : countWhite();
}

/*
 * Current count of black stones.
 */
int Board::countBlack() {
    return black.count();
}

/*
 * Current count of white stones.
 */
int Board::countWhite() {
    return taken.count() - black.count();
}

/*
 * Sets the board state given an 8x8 char array where 'w' indicates a white
 * piece and 'b' indicates a black piece. Mainly for testing purposes.
 */
void Board::setBoard(char data[]) {
    taken.reset();
    black.reset();
    for (int i = 0; i < 64; i++) {
        if (data[i] == 'b') {
            taken.set(i);
            black.set(i);
        } if (data[i] == 'w') {
            taken.set(i);
        }
    }
}

std::vector<Move>* Board::getMoveList(Side _side){
    std::vector<Move>* possibleMoves = new std::vector<Move>;
    for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Move move(i, j);
                if (this->checkMove(&move, _side)) {
                    possibleMoves->push_back(move);
                }
            }
        }
    return possibleMoves;
}

bool Board::hasBlankNeighbor(int i, int j, Side side, Side other){
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) 
                continue;
            if (!get(other, i + dx, j + dy) && !get(side, i + dx, j + dy)){
                return true;
            }
        }
    }
    return false;
}

int Board::getMoveScoreHeuristic(Move* _move, Side side){
    // First calculate the score of the current board.
    Side other = (side == BLACK) ? WHITE : BLACK;
    int myScore = this->count(side);
    int oppScore = this->count(other);

    // Copy the board.
    Board *tempBoard = this->copy();

    // Apply the move on the copied board.
    tempBoard->doMove(_move, side);

    // Calculate the score.
    int myNewScore = tempBoard->count(side);
    int oppNewScore = tempBoard->count(other);

    int myChange = myNewScore - myScore; // The number of new pieces on my side
    int oppChange = oppNewScore - oppScore; // The number of opponent lost pieces
    int flipped = myChange - oppChange;
    int deltaScore = myNewScore - oppNewScore;

    // Check mobility and the opponent's mobility
    int mobility = tempBoard->getMoveList(side)->size();
    int antimobility = tempBoard->getMoveList(other)->size();

    // Check potential mobility
    int potentialMobility = 0;
    for(int i = 1; i < 7; i++){
        for (int j = 1; j < 7; j++){
            if(hasBlankNeighbor(i, j, side, other)){
                potentialMobility++;                
            }
        }
    }

    if(debug)
        std::cerr << "potentialMobility: " << potentialMobility << std::endl;

    // Check stability
    int stability = 0;
    int MX = _move->getX();
    int MY = _move->getY();

    // Check row to right
    for(int j = MY; j < 8; j++)
        if (tempBoard->get(side, MX, j))
        {
            if (j == 7) // You have a piece on the edge at that row. 
            {
                stability ++;
            }
        }
        else // You are not connected to the edge. 
        {
            break;
        }

    // Check row to left
    for(int j = MY; j >= 0; j--)
        if (tempBoard->get(side, MX, j))
        {
            if (j == 0) // You have a piece on the edge at that row.
            {
                stability ++;
            }
        }
        else // You are not connected to the edge. 
        {
            break;
        }
    
    // Check column below
    for(int i = MX; i < 8; i++)
        if (tempBoard->get(side, i, MY))
        {
            if (i == 7) // You have a piece on the edge at that row.
            {
                stability ++;
            }
        }
        else // You are not connected to the edge. 
        {
            break;
        }

    // Check column above
    for(int i = MX; i >= 0; i--)
        if (tempBoard->get(side, i, MY))
        {
            if (i == 0) // You have a piece on the edge at that row.
            {
                stability ++;
            }
        }
        else // You are not connected to the edge. 
        {
            break;
        }

    // Check diagonal (up right)
    int tempY = MY;
    for(int i = MX; i < 8; i++)
        if (tempBoard->get(side, i, tempY))
        {
            if (i == 0) // You have a piece on the edge at that row.
            {
                stability ++;
            }
        }
        else // You are not connected to the edge. 
        {
            break;
        }
        tempY --;

    // Check diagonal (down left)
    tempY = MY;
    for(int i = MX; i >= 0; i--)
        if (tempBoard->get(side, i, tempY))
        {
            if (i == 0) // You have a piece on the edge at that row.
            {
                stability ++;
            }
        }
        else // You are not connected to the edge. 
        {
            break;
        }
        tempY ++;

    // Check diagonal (up left)
    tempY = MY;
    for(int i = MX; i < 8; i++)
        if (tempBoard->get(side, i, tempY))
        {
            if (i == 0) // You have a piece on the edge at that row.
            {
                stability ++;
            }
        }
        else // You are not connected to the edge. 
        {
            break;
        }
        tempY ++;

    // Check diagonal (down right)
    tempY = MY;
    for(int i = MX; i >= 0; i--)
        if (tempBoard->get(side, i, tempY))
        {
            if (i == 0) // You have a piece on the edge at that row.
            {
                stability ++;
            }
        }
        else // You are not connected to the edge. 
        {
            break;
        }
        tempY --;


    int finalScore = /*myNewScore +*/ deltaScore + flipped + stability + 
        potentialMobility + mobility - antimobility + 4 * _move->getRingMultiplier();
        
    if (debug)
    {
        std::cerr << "------------------------------" << std::endl;
        std::cerr << "Score Breakdown: " << finalScore << std::endl;
        //std::cerr << "myNewScore: " << myNewScore << std::endl;
        std::cerr << "deltaScore: " << deltaScore << std::endl;
        std::cerr << "flipped: " << flipped << std::endl;
        std::cerr << "stability: " << stability << std::endl;
        std::cerr << "potentialMobility: " << potentialMobility << std::endl;
        std::cerr << "mobility: " << mobility << std::endl;
        std::cerr << "antimobility: " << -antimobility << std::endl;
        std::cerr << "Ring Multiplier: " << 4 * _move->getRingMultiplier() << std::endl;
        std::cerr << "------------------------------" << std::endl;
    }

    // Update move score.
    _move->setScore(finalScore);

    return finalScore;
}



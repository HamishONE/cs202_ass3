#include "SuperGame.hpp"
#include "Player.hpp"
#include <set>
#include <map>

bool SuperGame::playNextTurn(unsigned int column) {

    // If the game is not in progress do nothing
    if (gameStatus != GS_IN_PROGRESS) {
        return false;
    }

    // Create a disc according to the current player
    Grid::Cell disc;
    if (currentPlayer == player1) {
        disc = Grid::GC_PLAYER_ONE;
    } else {
        disc = Grid::GC_PLAYER_TWO;
    }

    // Insert the disc into the specified columns but return if it fails
    if (!grid->insertDisc(column, disc)) {
        return false;
    }

    // Loop while there is still a chain of 4 discs
    while (findWinner() != 0) {

        // Find all winners, removing the chains formed and incrementing their scores
        findAllWinners();
    }

    // Switch the current player
    if (currentPlayer == player1) {
        currentPlayer = player2;
    } else {
        currentPlayer = player1;
    }

    // If any of the top cells are empty it is not a draw, so exit the function so the game can continue
    for (unsigned int i=0; i<grid->columnCount(); i++) {
        if (grid->cellAt(0, i) == Grid::GC_EMPTY) {
            return true;
        }
    }

    // The game has finished so set the status to complete
    gameStatus = GS_COMPLETE;

    // If one player has a higher score increment their win counter
    if (player1->getScore() > player2->getScore()) {
        player1->increaseWins();
    } else if (player2->getScore() > player1->getScore()) {
        player2->increaseWins();
    }

    return true;
}

const Player* SuperGame::winner() const {

    // If the game is not complete do nothing
    if (gameStatus != GS_COMPLETE) {
        return 0;
    }

    // If one player has a larger score they are the winner
    if (player1->getScore() > player2->getScore()) {
        return player1;
    } else if (player2->getScore() > player1->getScore()) {
        return player2;
    }

    // Otherwise return null
    return 0;
}

void SuperGame::findAllWinners() const {

    // Create a list of coordinates on the grid as a set to store discs to remove in a top-down order
    typedef std::pair<unsigned int, unsigned int> coord;
    std::set<coord> list;

    // Create two booleans to store if the players should score a point
    bool p1 = false, p2 = false;

    // Create a mapping between the discs and these booleans
    std::map<Grid::Cell, bool*> map;
    map[Grid::GC_PLAYER_ONE] = &p1;
    map[Grid::GC_PLAYER_TWO] = &p2;

    // Loop through every cell on the board
    for (unsigned int i=0; i<grid->rowCount(); i++) {
        for (unsigned int j=0; j<grid->columnCount(); j++) {

            // If the cell is empty skip to the next cell
            Grid::Cell cell = grid->cellAt(i, j);
            if (cell == Grid::GC_EMPTY) {
                continue;
            }

            // Check around each cell in the 4 directions for a line of 4 and if so:
            //  - Set that players boolean to true
            //  - Add all the 4 cells to the list to remove from
            if (grid->cellAt(i+1, j) == cell && grid->cellAt(i+2, j) == cell && grid->cellAt(i+3, j) == cell) {
                *map[cell] = true;
                for (unsigned int k=0; k<4; k++) {
                    list.insert(coord(i+k, j));
                }
            }
            if (grid->cellAt(i, j+1) == cell && grid->cellAt(i, j+2) == cell && grid->cellAt(i, j+3) == cell) {
                *map[cell] = true;
                for (unsigned int k=0; k<4; k++) {
                    list.insert(coord(i, j+k));
                }
            }
            if (grid->cellAt(i+1, j+1) == cell && grid->cellAt(i+2, j+2) == cell && grid->cellAt(i+3, j+3) == cell) {
                *map[cell] = true;
                for (unsigned int k=0; k<4; k++) {
                    list.insert(coord(i+k, j+k));
                }
            }
            if (grid->cellAt(i+1, j-1) == cell && grid->cellAt(i+2, j-2) == cell && grid->cellAt(i+3, j-3) == cell) {
                *map[cell] = true;
                for (unsigned int k=0; k<4; k++) {
                    list.insert(coord(i+k, j-k));
                }
            }
        }
    }

    // Remove all discs added to the list
    for (std::set<coord>::iterator it=list.begin(); it!=list.end(); it++) {
        grid->removeDisk(it->first, it->second);
    }

    // Increase the score of players as appropriate
    if (p1) {
        player1->increaseScore();
    }
    if (p2) {
        player2->increaseScore();
    }
}
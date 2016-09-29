#include <set>
#include "SuperGame.hpp"

bool SuperGame::playNextTurn(unsigned int column) {

    if (gameStatus != GS_IN_PROGRESS) {
        return false;
    }

    Grid::Cell disc;
    if (currentPlayer == player1) {
        disc = Grid::GC_PLAYER_ONE;
    } else {
        disc = Grid::GC_PLAYER_TWO;
    }

    if (grid->insertDisc(column, disc) == false) {
        return false;
    }

    while (findWinner() != 0) {
        findWinner()->increaseScore();
        removeFour();
    }

    // Swap player
    if (currentPlayer == player1) {
        currentPlayer = player2;
    } else {
        currentPlayer = player1;
    }

    // Check for game end
    bool done = true;
    for (unsigned int i=0; i<grid->columnCount(); i++) {
        if (grid->cellAt(0, i) == Grid::GC_EMPTY) {
            done = false;
        }
    }

    // If so find winner
    if (done) {
        gameStatus = GS_COMPLETE;
        if (player1->getScore() > player2->getScore()) {
            player1->increaseWins();
        }
        if (player2->getScore() > player1->getScore()) {
            player2->increaseWins();
        }
    }

    return true;
}

void addToList(std::vector< std::pair<unsigned int, unsigned int> > &list, std::pair<unsigned int, unsigned int> pair) {
    for (unsigned int i=0; i<list.size(); i++) {
        if (list[i].first == pair.first && list[i].second == pair.second) {
            return;
        }
    }
    list.push_back(pair);
}

void SuperGame::removeFour() {

    std::vector<std::pair< unsigned int, unsigned int> > list;

    for (unsigned int i=0; i<grid->rowCount(); i++) {
        for (unsigned int j=0; j<grid->columnCount(); j++) {
            Grid::Cell cell = grid->cellAt(i, j);
            if (cell == Grid::GC_EMPTY) continue;

            if (grid->cellAt(i+1, j) == cell && grid->cellAt(i+2, j) == cell && grid->cellAt(i+3, j) == cell) {
                for (unsigned int k=0; k<4; k++) {
                    addToList(list, std::pair<unsigned int, unsigned int>(i+k,j));
                }
            }
            if (grid->cellAt(i, j+1) == cell && grid->cellAt(i, j+2) == cell && grid->cellAt(i, j+3) == cell) {
                for (unsigned int k=0; k<4; k++) {
                    addToList(list, std::pair<unsigned int, unsigned int>(i,j+k));
                }
            }
            if (grid->cellAt(i+1, j+1) == cell && grid->cellAt(i+2, j+2) == cell && grid->cellAt(i+3, j+3) == cell) {
                for (unsigned int k=0; k<4; k++) {
                    addToList(list, std::pair<unsigned int, unsigned int>(i+k,j+k));
                }
            }
        }
    }

    for (unsigned int i=0; i<list.size(); i++) {
        grid->removeDisk(list[i].first, list[i].second);
    }
}
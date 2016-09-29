#include "Game.hpp"

Game::Game() {
    gameStatus = GS_INVALID;
    grid = 0;
    player1 = 0;
    player2 = 0;
    currentPlayer = player1;
}

Game::~Game() {
    delete grid;
}

void Game::updateStatus() {
    if (player1 != 0 && player2 != 0 && grid != 0) {
        gameStatus = GS_IN_PROGRESS;
    }
}

void Game::setGrid(Grid* grid) {
    delete this->grid;
    this->grid = grid;
    updateStatus();
}

void Game::setPlayerOne(Player* player) {
    if (player == 0) return;

    if (currentPlayer == player1) currentPlayer = player;
    player1 = player;
    updateStatus();
}

void Game::setPlayerTwo(Player* player) {
    if (player == 0) return;
    player2 = player;
    updateStatus();
}

void Game::restart() {

    if (gameStatus == GS_INVALID) {
        return;
    }

    grid->reset();
    player1->resetScore();
    player2->resetScore();
    updateStatus();
}

Game::Status Game::status() const {
    return gameStatus;
}

const Player* Game::winner() const {

    if (gameStatus != GS_COMPLETE) {
        return 0;
    }

    return findWinner();
}

const Player* Game::nextPlayer() const {
    if (gameStatus != GS_IN_PROGRESS) {
        return 0;
    }
    return currentPlayer;
}

Player* Game::cellToPlayer(Grid::Cell cell) const {
    if (cell == Grid::GC_PLAYER_ONE) {
        return player1;
    } else if (cell == Grid::GC_PLAYER_TWO) {
        return player2;
    } else {
        return 0;
    }
}

Player* Game::findWinner() const {
    for (unsigned int i=0; i<grid->rowCount(); i++) {
        for (unsigned int j=0; j<grid->columnCount(); j++) {
            Grid::Cell cell = grid->cellAt(i, j);
            if (cell == Grid::GC_EMPTY) continue;

            if (grid->cellAt(i+1, j) == cell && grid->cellAt(i+2, j) == cell && grid->cellAt(i+3, j) == cell) {
                return cellToPlayer(cell);
            }
            if (grid->cellAt(i, j+1) == cell && grid->cellAt(i, j+2) == cell && grid->cellAt(i, j+3) == cell) {
                return cellToPlayer(cell);
            }
            if (grid->cellAt(i+1, j+1) == cell && grid->cellAt(i+2, j+2) == cell && grid->cellAt(i+3, j+3) == cell) {
                return cellToPlayer(cell);
            }
        }
    }
    return 0;
}

bool Game::playNextTurn(unsigned int column) {
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

    if (findWinner() == 0) {
        if (currentPlayer == player1) {
            currentPlayer = player2;
        } else {
            currentPlayer = player1;
        }

        // Check for draw
        for (unsigned int i=0; i<grid->columnCount(); i++) {
            if (grid->cellAt(0, i) == Grid::GC_EMPTY) {
                return true;
            }
        }
        gameStatus = GS_COMPLETE;

    } else {
        gameStatus = GS_COMPLETE;
        findWinner()->increaseWins();
        findWinner()->increaseScore();
    }

    return true;
}


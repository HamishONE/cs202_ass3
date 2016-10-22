#include <map>
#include "Game.hpp"

Game::Game() {

    // The game starts as invalid
    gameStatus = GS_INVALID;

    // Initialise pointers to null
    grid = 0;
    player1 = 0;
    player2 = 0;

    // The first player is player 1
    currentPlayer = player1;
}

Game::~Game() {

    // Remove the grid from the heap
    delete grid;
}

void Game::updateStatus() {

    // Set the status to in progress if the players and grid are not null
    if (player1 != 0 && player2 != 0 && grid != 0) {
        gameStatus = GS_IN_PROGRESS;
    }
}

void Game::setGrid(Grid* grid) {

    // Remove any previous allocated grid from the heap
    delete this->grid;

    // Set the grid to the one provided
    this->grid = grid;

    // Update the game status to in progress if appropriate
    updateStatus();
}

void Game::setPlayer(Player* &newPlayer, Player* &oldPlayer) {

    // If the new player provided in null do nothing
    if (newPlayer == 0) {
        return;
    }

    // If the player provided replaces the current player change the current player
    if (currentPlayer == oldPlayer) {
        currentPlayer = newPlayer;
    }

    // Replace the old player with the new one
    oldPlayer = newPlayer;

    // Update the game status to in progress if appropriate
    updateStatus();
}

void Game::setPlayerOne(Player* player) {
    setPlayer(player, player1);
}

void Game::setPlayerTwo(Player* player) {
    setPlayer(player, player2);
}

void Game::restart() {

    // If the game is not valid do nothing
    if (gameStatus == GS_INVALID) {
        return;
    }

    // Reset the grid and players scores
    grid->reset();
    player1->resetScore();
    player2->resetScore();

    // Set the game status back to in progress
    gameStatus = GS_IN_PROGRESS;
}

Game::Status Game::status() const {
    return gameStatus;
}

const Player* Game::winner() const {

    // If the game is not complete do nothing
    if (gameStatus != GS_COMPLETE) {
        return 0;
    }

    // Return the winner
    return findWinner();
}

const Player* Game::nextPlayer() const {

    // If the game is not in progress do nothing
    if (gameStatus != GS_IN_PROGRESS) {
        return 0;
    }

    // Return the current player
    return currentPlayer;
}

Player* Game::findWinner() const {

    // Create a map between the cell enum and the player pointers
    std::map<Grid::Cell, Player*> map;
    map[Grid::GC_PLAYER_ONE] = player1;
    map[Grid::GC_PLAYER_TWO] = player2;
    map[Grid::GC_EMPTY] = 0;

    // Loop through every cell in the grid
    for (unsigned int i=0; i<grid->rowCount(); i++) {
        for (unsigned int j=0; j<grid->columnCount(); j++) {

            // If the cell is empty skip to the next cell
            Grid::Cell cell = grid->cellAt(i, j);
            if (cell == Grid::GC_EMPTY) {
                continue;
            }

            // Check around each cell in the 4 directions for a line of 4 and if so return the player using the map
            if (grid->cellAt(i+1, j) == cell && grid->cellAt(i+2, j) == cell && grid->cellAt(i+3, j) == cell) {
                return map[cell];
            }
            if (grid->cellAt(i, j+1) == cell && grid->cellAt(i, j+2) == cell && grid->cellAt(i, j+3) == cell) {
                return map[cell];
            }
            if (grid->cellAt(i+1, j+1) == cell && grid->cellAt(i+2, j+2) == cell && grid->cellAt(i+3, j+3) == cell) {
                return map[cell];
            }
            if (grid->cellAt(i+1, j-1) == cell && grid->cellAt(i+2, j-2) == cell && grid->cellAt(i+3, j-3) == cell) {
                return map[cell];
            }
        }
    }

    // Otherwise no-one has won so return null
    return 0;
}

bool Game::playNextTurn(unsigned int column) {

    // If the game is not in progress do nothing
    if (gameStatus != GS_IN_PROGRESS) {
        return false;
    }

    // Create a disc for the current player
    Grid::Cell disc;
    if (currentPlayer == player1) {
        disc = Grid::GC_PLAYER_ONE;
    } else {
        disc = Grid::GC_PLAYER_TWO;
    }

    // Create a disc according to the current player
    if (!grid->insertDisc(column, disc)) {
        return false;
    }

    // Check if there is a winner
    if (findWinner() == 0) {

        // If there is no winner switch the current player
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

    } else {

        // If there is a winner increase there score and wins by 1
        findWinner()->increaseWins();
        findWinner()->increaseScore();
    }

    // The game has finished so set the status to complete
    gameStatus = GS_COMPLETE;
    return true;
}


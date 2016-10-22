#ifndef SUPERGAME_HPP
#define SUPERGAME_HPP

#include "Game.hpp"

class SuperGame : public Game {
public:
	SuperGame();
    bool playNextTurn(unsigned int column);
    const Player* winner() const;
private:
    void removeFour();
    std::vector<Player*> findAllWinners() const;
    const Player *winningPlayer;
};

#endif /* end of include guard: SUPERGAME_HPP */

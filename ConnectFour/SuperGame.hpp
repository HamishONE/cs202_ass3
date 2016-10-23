#ifndef SUPERGAME_HPP
#define SUPERGAME_HPP

#include "Game.hpp"

class SuperGame : public Game {
public:
    bool playNextTurn(unsigned int column);
    const Player* winner() const;
private:
    void findAllWinners();
};

#endif /* end of include guard: SUPERGAME_HPP */

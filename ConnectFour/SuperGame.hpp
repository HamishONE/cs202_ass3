#ifndef SUPERGAME_HPP
#define SUPERGAME_HPP

#include "Game.hpp"

class SuperGame : public Game {
public:
    bool playNextTurn(unsigned int column);
private:
    void removeFour();
    std::vector<Player*> findAllWinners() const;
};

#endif /* end of include guard: SUPERGAME_HPP */

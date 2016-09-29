#ifndef SUPERGAME_HPP
#define SUPERGAME_HPP

#include "Game.hpp"

class SuperGame : public Game {
public:
    bool playNextTurn(unsigned int column);
    const Player* winner() const;
private:
    void removeFour();
    std::vector<Player*> findAllWinners() const;
    void findEnd();
    const Player *winningPlayer;
};

#endif /* end of include guard: SUPERGAME_HPP */

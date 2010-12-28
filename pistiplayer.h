#ifndef PISTIPLAYER_H
#define PISTIPLAYER_H

#include "core/player.h"

class State;
class PistiPlayer : public Player
{
public:
    PistiPlayer(int r_pos = 0, QObject *parent = 0);
    PistiPlayer(QString name, int pos = 0, QObject *parent = 0);

    /* override */
    Card* dummyPlay();
    Card* dummyPlay(State &state);
    void computeScore();
    void reset();
};

#endif // PISTIPLAYER_H

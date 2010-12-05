#ifndef PISTIPLAYER_H
#define PISTIPLAYER_H

#include "core/player.h"

class PistiPlayer : public Player
{
public:
    PistiPlayer(int r_pos = 0, QObject *parent = 0);
    PistiPlayer(QString name, int pos = 0, QObject *parent = 0);

    /* override */
    Card* dummyPlay();
    void computeScore();
};

#endif // PISTIPLAYER_H

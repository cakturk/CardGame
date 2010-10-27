#ifndef BATAKPLAYER_H
#define BATAKPLAYER_H

#include "core/player.h"

class BatakPlayer : public Player
{
public:
    BatakPlayer(int r_pos = 0, QObject *parent = 0);
    BatakPlayer(QString name, int pos = 0, QObject *parent = 0);

    Card* play(int index);
    Card* play(QObject *cardObj);
    Card* dummyPlay();
    inline void kozPlayed() { seenKozSoFar = true; }

private:
    bool seenKozSoFar;
    quint16 bet;
};

#endif // BATAKPLAYER_H

#ifndef BATAKPLAYER_H
#define BATAKPLAYER_H

#include "core/player.h"

class BatakPlayer : public Player
{
public:
    BatakPlayer(int r_pos = 0, QObject *parent = 0);
    BatakPlayer(QString name, int pos = 0, QObject *parent = 0);

    Card* play(int index);
    Card* dummyPlay();

    void computeScore();

    inline void betFor(int number) { bet_ = number; }
    inline int bet() const { return bet_; }
    inline void kozPlayed() { seenKozSoFar = true; }
    inline void resetBet() { bet_ = 0; }

private:
    int estimateBet();

    bool seenKozSoFar;
    int bet_, scoredBet;
};

#endif // BATAKPLAYER_H

#ifndef BATAKPLAYER_H
#define BATAKPLAYER_H

#include "core/player.h"
#include "state.h"

class BatakPlayer : public Player
{
public:
    BatakPlayer(int r_pos = 0, QObject *parent = 0);
    BatakPlayer(QString name, int pos = 0, QObject *parent = 0);

    Card* play(int index);
    Card* play(int index, State &state);
    Card* dummyPlay(State &state);
    Card* dummyPlayV2(State &state);

    void computeScore();

    inline void bidFor(int number) { bid_ = number; }
    inline void resetBid() { bid_ = 0; }
    inline int trick() const { return bid_; }
    int makeBidDecision() const;

private:
    int bidDecisionHelper(CardSequence &) const;
    CardSequence validCards(State&);

    bool isValid(Card *selectedCard, State &state);
    int compare(Card *lhs, Card *rhs) const;

    int bid_, tricks_;
};

#endif // BATAKPLAYER_H

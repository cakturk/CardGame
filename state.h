#ifndef STATE_H
#define STATE_H

#include "core/card.h"
template <class T> class QList;

/**
 * Holds the current state of the game.
 */
class State
{
public:
    State();

    inline void appendToBoard(Card *card) { cardsOnBoard_.append(card); }
    void appendToPlayedCard(Card *card);

    inline const QList<Card *> cardsOnBoard() const { return cardsOnBoard_; }
    inline const QList<Card *> playedCards() const { return playedCards_; }
    inline int sizeofCardsOnBoard() const { return cardsOnBoard_.size(); }
    inline int sizeofPlayedCards() const { return playedCards_.size(); }
    inline bool contains(Card *card) const { return (playedCards_.contains(card)); }
    inline Card* bottom() const { return cardsOnBoard_.last(); }
    inline Card* top() const { return cardsOnBoard_.first(); }
    inline int karoCount() const { return karoCount_; }
    inline int kupaCount() const { return kupaCount_; }
    inline int sinekCount() const { return sinekCount_; }
    inline int macaCount() const { return macaCount_; }

    const Card* highestRankedCardOnBoard(Card::Suit type) const;
    const Card* lowstRankedCardBoard(Card::Suit suit) const;
    bool boardContainsKoz() const;

private:
    QList<Card *> cardsOnBoard_;
    QList<Card *> playedCards_;

    int karoCount_, kupaCount_, sinekCount_, macaCount_;

    bool playedKozSoFar;
};

#endif // STATE_H

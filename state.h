#ifndef STATE_H
#define STATE_H

#include "core/card.h"
#include "core/cardsequence.h"
template <class T> class QList;

/**
 * Holds the current state of the game.
 */
class State
{
public:
    State();

    inline void appendToBoard(Card *card) { m_cardsOnBoard->append(card); }
    void appendToPlayedCard(Card *card);
    void append(Card *card);

    inline const CardSequence* cardsOnBoard() const { return m_cardsOnBoard; }
    inline const CardSequence* playedCards() const { return m_playedCards; }
    inline int sizeofCardsOnBoard() const { return m_cardsOnBoard->size(); }
    inline int sizeofPlayedCards() const { return m_playedCards->size(); }
    inline bool contains(Card *card) const { return (playedCards_.contains(card)); }
    inline Card* bottom() const { return m_cardsOnBoard->takeLast(); }
    inline Card* top() const { return m_cardsOnBoard->takeFirst(); }

    const Card* highestRankedCardOnBoard(Card::Suit suit) const;
    const Card* lowstRankedCardBoard(Card::Suit suit) const;
    bool boardContainsKoz() const;

private:
    QList<Card *> cardsOnBoard_;
    QList<Card *> playedCards_;

    /* cardsOnBoard is a subset of playedCards */
    CardSequence *m_cardsOnBoard;
    CardSequence *m_playedCards;

    int karoCount_, kupaCount_, sinekCount_, macaCount_;
    bool playedKozSoFar;
};

#endif // STATE_H

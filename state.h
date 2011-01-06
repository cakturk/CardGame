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

    // TODO: Remove board function
    inline void appendToBoard(Card *card) { m_cardsOnBoard.append(card); }
    void appendToPlayedCard(Card *card);
    void append(Card *card);

    CardSequence takeCardsFromBoard();
    inline CardSequence cardsOnBoard() const { return m_cardsOnBoard; }
    inline CardSequence playedCards() const { return m_playedCards; }

    inline void clearBoard() { m_cardsOnBoard.clear(); }
    inline void clearPlayedCards() { m_playedCards.clear(); }
    void clear();

    inline int sizeofCardsOnBoard() const { return m_cardsOnBoard.size(); }
    inline int sizeofPlayedCards() const { return m_playedCards.size(); }

    inline bool contains(Card *card) const { return (m_playedCards.contains(card)); }
    inline bool isKozBroken() const { return m_playedCards.hasMaca(); }

    inline Card* lastPlayedCard() { return m_cardsOnBoard.last(); }
    inline Card* firstPlayedCard() { return m_cardsOnBoard.first(); }

    const Card* highestRankedCardOnBoard(Card::Suit suit) const;
    const Card* lowstRankedCardBoard(Card::Suit suit) const;

private:
    /* cardsOnBoard is a subset of playedCards */
    CardSequence m_cardsOnBoard;
    CardSequence m_playedCards;

    int karoCount_, kupaCount_, sinekCount_, macaCount_;
    bool playedKozSoFar;
};

#endif // STATE_H

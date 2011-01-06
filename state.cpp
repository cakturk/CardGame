#include <QList>
#include "state.h"

State::State()
{ }

void State::appendToPlayedCard(Card *card)
{
    m_playedCards.append(card);
}

void State::append(Card *card)
{
    m_cardsOnBoard.append(card);
    m_playedCards.append(card);
}

CardSequence State::takeCardsFromBoard()
{
    CardSequence cs = m_cardsOnBoard;
    m_cardsOnBoard.clear();
    return cs;
}

void State::clear()
{
    m_cardsOnBoard.clear();
    m_playedCards.clear();
}

const Card* State::highestRankedCardOnBoard(Card::Suit suit) const
{
    return m_cardsOnBoard.highestRankedCardFor(suit);
}

const Card* State::lowstRankedCardBoard(Card::Suit suit) const
{
    return m_cardsOnBoard.lowestRankedCardFor(suit);
}

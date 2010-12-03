#include <QList>
#include "state.h"

State::State()
{ }

void State::appendToPlayedCard(Card *card)
{
    m_playedCards->append(card);
}

void State::append(Card *card)
{
    m_cardsOnBoard->append(card);
    m_playedCards->append(card);
}

const Card* State::highestRankedCardOnBoard(Card::Suit suit) const
{
    return m_cardsOnBoard->highestRankedCardFor(suit);
}

const Card* State::lowstRankedCardBoard(Card::Suit suit) const
{
    return m_cardsOnBoard->lowestRankedCardFor(suit);
}

bool State::boardContainsKoz() const
{
    return m_playedCards->hasMaca();
}

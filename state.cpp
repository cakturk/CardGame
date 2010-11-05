#include <QList>
#include "state.h"

State::State() : karoCount_(0), kupaCount_(0), sinekCount_(0), macaCount_(0), playedKozSoFar(false)
{
}

void State::appendToPlayedCard(Card *card)
{
    switch (card->suit) {
    case Card::KARO:
        ++karoCount_;
        break;
    case Card::KUPA:
        ++kupaCount_;
        break;
    case Card::SINEK:
        ++sinekCount_;
        break;
    case Card::MACA:
        ++macaCount_;
        break;
    }

    playedCards_.append(card);
}

const Card* State::highestRankedCardOnBoard(Card::Suit suit) const
{
    Card *currentCard = NULL;
    Card* previousCard = cardsOnBoard_.first();

    int max = 0;
    for (int j = 0; j < sizeofCardsOnBoard(); ++j) {
        currentCard = cardsOnBoard_.at(j);

        if (currentCard->suit == suit &&
            currentCard->value > previousCard->value) {
            max = j;
        }

        previousCard = currentCard;
    }

    return cardsOnBoard_.at(max);
}

const Card* State::lowstRankedCardBoard(Card::Suit suit) const
{
    Card *currentCard = NULL;
    Card* previousCard = cardsOnBoard_.first();

    int min = 0;
    for (int j = 0; j < sizeofCardsOnBoard(); ++j) {
        currentCard = cardsOnBoard_.at(j);

        if (currentCard->suit == suit &&
            currentCard->value < previousCard->value) {
            min = j;
        }

        previousCard = currentCard;
    }

    return cardsOnBoard_.at(min);
}

bool State::boardContainsKoz() const
{
    Card *card;
    for (int j = 0; cardsOnBoard_.size(); ++j) {
        card = cardsOnBoard_.at(j);
        if (card->suit == Card::MACA)
            return true;
    }

    return false;
}

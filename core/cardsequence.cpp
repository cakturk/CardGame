#include "cardsequence.h"
#include <QList>

CardSequence::CardSequence()
{
}

void CardSequence::append(Card *card)
{
    incSuitCount(card->suit);
    cardSequence.append(card);
}

bool CardSequence::remove(Card *card)
{
    decSuitCount(card->suit);
    return cardSequence.removeOne(card);
}

void CardSequence::removeAt(int index)
{
    Card::Suit suit = cardSequence.at(index)->suit;
    decSuitCount(suit);
    cardSequence.removeAt(index);
}

Card* CardSequence::takeFirst()
{
    Card *first = cardSequence.takeFirst();
    decSuitCount(first->suit);
    return first;
}

Card* CardSequence::takeLast()
{
    Card *last = cardSequence.takeLast();
    decSuitCount(last->suit);
    return last;
}

Card* CardSequence::takeAt(int n)
{
    Card *returnee = cardSequence.takeAt(n);
    decSuitCount(returnee->suit);
    return returnee;
}

Card* CardSequence::take(Card *card)
{
    Card *returnee;
    int n = find(card);

    if (n >= 0)
        returnee = cardSequence.at(n);
    else
        returnee = NULL;

    return returnee;
}

Card* CardSequence::highestRankedCardFor(Card::Suit suit)
{
    Card *currentCard = NULL;
    Card* previousCard = cardSequence.first();

    int max = 0;
    for (int j = 0; j < cardSequence.size(); ++j) {
        currentCard = cardSequence.at(j);

        if (currentCard->suit == suit &&
            currentCard->value > previousCard->value) {
            max = j;
        }

        previousCard = currentCard;
    }

    return cardSequence.at(max);
}

bool CardSequence::hasKaro() const
{
    return hasSuit(Card::KARO);
}

bool CardSequence::hasKupa() const
{
    return hasSuit(Card::KUPA);
}

bool CardSequence::hasSinek() const
{
    return hasSuit(Card::SINEK);
}

bool CardSequence::hasMaca() const
{
    return hasSuit(Card::MACA);
}

bool CardSequence::hasOtherThan(Card::Suit suit) const
{
    Card *card;
    for (int j = 0; j < cardSequence.size(); ++j) {
        card = cardSequence.at(j);
        if (card->suit != suit)
            return false;
    }

    return true;
}

bool CardSequence::hasSuit(Card::Suit suit) const
{
    Card *card;
    for (int j = 0; cardSequence.size(); ++j) {
        card = cardSequence.at(j);
        if (card->suit == suit)
            return true;
    }

    return false;
}

bool CardSequence::hasCard(Card *card) const
{
    if (hasSuit(card->suit))
        foreach (Card *requestedCard, cardSequence)
            if (requestedCard->value == card->value)
                return true;

    return false;
}

void CardSequence::sortCards()
{
    qSort(cardSequence.begin(), cardSequence.end(), lessThan);
}

inline
        void CardSequence::incSuitCount(Card::Suit suit)
{
    switch (suit) {
    case Card::KARO:
        --karoCount_;
        break;
    case Card::KUPA:
        --kupaCount_;
        break;
    case Card::SINEK:
        --sinekCount_;
        break;
    case Card::MACA:
        --macaCount_;
        break;
    }
}

inline
        void CardSequence::decSuitCount(Card::Suit suit)
{
    switch (suit) {
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
}

int CardSequence::find(Card *card)
{
    int n = 0;
    foreach (Card *lookFor, cardSequence) {
        if (lookFor->suit == card->suit &&
            lookFor->value == card->value)
            return n;
        ++n;
    }

    return -1;
}

bool lessThan(Card *lhs, Card *rhs)
{
    if (lhs->suit < rhs->suit) {
        return true;
    } else {
        if (rhs->value == 1)
            return true;
        else if (lhs->value < rhs->value)
            return true;
        else
            return false;
    }
}

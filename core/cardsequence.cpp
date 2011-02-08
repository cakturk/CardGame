#include "cardsequence.h"
#include <QList>

CardSequence::CardSequence() :
        karoCount_(0), kupaCount_(0), sinekCount_(0), macaCount_(0)
{ }

/*
 * Copy constructor
 */
CardSequence::CardSequence(const CardSequence &rhs)
{
    // "copy constructor";
    if (this == &rhs)
        return;

    this->cardSequence = rhs.cardSequence;
    this->karoCount_ = rhs.karoCount_;
    this->kupaCount_ = rhs.kupaCount_;
    this->sinekCount_ = rhs.sinekCount_;
    this->macaCount_ = rhs.macaCount_;
}

CardSequence & CardSequence::operator =(const CardSequence &rhs)
{
    // "assignment operator";
    this->cardSequence = rhs.cardSequence;
    this->karoCount_ = rhs.karoCount_;
    this->kupaCount_ = rhs.kupaCount_;
    this->sinekCount_ = rhs.sinekCount_;
    this->macaCount_ = rhs.macaCount_;

    return *this;
}

void CardSequence::append(Card *card)
{
    incSuitCount(card->suit);
    cardSequence.append(card);
}

void CardSequence::append(CardSequence &rhs)
{
    for (int i = 0; i < rhs.size(); ++i)
        this->append(rhs.at(i));
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

void CardSequence::clear()
{
    cardSequence.clear();
    karoCount_ = 0;
    kupaCount_ = 0;
    sinekCount_ = 0;
    macaCount_ = 0;
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
        returnee = cardSequence.takeAt(n);
    else
        returnee = NULL;

    return returnee;
}

int CardSequence::count(Card *card) const
{
    int retVal = 0;
    for (int j = 0; j < cardSequence.size(); ++j) {
        if (cardSequence.at(j)->value == card->value)
            ++retVal;
    }

    return retVal;
}

Card* CardSequence::highestRankedCardFor(Card::Suit suit) const
{
    CardSequence seq = filterBySuit(suit);
    seq.sortCards();

    return seq.last();
}

Card* CardSequence::lowestRankedCardFor(Card::Suit suit) const
{
    Card *currentCard = NULL;
    Card *previousCard = cardSequence.first();

    int min= 0;
    for (int j = 0; j < cardSequence.size(); ++j) {
        currentCard = cardSequence.at(j);

        if (currentCard->suit == suit &&
            currentCard->value < previousCard->value)
            min = j;
    }

    return cardSequence.at(min);
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

bool CardSequence::hasOtherThan(int value) const
{
    Card *card;
    for (int j = 0; j < cardSequence.size(); ++j) {
        card = cardSequence.at(j);
        if (card->value != value)
            return true;
    }

    return false;
}

bool CardSequence::hasGreaterThan(int value) const
{
    if (value == 1)
        return false;

    Card *card;
    for (int j = 0; j < cardSequence.size(); ++j) {
        card = cardSequence.at(j);

        if (card->value == 1)
            return true;

        if (card->value != 1 && card->value > value) {
            qDebug() << "hasGreaterThan" << card->value << "<" << value;
            return true;
        }
    }

    return false;
}

bool CardSequence::hasGreaterThan(Card *card) const
{
    if (hasSuit(card->suit))
        return filterBySuit(card->suit).hasGreaterThan(card->value);

    return false;
}

CardSequence CardSequence::filterOut(Card::Suit suit) const
{
    CardSequence retVal;
    Card *card;
    for (int j = 0; j < cardSequence.size(); ++j) {
        card = cardSequence.at(j);
        if (card->suit != suit)
            retVal.append(card);
    }

    return retVal;
}

CardSequence CardSequence::filterOut(int value) const
{
    CardSequence retVal;
    Card *card;
    for (int j = 0; j < cardSequence.size(); ++j) {
        card = cardSequence.at(j);
        if (card->value != value)
            retVal.append(card);
    }

    return retVal;
}

CardSequence CardSequence::filterOutLessThan(Card *card) const
{
    Card *c;
    CardSequence retVal;
    CardSequence seq = filterBySuit(card->suit);

    for (int j = 0; j < seq.size(); ++j) {
        c = seq.at(j);

        if (c->value == 1)
            retVal.append(c);
        else if (card->value < c->value)
            retVal.append(c);
    }

    return retVal;
}

CardSequence CardSequence::filterBySuit(Card::Suit suit) const
{
    CardSequence retVal;
    Card *card;
    for (int j = 0; j < cardSequence.size(); ++j) {
        card = cardSequence.at(j);
        if (card->suit == suit)
            retVal.append(card);
    }

    return retVal;
}

CardSequence CardSequence::filterByValue(int value) const
{
    CardSequence retVal;
    Card *card;
    for (int j = 0; j < cardSequence.size(); ++j) {
        card = cardSequence.at(j);
        if (card->value == value)
            retVal.append(card);
    }

    return retVal;
}

bool CardSequence::hasSuit(Card::Suit suit) const
{
    Card *card;
    for (int j = 0; j < cardSequence.size(); ++j) {
        card = cardSequence.at(j);
        if (card->suit == suit)
            return true;
    }

    return false;
}

bool CardSequence::hasCard(Card *card) const
{
    return find(card) != -1;
}

void CardSequence::sortCards()
{
    qSort(cardSequence.begin(), cardSequence.end(), lessThan);
}

void CardSequence::shuffle()
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    for (int i = cardSequence.size() - 1; i > 0; --i) {
        int random = qrand() % cardSequence.size();
        Card *temp = cardSequence.at(i);
        cardSequence[i] = cardSequence.at(random);
        cardSequence[random] = temp;
    }
}

inline
void CardSequence::incSuitCount(Card::Suit suit)
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

inline
void CardSequence::decSuitCount(Card::Suit suit)
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

int CardSequence::find(Card *card) const
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
    } else if (lhs->suit > rhs->suit) {
        return false;
    } else {
        if (rhs->value == 1)
            return true;
        else if (lhs->value == 1)
            return false;
        else
            return lhs->value < rhs->value;
    }
}

#include "person.h"

Person::Person(QObject *parent) :
    QObject(parent)
{
    turn = false;
    pistiCount = score = 0;
}

void Person::setHand(QList<Card *> &h)
{
    this->hand = h;
}

Card* Person::play(int index)
{
    Card *c = hand.at(index);
    if (isAcceptable(c))
        return ( hand.takeAt(index) );

    return NULL;
}

Card* Person::play(Card *lastPlayedCard)
{
    if (hand.contains(lastPlayedCard)) {
        int index = hand.indexOf(lastPlayedCard);
        return (hand.takeAt(index));
    } else {
        Card *vale;
        for (int index = 0; index < hand.size(); index++) {
            vale = hand.at(index);

            if (vale->cardNumber == 11)
                return (hand.takeAt(index));
        }
    }

    return hand.takeFirst();
}

Card* Person::dummyPlay(Card* lastPlayedCard)
{
    if (lastPlayedCard != NULL) {
        if(hand.contains(lastPlayedCard)) {
            int index = hand.indexOf(lastPlayedCard);
            return (hand.takeAt(index));
        } else {
            Card *vale;
            for (int i = 0; i < hand.size(); i++) {
                vale = hand.at(i);
                if (vale->cardNumber == 11)
                    return (hand.takeAt(i));
            }
        }
    } else {
        for (int i = 0; i < hand.size(); i++) {
            Card *c;
            c = hand.at(i);
            if (c->cardNumber != 11)
                return (hand.takeAt(i));
        }
    }

    return hand.takeFirst();
}

void Person::collectCards(QList<Card *> &c)
{
    Card *card;

    for (int i = 0; c.size(); ++i) {
        card = c.takeFirst();
        scoredCards.append(card);
    }
}

void Person::reset()
{
    hand.clear();
    scoredCards.clear();
    pistiCount = 0;
    score = 0;
}

bool Person::isAcceptable(Card *c)
{
    // TODO atilan kart uygun mu
    return true;
}

const QList<Card *>& Person::getScoredCards()
{
    return scoredCards;
}

int Person::getNumberOfCards()
{
    return (this->hand.size());
}

QList<Card *>& Person::getHand()
{
    return hand;
}

void Person::computePlayerScore()
{
    int pCount = pistiCount;
    while (pCount--)
        score += 10;

    pCount = 0;

    for (int i = 0; i < scoredCards.size(); i++) {
        Card *card = scoredCards.at(i);

        if (card->cardNumber == 1)
            score++;
        if (card->cardNumber == 11)
            score++;
        if (card->type == Card::SINEK && card->cardNumber == 2)
            score += 2;
        if (card->type == Card::KARO && card->cardNumber == 10)
            score += 3;
    }
}

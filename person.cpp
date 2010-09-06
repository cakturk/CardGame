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

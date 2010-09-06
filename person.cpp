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
    Card *retVal;

    if (hand.contains(lastPlayedCard)) {
        int index = hand.indexOf(lastPlayedCard);
        retVal = hand.takeAt(index);
    } else {
        Card *vale;
        for (int index = 0; index < hand.size(); index++) {
            vale = hand.at(index);

            if (vale->cardNumber == 11) {
                retVal = hand.takeAt(index);
                break;
            }
        }
    }

    return retVal;
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

#include "player.h"

Player::Player(int r_pos, QObject *parent) :
    QObject(parent), realPosition(r_pos)
{
    turn = _myself = false;
    pistiCount = score = 0;
    sock = 0;
}

Player::Player(QString name, int r_pos, QObject *parent) :
        QObject(parent), playerName(name), realPosition(r_pos)
{
    turn = _myself = false;
    pistiCount = score = 0;
    sock = 0;
}

Player::~Player()
{
    if (scoredCards.size()) {
        foreach (Card *card, scoredCards) {
            delete card;
        }
    }

    if (hand.size()) {
        const Card *card;
        for (int j = 0; j < hand.size(); j++) {
            card = hand.at(j);
            delete card;
        }
    }
}

void Player::setHand(CardSequence &rhs)
{
    this->hand = rhs;
}

Card* Player::play(int index)
{
    if (index < 0 || 3 < index)
        return hand.takeFirst();

    const Card *c = hand.at(index);
    if (isAcceptable(c))
        return ( hand.takeAt(index) );

    return NULL;
}

Card* Player::play(Card *lastPlayedCard)
{
    if (hand.contains(lastPlayedCard)) {
        return (hand.take(lastPlayedCard));
    } else {
        const Card *vale;
        for (int index = 0; index < hand.size(); index++) {
            vale = hand.at(index);

            if (vale->value == 11)
                return (hand.takeAt(index));
        }
    }

    return hand.takeFirst();
}

Card* Player::play(QObject *obj)
{
    Card *clickedCard = static_cast<Card *>(obj);

    int index = 0;
    for (int j = 0; j < hand.size(); ++j) {
        if (clickedCard == hand.at(j)) {
            index = j;
            break;
        }
    }

    return (this->play(index));
}

Card* Player::dummyPlay(Card* lastPlayedCard)
{
    if (lastPlayedCard != NULL) {
        if(hand.contains(lastPlayedCard)) {
            return (hand.take(lastPlayedCard));
        } else {
            const Card *vale;
            for (int i = 0; i < hand.size(); i++) {
                vale = hand.at(i);
                if (vale->value == 11)
                    return (hand.takeAt(i));
            }
        }
    } else {
        for (int i = 0; i < hand.size(); i++) {
            const Card *c;
            c = hand.at(i);
            if (c->value != 11)
                return (hand.takeAt(i));
        }
    }

    return hand.takeFirst();
}

void Player::collectCards(QList<Card *> &c)
{
    Card *card;

    for (int i = 0; c.size(); ++i) {
        card = c.takeFirst();
        scoredCards.append(card);
    }
}

void Player::reset()
{
    hand.clear();
    scoredCards.clear();
    pistiCount = 0;
    score = 0;
}

bool Player::isAcceptable(const Card *) const
{
    // TODO atilan kart uygun mu
    return true;
}

const QList<Card *>& Player::getScoredCards()
{
    return scoredCards;
}

int Player::getNumberOfCards() const
{
    return (this->hand.size());
}

CardSequence & Player::getHand()
{
    return hand;
}


void Player::setTurn(bool b)
{
    turn = b;
}


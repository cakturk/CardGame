#include "pistiplayer.h"
#include "state.h"

PistiPlayer::PistiPlayer(int r_pos, QObject *parent) :
        Player(r_pos, parent)
{ }

PistiPlayer::PistiPlayer(QString name, int pos, QObject *parent) :
        Player(name, pos, parent)
{ }

Card* PistiPlayer::dummyPlay()
{
    Card *lastPlayedCard = NULL;

    if (! cardsOnTable.isEmpty())
        lastPlayedCard = cardsOnTable.last();

    if (lastPlayedCard == NULL)
        qDebug() << "lastplayedcard == Nil";

    if (hand.contains(lastPlayedCard)) {
        return (hand.take(lastPlayedCard));
    } else {
        Card *vale;
        for (int i = 0; i < hand.size(); ++i) {
            vale = hand.at(i);
            if (vale->value == 11)
                return (hand.takeAt(i));
        }

        int imax = 0, count = 0, previousCount = 0;
        if (playedCards_.size()) {
            for (int i = 0; i < hand.size(); ++i) {
                vale = hand.at(i);
                Card *foo = vale;
                count = playedCards_.count(foo);
                if (count > previousCount)
                    imax = i;
                previousCount = count;
            }
            return (hand.takeAt(imax));
        }
    }

    return hand.takeFirst();
}

Card* PistiPlayer::dummyPlay(State &state)
{
    CardSequence sequence;
    Card* lastPlayedCard;
    Card* retVal;

    if (! hand.size())
        return NULL;

    if (state.sizeofCardsOnBoard()) {
        lastPlayedCard = state.lastPlayedCard();

        sequence = hand.filterByValue(lastPlayedCard->value);
        if (sequence.size()) {
            retVal = sequence.first();
            // Vale varsa bul.
        } else if ((sequence = hand.filterByValue(11)).size()) {
            retVal = sequence.first();
        } else {
            Card *card;
            int imax = 0, count = 0, previousCount = 0;
            for (int j = 0; j < hand.size(); ++j) {
                card = hand.at(j);
                count = state.playedCards().count(card);
                if (count > previousCount)
                    imax = j;

                previousCount = count;
            }
            return hand.at(imax);
        }
    }

    return hand.takeFirst();
}

Card* PistiPlayer::play(Card *card, State &state)
{
    return NULL;
}

void PistiPlayer::computeScore()
{
    int pCount = pistiCount;
    while (pCount--)
        score += 10;

    pCount = 0;

    for (int i = 0; i < getScoredCards().size(); i++) {
        Card *card = getScoredCards().at(i);

        if (card->value == 1)
            score++;
        if (card->value == 11)
            score++;
        if (card->type == Card::SINEK && card->value == 2)
            score += 2;
        if (card->type == Card::KARO && card->value == 10)
            score += 3;
    }
}

void PistiPlayer::reset()
{
    Player::reset();
}

int PistiPlayer::makeBidDecision()
{
    qWarning() << "This function hasn't implemented yet"
               << "Don't use this function for PistiEngine";
    return -1;
}

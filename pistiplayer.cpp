#include "pistiplayer.h"

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
        qDebug() << "lastplayedcar == Nil";

    if (hand.contains(lastPlayedCard)) {
        int index = hand.indexOf(lastPlayedCard);
        return (hand.takeAt(index));
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
                count = playedCards_.count(vale);
                if (count > previousCount)
                    imax = i;
                previousCount = count;
            }
            return (hand.takeAt(imax));
        }
    }

    return hand.takeFirst();
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

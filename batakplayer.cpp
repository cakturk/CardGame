#include "batakplayer.h"

BatakPlayer::BatakPlayer(int r_pos, QObject *parent) :
        Player(r_pos, parent), seenKozSoFar(false), bet_(0), scoredBet(0)
{ }

BatakPlayer::BatakPlayer(QString name, int pos, QObject *parent) :
        Player(name, pos, parent), seenKozSoFar(false), bet_(0), scoredBet(0)
{ }

Card* BatakPlayer::play(int index)
{
    if (index < 0 && index > cardsOnTable.size())
        return NULL;

    Card *typeToPlay = 0, *valueToRaise = 0, *selectedCard = 0;

    selectedCard = hand.at(index);

    if (cardsOnTable.size()) {
        typeToPlay = cardsOnTable.first();
        valueToRaise = cardsOnTable.last();

        QListIterator<Card *> it(cardsOnTable);
        it.toBack();
        while (it.hasPrevious()) {
            valueToRaise = it.previous();
            if (valueToRaise->cardType == typeToPlay->cardType) {
                break;
            }
        }

        if (selectedCard->cardType == valueToRaise->cardType
            && selectedCard->cardNumber > valueToRaise->cardNumber)
            return (hand.takeAt(index));

    } else if (selectedCard->cardType != Card::MACA) {
            return (hand.takeAt(index));
    }

    return NULL;
}

Card* BatakPlayer::dummyPlay()
{
    if (cardsOnTable.size()) {

    }
    return NULL;
}

void BatakPlayer::computeScore()
{
    int roundScore = scoredCards.size() / 4;

    if (roundScore >= bet_) {
        score += (bet_ * 10);
    } else {
        score += (bet_ * (-10));
    }
}

int BatakPlayer::estimateBet()
{
    return 0;
}

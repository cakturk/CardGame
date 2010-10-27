#include "batakplayer.h"

BatakPlayer::BatakPlayer(int r_pos, QObject *parent) :
        Player(r_pos, parent), seenKozSoFar(false)
{ }

BatakPlayer::BatakPlayer(QString name, int pos, QObject *parent) :
        Player(name, pos, parent), seenKozSoFar(false)
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
            return selectedCard;
    } else {
        if (selectedCard->cardType != Card::MACA)
            return selectedCard;
    }

    return NULL;
}

Card* BatakPlayer::dummyPlay()
{
    if (cardsOnTable.size()) {

    }
    return NULL;
}

Card* BatakPlayer::play(QObject *obj)
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

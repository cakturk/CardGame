#include "batakplayer.h"

BatakPlayer::BatakPlayer(int r_pos, QObject *parent) :
        Player(r_pos, parent), bid_(0), trick_(0)
{ }

BatakPlayer::BatakPlayer(QString name, int pos, QObject *parent) :
        Player(name, pos, parent), bid_(0), trick_(0)
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
            if (valueToRaise->suit == typeToPlay->suit) {
                break;
            }
        }

        if (selectedCard->suit == valueToRaise->suit
            && selectedCard->value > valueToRaise->value)
            return (hand.takeAt(index));

    } else if (selectedCard->suit != Card::MACA) {
            return (hand.takeAt(index));
    }

    return NULL;
}

Card* BatakPlayer::dummyPlay(State *state)
{
    Card *card;

    if (state->sizeofCardsOnBoard()) {
        Card *bottom = state->bottom();
        const Card *highestRankedCard = state->highestRankedCardOnBoard(bottom->suit);

        if (hasGreaterRankedCard(highestRankedCard)) {

        } else {

        }
    }
    return NULL;
}

void BatakPlayer::computeScore()
{
    int numberOfTricks = scoredCards.size() / 4;

    if (numberOfTricks >= bid_) {
        score += (bid_ * 10);
    } else {
        score += (bid_ * (-10));
    }
}

int BatakPlayer::makeBidDecision()
{
    return 0;
}

bool BatakPlayer::hasGreaterRankedCard(const Card *rhs) const
{
    foreach (Card *card, hand) {
        if (card->value > rhs->value &&
            card->suit == rhs->suit)
            return true;
    }

    return false;
}

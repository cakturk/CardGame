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
    // TODO: improve decision
    CardSequence seq;
    Card *retVal;
    Card *lastPlayedCard;

    if (! hand.size())
        return NULL;

    if (state->sizeofCardsOnBoard()) {
        lastPlayedCard = state->lastPlayedCard();
        seq = hand.filterOutLessThan(lastPlayedCard);
        if (seq.size()) {
            retVal = seq.first();
        } else if ((seq = hand.filterBySuit(lastPlayedCard->suit)).size()) {
            retVal = seq.first();
        } else if ((seq = hand.filterBySuit(Card::MACA)).size()) {
            CardSequence spadesOnBoard = state->playedCards()->filterBySuit(Card::MACA);
            // Daha onceden birisi kozlamis
            if (spadesOnBoard.size()) {
                spadesOnBoard.sortCards();
                CardSequence filteredSeq = seq.filterOutLessThan(spadesOnBoard.last());

                if (filteredSeq.size())
                    retVal = filteredSeq.first();
                else
                    retVal = seq.first();
            }
        }
    } else {
        // TODO: Eger elinde baska kart varsa koz acilmadan koz atmamali.
        seq = hand.filterOut(Card::MACA);
        if (seq.size())
            retVal = seq.first();
        else
            retVal = hand.first();
    }

    retVal = hand.take(retVal);

    return retVal;
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

bool BatakPlayer::hasGreaterRankedCard(const Card *) const
{
    return false;
}

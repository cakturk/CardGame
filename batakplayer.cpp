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

Card* BatakPlayer::dummyPlay(State &state)
{
    // TODO: improve decision
    CardSequence sequence;
    Card *retVal;
    Card *firstPlayedCard;

    if (! hand.size())
        return NULL;

    if (state.sizeofCardsOnBoard()) {
        firstPlayedCard = state.firstPlayedCard();
        Card *c = state.cardsOnBoard().highestRankedCardFor(firstPlayedCard->suit);

        sequence = hand.filterOutLessThan(c);
        if (sequence.size()) {
            retVal = sequence.first();
        } else if ((sequence = hand.filterBySuit(firstPlayedCard->suit)).size()) {
            retVal = sequence.first();
        } else if ((sequence = hand.filterBySuit(Card::MACA)).size()) {
            CardSequence spadesOnBoard = state.playedCards().filterBySuit(Card::MACA);
            // Daha onceden birisi kozlamis
            if (spadesOnBoard.size()) {
                spadesOnBoard.sortCards();
                CardSequence filteredSeq = sequence.filterOutLessThan(spadesOnBoard.last());

                if (filteredSeq.size())
                    retVal = filteredSeq.first();
                else
                    retVal = sequence.first();
            }
        }
    } else {
        // TODO: Eger elinde baska kart varsa koz acilmadan koz atmamali.
        sequence = hand.filterOut(Card::MACA);
        if (sequence.size())
            retVal = sequence.first();
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

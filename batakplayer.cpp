#include "batakplayer.h"

BatakPlayer::BatakPlayer(int r_pos, QObject *parent) :
        Player(r_pos, parent), bid_(0), tricks_(0)
{ }

BatakPlayer::BatakPlayer(QString name, int pos, QObject *parent) :
        Player(name, pos, parent), bid_(0), tricks_(0)
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

Card* BatakPlayer::play(int index, State &state)
{
    if (index < 0 || index > 12 || hand.isEmpty())
        return NULL;

    Card *selectedCard = hand.at(index);

    if (state.sizeofCardsOnBoard()) {
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

Card* BatakPlayer::dummyPlayV2(State &state)
{
    CardSequence validSeq = validCards(state);

    if (! validSeq.size())
        return NULL;

    state.playedCards().hasGreaterThan(validSeq.first());
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

CardSequence BatakPlayer::validCards(State &state)
{
    CardSequence retVal;
    for (int j = 0; j < hand.size(); ++j)
        if (isValid(hand.at(j), state))
            retVal.append(hand.takeAt(j));

    return retVal;
}

bool BatakPlayer::isValid(Card *selectedCard, State &state)
{
    bool retVal;
    Card *leadingCard;

    leadingCard = state.firstPlayedCard();

    if (selectedCard->suit == leadingCard->suit) {
        Card *highestRankedCard = state.cardsOnBoard().
                                  highestRankedCardFor(leadingCard->suit);
        if (selectedCard->value > highestRankedCard->value) {
            retVal = true;
        } else {
            if (hand.hasGreaterThan(selectedCard->value))
                retVal = false;
            else
                retVal = true;
        }
    } else {
        if (hand.hasSuit(leadingCard->suit))
            retVal = false;
        else {
            if (selectedCard->suit == Card::MACA) {
                if (state.cardsOnBoard().hasMaca()) {
                    Card *highestRankedCard = state.cardsOnBoard().
                                              highestRankedCardFor(Card::MACA);
                    if (selectedCard->value > highestRankedCard->value)
                        retVal = true;
                    else if (hand.hasGreaterThan(highestRankedCard))
                        retVal = false;
                    else
                        retVal = true;
                }
            } else {
                retVal = true;
            }
        }
    }

    return retVal;
}

bool BatakPlayer::hasGreaterRankedCard(const Card *) const
{
    return false;
}

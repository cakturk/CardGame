#include "gameengine.h"
#include "batakengine.h"
#include "state.h"

BatakEngine::BatakEngine(QObject *parent) :
        GameEngine(parent)
{ }

BatakEngine::BatakEngine(int playerNum, QObject *parent) :
        GameEngine(playerNum, parent)
{ }

BatakEngine::~BatakEngine()
{ }

void BatakEngine::checkState(State &)
{
}

void BatakEngine::loopGame()
{
}

Card* BatakEngine::winingCard() const
{
    CardSequence seq = state.cardsOnBoard();
    CardSequence tmp;
    Card *leadingCard, *highestRankedCard;

    if (seq.size() < 4)
        return false;

    leadingCard = seq.first();

    if (seq.hasMaca()) {
        tmp = seq.filterBySuit(Card::MACA);
        tmp.sortCards();
        highestRankedCard = tmp.last();
    } else {
        tmp = seq.filterBySuit(leadingCard->suit);
        if (!tmp.isEmpty()) {
            tmp.sortCards();
            highestRankedCard = tmp.last();
        }
    }

    return highestRankedCard;
}

Player* BatakEngine::winingPlayer(Card *card) const
{
    return map[card];
}

#include "gameengine.h"
#include "batakengine.h"
#include "state.h"
#define MINIMUM_NUMBER_OF_CARDS 13

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
    Player *currentPlayer;
    Card *card;

    for (currentPlayer = playerList_.nextPlayer();
    /*playerList_.currentPlayerPosition() != PlayerList::SOUTH*/;
    currentPlayer = playerList_.nextPlayer()) {

        if ((card = currentPlayer->dummyPlay(state)) != NULL) {
            state.append(card);
            map[card] = currentPlayer;

            if (state.sizeofCardsOnBoard() == 4) {
                Card *wCard = winingCard();
                Player *wPlayer = map[wCard];
                wPlayer->score++;
                state.clearBoard();
            }
        }
    }
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

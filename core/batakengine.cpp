#include "gameengine.h"
#include "batakengine.h"
#include "state.h"

BatakEngine::BatakEngine(int playerNumber, QObject *parent) :
        GameEngine(playerNumber, parent)
{
}

bool BatakEngine::checkState(Player *, State *state)
{
    if (state->sizeofCardsOnBoard() < 4)
        return false;

    Card *bottom = state->bottom();
    Card *lastPlayed = state->top();
    const Card *highestRankedCard = state->highestRankedCardOnBoard(bottom->suit);

    return true;
}
